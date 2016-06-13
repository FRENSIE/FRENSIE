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
#include "Utility_HistogramDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a cutoff elastic distribution
void ElasticElectronScatteringDistributionACEFactory::createCutoffElasticDistribution(
	Teuchos::RCP<const CutoffElasticElectronScatteringDistribution>&
        cutoff_elastic_distribution,
	const Data::XSSEPRDataExtractor& raw_electroatom_data,
    const double upper_cutoff_angle_cosine )
{
  // Extract the number of tabulated distributions
  int size = raw_electroatom_data.extractELASIBlock().size()/3;

  // Create the scattering function
  ElasticDistribution scattering_function(size);

  ElasticElectronScatteringDistributionACEFactory::createScatteringFunction(
							  raw_electroatom_data,
							  scattering_function );

  cutoff_elastic_distribution.reset(
        new CutoffElasticElectronScatteringDistribution(
                scattering_function,
                upper_cutoff_angle_cosine ) );
}

// Create the scattering function
void ElasticElectronScatteringDistributionACEFactory::createScatteringFunction(
        const Data::XSSEPRDataExtractor& raw_electroatom_data,
        ElasticDistribution& scattering_function )
{
  // Extract the elastic scattering information data block (ELASI)
  Teuchos::ArrayView<const double> elasi_block(
				     raw_electroatom_data.extractELASIBlock() );

  // Get the size of the angular energy grid
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
// end MonteCarlo_ElasticScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//

