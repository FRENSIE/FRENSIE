//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungElectronScatteringDistributionACEFactory.cpp
//! \author Luke Kersting
//! \brief  The bremsstrahlung scattering distribution ACE factory definition
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_ArrayView.hpp>

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungElectronScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp"
#include "Utility_TabularCDFDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a simple dipole bremsstrahlung distribution
void BremsstrahlungElectronScatteringDistributionACEFactory::createBremsstrahlungDistribution(
    const Data::XSSEPRDataExtractor& raw_electroatom_data,
    std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
      scattering_distribution,
    const double evaluation_tol )
{
  // Get the number of tables
  double size = raw_electroatom_data.extractBREMIBlock().size()/3;

  // Create the scattering function
  std::shared_ptr<Utility::FullyTabularTwoDDistribution> scattering_function;

  BremsstrahlungElectronScatteringDistributionACEFactory::createScatteringFunction(
                              raw_electroatom_data,
                              scattering_function,
                              evaluation_tol );

  scattering_distribution.reset(
   new BremsstrahlungElectronScatteringDistribution( scattering_function ) );
}

// Create a detailed 2BS bremsstrahlung distribution
void BremsstrahlungElectronScatteringDistributionACEFactory::createBremsstrahlungDistribution(
    const int atomic_number,
    const Data::XSSEPRDataExtractor& raw_electroatom_data,
    std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
      scattering_distribution,
    const double evaluation_tol )
{
  // Get the number of tables
  double size = raw_electroatom_data.extractBREMIBlock().size()/3;

  // Create the scattering function
  std::shared_ptr<Utility::FullyTabularTwoDDistribution> scattering_function;

  BremsstrahlungElectronScatteringDistributionACEFactory::createScatteringFunction(
                              raw_electroatom_data,
                              scattering_function,
                              evaluation_tol );

  scattering_distribution.reset(
   new BremsstrahlungElectronScatteringDistribution( atomic_number,
                                                     scattering_function ) );
}

// Create the energy loss function
/*! \details If the eprdata12 library is used the TwoDInterpPolicy will be set
 *  to LinLinLin to match MCNP6.1. If the eprdata14 library is used the
 *  TwoDInterpPolicy will be set to LogLogLog to match MCNP6.2.
 */
void BremsstrahlungElectronScatteringDistributionACEFactory::createScatteringFunction(
    const Data::XSSEPRDataExtractor& raw_electroatom_data,
    std::shared_ptr<Utility::FullyTabularTwoDDistribution>& scattering_function,
    const double evaluation_tol )
{
  // Extract the bremsstrahlung scattering information data block (BREMI)
  Teuchos::ArrayView<const double> bremi_block(
                    raw_electroatom_data.extractBREMIBlock() );

  // Extract the number of tabulated distributions
  int N = bremi_block.size()/3;

  // Extract the electron energy grid for bremsstrahlung energy distributions
  Teuchos::Array<double> electron_energy_grid(bremi_block(0,N));

  // Extract the table lengths for bremsstrahlung energy distributions
  Teuchos::Array<double> table_length(bremi_block(N,N));

  // Extract the offsets for bremsstrahlung energy distributions
  Teuchos::Array<double> offset(bremi_block(2*N,N));

  // Extract the bremsstrahlung photon energy distributions block (BREME)
  Teuchos::ArrayView<const double> breme_block =
    raw_electroatom_data.extractBREMEBlock();

  // Get the scattering data
  Utility::FullyTabularTwoDDistribution::DistributionType function_data( N );

  // Check if the file version is eprdata14 or eprdata12
  if ( raw_electroatom_data.isEPRVersion14() )
  {
    for( unsigned n = 0; n < N; ++n )
    {
      function_data[n].first = electron_energy_grid[n];

      function_data[n].second.reset(
        new Utility::TabularCDFDistribution<Utility::LogLog>(
            breme_block( offset[n], table_length[n] ),
            breme_block( offset[n] + table_length[n], table_length[n] ),
            true ) );
    }

    // Create the scattering function with LogLogLog interp (eprdata14)
    scattering_function.reset(
      new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::Correlated<Utility::LogLogLog> >(
            function_data,
            1e-6,
            evaluation_tol ) );
  }
  else
  {
    for( unsigned n = 0; n < N; ++n )
    {
      function_data[n].first = electron_energy_grid[n];

      function_data[n].second.reset(
        new Utility::TabularCDFDistribution<Utility::LinLin>(
            breme_block( offset[n], table_length[n] ),
            breme_block( offset[n] + table_length[n], table_length[n] ),
            true ) );
    }

    // Create the scattering function with LinLinLin interp (eprdata12)
    scattering_function.reset(
      new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::Correlated<Utility::LinLinLin> >(
            function_data,
            1e-6,
            evaluation_tol ) );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungElectronScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//

