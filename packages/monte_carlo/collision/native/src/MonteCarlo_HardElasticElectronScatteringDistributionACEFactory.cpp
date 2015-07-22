//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HardElasticElectronScatteringDistributionACEFactory.cpp
//! \author Luke Kersting
//! \brief  The hard elastic scattering distribution ACE factory definition
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayView.hpp>

// FRENSIE Includes
#include "MonteCarlo_HardElasticElectronScatteringDistributionACEFactory.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a hard elastic distribution
void HardElasticElectronScatteringDistributionACEFactory::createHardElasticDistribution(
			  const Data::XSSEPRDataExtractor& raw_electroatom_data,
              const double atomic_weight,
			  Teuchos::RCP<const HardElasticElectronScatteringDistribution>&
			    elastic_distribution )
{
  // Extract the number of tabulated distributions
  int size = raw_electroatom_data.extractELASIBlock().size()/3;

  // Create the scattering function
  HardElasticElectronScatteringDistribution::ElasticDistribution 
                                               scattering_function(size);

  HardElasticElectronScatteringDistributionACEFactory::createScatteringFunction( 
							  raw_electroatom_data,
                              size,
							  scattering_function );

  // Get the atomic number 
  const int atomic_number = raw_electroatom_data.extractAtomicNumber();

  elastic_distribution.reset( 
	      new HardElasticElectronScatteringDistribution( 
                                                  atomic_number,
                                                  atomic_weight,
                                                  scattering_function ) );
}

// Create common angle cosine grid for interpolation between energies
/* \details To calculate the moments of the elastic cross section, the elastic 
 * scattering distriution must be piecewise numerically integrated. In order 
 * to calculate moments with energies inbetween the energy grid points a 
 * common angle cosine grid must be created. */ 
void HardElasticElectronScatteringDistributionACEFactory::createCommonAngularGrid(
                 const Data::XSSEPRDataExtractor& raw_electroatom_data,
                 Teuchos::Array<double>& common_angular_grid )
{
  // Extract the elastic scattering information data block (ELASI)
  Teuchos::ArrayView<const double> elasi_block(
				     raw_electroatom_data.extractELASIBlock() );

  // Get the size of the energy grid
  double size = elasi_block.size()/3;

  // Extract the energy grid for elastic scattering angular distributions
  Teuchos::Array<double> angular_energy_grid(elasi_block(0,size));

  // Extract the table lengths for elastic scattering angular distributions
  Teuchos::Array<double> table_length(elasi_block(size,size));

  // Extract the offsets for elastic scattering angular distributions
  Teuchos::Array<double> offset(elasi_block(2*size,size));

  // Extract the elastic scattering angular distributions block (elas)
  Teuchos::ArrayView<const double> elas_block = 
    raw_electroatom_data.extractELASBlock();

  // Insert first angular bin at -1 and last bin at 0.999999
  common_angular_grid.push_back( -1.0 );
  common_angular_grid.push_back( 0.999999 );
  common_angular_grid.push_back( 1.0 );

  Teuchos::Array<double>::iterator common_bin;

  // Iterate through all energy bins
  for( unsigned n = 0; n < size; ++n )
  {
    Teuchos::Array<double>angular_grid( elas_block( offset[n] +1, 
                                                    table_length[n] - 3 ) );

    // insert any new angles into common grid
    for ( unsigned i = 0; i < angular_grid.size(); i++ )
    {
      common_bin = common_angular_grid.begin();
      for ( unsigned j = 1; j < common_angular_grid.size(); j++ )
      {
        common_bin++;
        if ( common_angular_grid[j-1] < angular_grid[i] && angular_grid[i]< common_angular_grid[j] )
        {
           common_angular_grid.insert( common_bin, angular_grid[i] );
        }
      }
    }
  }
}

// Return angle cosine grid for given grid energy bin
Teuchos::Array<double> HardElasticElectronScatteringDistributionACEFactory::getAngularGrid(
                 const Data::XSSEPRDataExtractor& raw_electroatom_data,
                 unsigned energy_bin )
{
  // Extract the elastic scattering information data block (ELASI)
  Teuchos::ArrayView<const double> elasi_block(
				     raw_electroatom_data.extractELASIBlock() );

  // Get the size of the energy grid
  double size = elasi_block.size()/3;

  // check that energy bin is valid
  testPrecondition( energy_bin <=  size - 1 );

  // Extract the energy grid for elastic scattering angular distributions
  Teuchos::Array<double> angular_energy_grid(elasi_block(0,size));

  // Extract the table lengths for elastic scattering angular distributions
  Teuchos::Array<double> table_length(elasi_block(size,size));

  // Extract the offsets for elastic scattering angular distributions
  Teuchos::Array<double> offset(elasi_block(2*size,size));

  // Extract the elastic scattering angular distributions block (elas)
  Teuchos::ArrayView<const double> elas_block = 
    raw_electroatom_data.extractELASBlock();

  Teuchos::Array<double> grid( elas_block( offset[energy_bin], 
                                           table_length[energy_bin] ) );

  return grid;

}


// Create the scattering function
void HardElasticElectronScatteringDistributionACEFactory::createScatteringFunction(
	   const Data::XSSEPRDataExtractor& raw_electroatom_data,
           const int size,
           HardElasticElectronScatteringDistribution::ElasticDistribution& 
                                                        scattering_function )
{
  // Extract the elastic scattering information data block (ELASI)
  Teuchos::ArrayView<const double> elasi_block(
				     raw_electroatom_data.extractELASIBlock() );

  // Extract the energy grid for elastic scattering angular distributions
  Teuchos::Array<double> angular_energy_grid(elasi_block(0,size));

  // Extract the table lengths for elastic scattering angular distributions
  Teuchos::Array<double> table_length(elasi_block(size,size));

  // Extract the offsets for elastic scattering angular distributions
  Teuchos::Array<double> offset(elasi_block(2*size,size));

  // Extract the elastic scattering angular distributions block (elas)
  Teuchos::ArrayView<const double> elas_block = 
    raw_electroatom_data.extractELASBlock();
  
  for( unsigned n = 0; n < size; ++n )
  {
    scattering_function[n].first = angular_energy_grid[n];

    scattering_function[n].second.reset( 
	  new const Utility::HistogramDistribution(
		 elas_block( offset[n], table_length[n] ),
		 elas_block( offset[n] + 1 + table_length[n], table_length[n]-1 ),
         true ) );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_HardElasticScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//

