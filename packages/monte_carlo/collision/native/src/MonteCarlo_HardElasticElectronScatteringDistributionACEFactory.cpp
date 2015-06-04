//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HardElasticScatteringDistributionACEFactory.cpp
//! \author Alex Robinson
//! \brief  The hard elastic scattering distribution ACE factory definition
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayView.hpp>

// FRENSIE Includes
#include "MonteCarlo_HardElasticScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_ThompsonScatteringDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a hard elastic distribution
void HardElasticScatteringDistributionACEFactory::createHardElasticDistribution(
			  const Data::XSSEPRDataExtractor& raw_electroatom_data,
			  Teuchos::RCP<const HardElasticScatteringDistribution>&
			  elastic_distribution )
{
  // Create the scattering function
  HardElasticElectronScatteringDistribution::ElasticDistribution 
                                               scattering_function;

  HardElasticScatteringDistributionACEFactory::createScatteringFunction( 
							  raw_electroatom_data,
							  scattering_function );

  // Get the atomic number 
  const int atomic_number = raw_electroatom_data.extractAtomicNumber();

  elastic_distribution.reset( 
	      new HardElasticScatteringDistribution( scattering_function, 
                                                     atomic_number ) );
}


// Create the scattering function
void HardElasticScatteringDistributionACEFactory::createScatteringFunction(
	   const Data::XSSEPRDataExtractor& raw_electroatom_data,
           HardElasticElectronScatteringDistribution::ElasticDistribution& 
                                                        scattering_function )
{
  // Extract the elastic scattering information data block (ELASI)
  Teuchos::ArrayView<const double> elasi_block(
				      raw_electroatom_data.extractELASIBlock() );
  
  // Extract the number of tabulated distributions
  int size = elasi_block.size()/3;

  // Extract the energy grid for elastic scattering angular distributions
  Teuchos::Array<double> angular_energy_grid(elasi_block(0,size));

  // Extract the table lengths for elastic scattering angular distributions
  Teuchos::Array<double> table_length(elasi_block(size,size));

  // Extract the offsets for elastic scattering angular distributions
  Teuchos::Array<double> offset(elasi_block(2*size,size));

  // Extract the elastic scattering angular distributions block (elas)
  Teuchos::ArrayView<const double> elas_block = 
    raw_electroatom_data.extractELASBlock();

  // Create the elastic scattering distributions
  HardElasticElectronScatteringDistribution::ElasticDistribution
    scattering_function( size );
  
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

