//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.cpp
//! \author Luke Kersting
//! \brief  The elastic scattering distribution Native factory definition
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayView.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create the hard elastic distributions ( both Analog and Screened Rutherford ) 
void ElasticElectronScatteringDistributionNativeFactory::createHardElasticDistributions(
	Teuchos::RCP<const AnalogElasticElectronScatteringDistribution>&
        analog_elastic_distribution,
	Teuchos::RCP<const ScreenedRutherfordElasticElectronScatteringDistribution>&
        screened_rutherford_elastic_distribution,
	const Data::EvaluatedElectronDataContainer& raw_electroatom_data,
    const double analog_lower_cutoff_angle )
{
  // Get the energy grid
  std::vector<double> angular_energy_grid = 
    raw_electroatom_data.getElasticAngularEnergyGrid();

  // Get size of paramters
  int size = angular_energy_grid.size();

  // Create the scattering function
  ElasticDistribution scattering_function(size);
  ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction( 
		raw_electroatom_data, 
        angular_energy_grid,
		scattering_function );

  // Create analog distribution
  analog_elastic_distribution.reset( 
        new AnalogElasticElectronScatteringDistribution( 
                scattering_function,
                analog_lower_cutoff_angle,
                true ) );

  // Upper cutoff angle for the screened Rutherford distribution
  double screened_rutherford_upper_cutoff_angle = 1.0e-6;
/*
  // Create the screened rutherford parmaters
  ParameterArray screened_rutherford_parameters( size );
  createScreenedRutherfordParameterArray( raw_electroatom_data,
                                          angular_energy_grid,
                                          screened_rutherford_parameters );
*/
  // Create the elastic cutoff pdf function
  Teuchos::RCP<const Utility::TabularDistribution<Utility::LinLin> >
    elastic_cutoff_pdf_function;

  ElasticElectronScatteringDistributionNativeFactory::createCutoffPDFFunction(
        scattering_function,
        screened_rutherford_upper_cutoff_angle,
        elastic_cutoff_pdf_function );

  // Get the atomic number 
  const int atomic_number = raw_electroatom_data.getAtomicNumber();
/*
  // Create the screened Rutherford distribution
  screened_rutherford_elastic_distribution.reset(
        new MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution(
                screened_rutherford_parameters,
                upper_cutoff_angle ) );
*/
  // Create the screened Rutherford distribution
  screened_rutherford_elastic_distribution.reset(
        new MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution(
                elastic_cutoff_pdf_function,
                atomic_number,
                screened_rutherford_upper_cutoff_angle ) );
}


// Create a analog elastic distribution
void ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution(
	Teuchos::RCP<const AnalogElasticElectronScatteringDistribution>&
        analog_elastic_distribution,
	const Data::EvaluatedElectronDataContainer& raw_electroatom_data,
    const double lower_cutoff_angle )
{
  // Get the energy grid for elastic scattering angular distributions
  std::vector<double> angular_energy_grid = 
        raw_electroatom_data.getElasticAngularEnergyGrid();

  // Get size of paramters
  int size = angular_energy_grid.size();

  // Create the scattering function
  ElasticDistribution scattering_function(size);

  ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction( 
		raw_electroatom_data, 
        angular_energy_grid,
		scattering_function );

  analog_elastic_distribution.reset( 
        new AnalogElasticElectronScatteringDistribution( 
                scattering_function,
                lower_cutoff_angle,
                true ) );
}


// Create a screened Rutherford elastic distribution
void ElasticElectronScatteringDistributionNativeFactory::createScreenedRutherfordElasticDistribution(
	Teuchos::RCP<const ScreenedRutherfordElasticElectronScatteringDistribution>&
        screened_rutherford_elastic_distribution,
	const Data::EvaluatedElectronDataContainer& raw_electroatom_data,
    const double upper_cutoff_angle )
{
  // Get the energy grid
  std::vector<double> angular_energy_grid = 
    raw_electroatom_data.getElasticAngularEnergyGrid();

  // Get size of paramters
  int size = angular_energy_grid.size();
/*
  // Get the screened rutherford parmaters
  ParameterArray screened_rutherford_parameters( size );

  createScreenedRutherfordParameterArray( raw_electroatom_data,
                                          angular_energy_grid,
                                          screened_rutherford_parameters );
*/
  // Create the scattering function
  ElasticDistribution scattering_function(size);

  ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction( 
		raw_electroatom_data, 
        angular_energy_grid,
		scattering_function );

  // Create the elastic cutoff pdf function
  Teuchos::RCP<const Utility::TabularDistribution<Utility::LinLin> >
    elastic_cutoff_pdf_function;

  ElasticElectronScatteringDistributionNativeFactory::createCutoffPDFFunction(
        scattering_function,
        upper_cutoff_angle,
        elastic_cutoff_pdf_function );

  // Get the atomic number 
  const int atomic_number = raw_electroatom_data.getAtomicNumber();
/*
  // Create the screened Rutherford distribution
  screened_rutherford_elastic_distribution.reset(
        new MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution(
                screened_rutherford_parameters,
                upper_cutoff_angle ) );
*/
  // Create the screened Rutherford distribution
  screened_rutherford_elastic_distribution.reset(
        new MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution(
                elastic_cutoff_pdf_function,
                atomic_number,
                upper_cutoff_angle ) );
}

// Return angle cosine grid for given grid energy bin
Teuchos::Array<double> ElasticElectronScatteringDistributionNativeFactory::getAngularGrid(
                 const Data::EvaluatedElectronDataContainer& raw_electroatom_data,
                 const double energy,
                 const double cutoff_angle )
{
  // Get the angular grid
  std::vector<double> raw_grid = 
    raw_electroatom_data.getAnalogElasticAngles( energy );

  // Find the first angle below the cutoff angle
  std::vector<double>::iterator end = --raw_grid.end();
  for ( end; end != raw_grid.begin(); --end )
  {
    if ( *end < cutoff_angle )
    {
      break;
    }
  }

  Teuchos::Array<double> grid( raw_grid.begin(), ++end );

   grid.push_back( cutoff_angle );

  return grid;
}


// Create the scattering function
void ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction(
        const Data::EvaluatedElectronDataContainer& raw_electroatom_data,
        const std::vector<double> angular_energy_grid,      
        ElasticDistribution& scattering_function )
{
  for( unsigned n = 0; n < angular_energy_grid.size(); ++n )
  {
    scattering_function[n].first = angular_energy_grid[n];

    // Get the analog elastic scattering angles at the energy
    Teuchos::Array<double> angles( 
        raw_electroatom_data.getAnalogElasticAngles( angular_energy_grid[n] ) );

    // Get the analog elastic scatering pdf at the energy
    Teuchos::Array<double> pdf( 
        raw_electroatom_data.getAnalogElasticPDF( angular_energy_grid[n] ) );

    scattering_function[n].second.reset( 
	  new const Utility::TabularDistribution<Utility::LinLin>( angles, pdf ) );
  }
}
/*
// Create the screened Rutherford parameter array
void ElasticElectronScatteringDistributionNativeFactory::createScreenedRutherfordParameterArray(
        const Data::EvaluatedElectronDataContainer& raw_electroatom_data,
        const std::vector<double> angular_energy_grid,
        ParameterArray& screened_rutherford_parameters )
{
  // Get Moliere's screening constants
  std::vector<double> moliere_screening_constant = 
    raw_electroatom_data.getMoliereScreeningConstant();

  // Get the normalization constants
  std::vector<double> normalization_constant = 
    raw_electroatom_data.getScreenedRutherfordNormalizationConstant();

  for ( int i = 0; i < angular_energy_grid.size(); ++i )
  {
    screened_rutherford_parameters[i].first = angular_energy_grid[i];
    screened_rutherford_parameters[i].second = moliere_screening_constant[i];
    screened_rutherford_parameters[i].third = normalization_constant[i];
  }
}
*/

// Create the elastic cutoff pdf function
void ElasticElectronScatteringDistributionNativeFactory::createCutoffPDFFunction(
        const AnalogElasticElectronScatteringDistribution::ElasticDistribution& 
                scattering_function,
        const double upper_cutoff_angle,
        Teuchos::RCP<const Utility::TabularDistribution<Utility::LinLin> >&
                elastic_cutoff_pdf_function )
{
  // function size
  int size = scattering_function.size();

  // Generate the angular energy grid and cutoff pdf
  Teuchos::Array<double> energy_grid(size), cutoff_pdf(size);
  
  for( unsigned n = 0; n < scattering_function.size(); ++n )
  {
    energy_grid[n] = scattering_function[n].first;

    cutoff_pdf[n] = 
        scattering_function[n].second->evaluatePDF( upper_cutoff_angle );    
  }  

  elastic_cutoff_pdf_function.reset(
    new Utility::TabularDistribution<Utility::LinLin>(
		 energy_grid,
		 cutoff_pdf,
         false ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElasticScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//

