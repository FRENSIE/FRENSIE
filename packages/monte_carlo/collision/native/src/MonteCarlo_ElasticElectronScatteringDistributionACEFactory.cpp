//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElasticElectronScatteringDistributionACEFactory.cpp
//! \author Luke Kersting
//! \brief  The elastic scattering distribution ACE factory definition
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayView.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElasticElectronScatteringDistributionACEFactory.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create the hard elastic distributions ( both Analog and Screened Rutherford ) 
void ElasticElectronScatteringDistributionACEFactory::createHardElasticDistributions(
	Teuchos::RCP<const AnalogElasticElectronScatteringDistribution>&
        analog_elastic_distribution,
	Teuchos::RCP<const ScreenedRutherfordElasticElectronScatteringDistribution>&
        screened_rutherford_elastic_distribution,
	const Data::XSSEPRDataExtractor& raw_electroatom_data,
    const double analog_lower_cutoff_angle )
{
  // Extract the number of tabulated distributions
  int size = raw_electroatom_data.extractELASIBlock().size()/3;

  // Get the atomic number 
  const int atomic_number = raw_electroatom_data.extractAtomicNumber();

  // Create the scattering function
  AnalogElasticElectronScatteringDistribution::ElasticDistribution 
        scattering_function(size);

  ElasticElectronScatteringDistributionACEFactory::createScatteringFunction( 
							  raw_electroatom_data, 
							  scattering_function );

  // Create analog distribution
  analog_elastic_distribution.reset( 
        new AnalogElasticElectronScatteringDistribution( 
                scattering_function,
                analog_lower_cutoff_angle,
                false ) );

  // Upper cutoff angle for the screened Rutherford distribution
  double screened_rutherford_upper_cutoff_angle = 1.0e-6;

  // Create the elastic cutoff pdf function
  Teuchos::RCP<const Utility::TabularDistribution<Utility::LinLin> >
    elastic_cutoff_pdf_function;

  ElasticElectronScatteringDistributionACEFactory::createCutoffPDFFunction(
        elastic_cutoff_pdf_function,
        scattering_function,
        screened_rutherford_upper_cutoff_angle );

  // Create the screened Rutherford distribution
  screened_rutherford_elastic_distribution.reset(
        new MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution(
                elastic_cutoff_pdf_function,
                atomic_number,
                screened_rutherford_upper_cutoff_angle ) );
}


// Create a analog elastic distribution
void ElasticElectronScatteringDistributionACEFactory::createAnalogElasticDistribution(
	Teuchos::RCP<const AnalogElasticElectronScatteringDistribution>&
        analog_elastic_distribution,
	const Data::XSSEPRDataExtractor& raw_electroatom_data,
    const double lower_cutoff_angle )
{
  // Extract the number of tabulated distributions
  int size = raw_electroatom_data.extractELASIBlock().size()/3;

  // Create the scattering function
  AnalogElasticElectronScatteringDistribution::ElasticDistribution 
        scattering_function(size);

  ElasticElectronScatteringDistributionACEFactory::createScatteringFunction( 
							  raw_electroatom_data, 
							  scattering_function );

  analog_elastic_distribution.reset( 
        new AnalogElasticElectronScatteringDistribution( 
                scattering_function,
                lower_cutoff_angle,
                false ) );
}


// Create a screened Rutherford elastic distribution
void ElasticElectronScatteringDistributionACEFactory::createScreenedRutherfordElasticDistribution(
	Teuchos::RCP<const ScreenedRutherfordElasticElectronScatteringDistribution>&
        screened_rutherford_elastic_distribution,
	const Data::XSSEPRDataExtractor& raw_electroatom_data,
    const double upper_cutoff_angle )
{
  // Extract the number of tabulated distributions
  int size = raw_electroatom_data.extractELASIBlock().size()/3;

  // Create the scattering function
  AnalogElasticElectronScatteringDistribution::ElasticDistribution 
        scattering_function(size);

  ElasticElectronScatteringDistributionACEFactory::createScatteringFunction( 
							  raw_electroatom_data, 
							  scattering_function );

  // Get the atomic number 
  const int atomic_number = raw_electroatom_data.extractAtomicNumber();

  // Create the elastic cutoff pdf function
  Teuchos::RCP<const Utility::TabularDistribution<Utility::LinLin> >
    elastic_cutoff_pdf_function;

  ElasticElectronScatteringDistributionACEFactory::createCutoffPDFFunction(
        elastic_cutoff_pdf_function,
        scattering_function,
        upper_cutoff_angle );

  // Create the screened Rutherford distribution
  screened_rutherford_elastic_distribution.reset(
        new MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution(
                elastic_cutoff_pdf_function,
                atomic_number,
                upper_cutoff_angle ) );
}

// Return angle cosine grid for given grid energy bin
Teuchos::Array<double> ElasticElectronScatteringDistributionACEFactory::getAngularGrid(
                 const Data::XSSEPRDataExtractor& raw_electroatom_data,
                 const unsigned energy_bin,
                 const double cutoff_mu )
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

  Teuchos::Array<double> raw_grid( elas_block( offset[energy_bin], 
                                   table_length[energy_bin] ) );

  // Find the first angle cosine above the cutoff mu
  Teuchos::Array<double>::iterator start;
  for ( start = raw_grid.begin(); start != raw_grid.end(); start++ )
  {
    if ( *start > cutoff_mu )
    {
      break;
    }
  }

  Teuchos::Array<double> grid( start, raw_grid.end() );

   grid.insert( grid.begin(), cutoff_mu );

  return grid;

}


// Create the scattering function
void ElasticElectronScatteringDistributionACEFactory::createScatteringFunction(
        const Data::XSSEPRDataExtractor& raw_electroatom_data,      
        AnalogElasticElectronScatteringDistribution::ElasticDistribution& 
                                                        scattering_function )
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

// Create the elastic cutoff pdf function
void ElasticElectronScatteringDistributionACEFactory::createCutoffPDFFunction(
        Teuchos::RCP<const Utility::TabularDistribution<Utility::LinLin> >&
                elastic_cutoff_pdf_function,
        const AnalogElasticElectronScatteringDistribution::ElasticDistribution& 
                scattering_function,
        const double upper_cutoff_angle )
{
  // function size
  int size = scattering_function.size();

  // Generate the angular energy grid and cutoff pdf
  Teuchos::Array<double> energy_grid(size), cutoff_pdf(size);
  
  for( unsigned n = 0; n < scattering_function.size(); ++n )
  {
    energy_grid[n] = scattering_function[n].first;

    cutoff_pdf[n] = 
        scattering_function[n].second->evaluatePDF( 1.0 - upper_cutoff_angle );    
  }  

  elastic_cutoff_pdf_function.reset(
    new Utility::TabularDistribution<Utility::LinLin>(
		 energy_grid,
		 cutoff_pdf,
         false ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElasticScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//

