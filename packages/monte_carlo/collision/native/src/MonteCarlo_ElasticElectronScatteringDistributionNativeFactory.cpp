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

// Create the hard elastic distributions ( both Cutoff and Screened Rutherford ) 
void ElasticElectronScatteringDistributionNativeFactory::createHardElasticDistributions(
	Teuchos::RCP<const CutoffElasticElectronScatteringDistribution>&
        cutoff_elastic_distribution,
	Teuchos::RCP<const ScreenedRutherfordElasticElectronScatteringDistribution>&
        screened_rutherford_elastic_distribution,
	const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_upper_cutoff_angle_cosine )
{
  // Get the energy grid
  std::vector<double> angular_energy_grid = 
    data_container.getElasticAngularEnergyGrid();

  // Get size of paramters
  int size = angular_energy_grid.size();

  // Create the scattering function
  ElasticDistribution scattering_function(size);
  ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction( 
	data_container, 
	angular_energy_grid,
	scattering_function );

  // Create cutoff distribution
  cutoff_elastic_distribution.reset( 
        new CutoffElasticElectronScatteringDistribution( 
                scattering_function,
                cutoff_upper_cutoff_angle_cosine ) );

/*
  // Create the screened rutherford parmaters
  ParameterArray screened_rutherford_parameters( size );
  createScreenedRutherfordParameterArray( data_container,
                                          angular_energy_grid,
                                          screened_rutherford_parameters );
*/

  // Get the atomic number 
  const int atomic_number = data_container.getAtomicNumber();
/*
  // Create the screened Rutherford distribution
  screened_rutherford_elastic_distribution.reset(
        new MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution(
                screened_rutherford_parameters ) );
*/
  // Create the screened Rutherford distribution
  screened_rutherford_elastic_distribution.reset(
        new MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution(
                cutoff_elastic_distribution,
                atomic_number ) );
}


// Create a cutoff elastic distribution
void ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution(
	Teuchos::RCP<const CutoffElasticElectronScatteringDistribution>&
        cutoff_elastic_distribution,
	const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double lower_cutoff_angle )
{
  // Get the energy grid for elastic scattering angular distributions
  std::vector<double> angular_energy_grid = 
        data_container.getElasticAngularEnergyGrid();

  // Get size of paramters
  int size = angular_energy_grid.size();

  // Create the scattering function
  ElasticDistribution scattering_function(size);

  ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction( 
		data_container, 
        angular_energy_grid,
		scattering_function );

  cutoff_elastic_distribution.reset( 
        new CutoffElasticElectronScatteringDistribution( 
                scattering_function,
                lower_cutoff_angle ) );
}


// Create a screened Rutherford elastic distribution
void ElasticElectronScatteringDistributionNativeFactory::createScreenedRutherfordElasticDistribution(
	Teuchos::RCP<const ScreenedRutherfordElasticElectronScatteringDistribution>&
        screened_rutherford_elastic_distribution,
	const Teuchos::RCP<const CutoffElasticElectronScatteringDistribution>&
        cutoff_elastic_distribution,
	const Data::ElectronPhotonRelaxationDataContainer& data_container )
{
/*
  // Get the energy grid
  std::vector<double> angular_energy_grid = 
    data_container.getElasticAngularEnergyGrid();

  // Get size of paramters
  int size = angular_energy_grid.size();

  // Get the screened rutherford parmaters
  ParameterArray screened_rutherford_parameters( size );

  createScreenedRutherfordParameterArray( data_container,
                                          angular_energy_grid,
                                          screened_rutherford_parameters );

  // Create the screened Rutherford distribution
  screened_rutherford_elastic_distribution.reset(
        new MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution(
                screened_rutherford_parameters ) );
*/
  // Get the atomic number 
  const int atomic_number = data_container.getAtomicNumber();

  // Create the screened Rutherford distribution
  screened_rutherford_elastic_distribution.reset(
        new MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution(
                cutoff_elastic_distribution,
                atomic_number ) );
}

// Return angle cosine grid for given grid energy bin
Teuchos::Array<double> ElasticElectronScatteringDistributionNativeFactory::getAngularGrid(
                 const Data::ElectronPhotonRelaxationDataContainer& data_container,
                 const double energy,
                 const double cutoff_angle_cosine )
{
  // Get the angular grid
  std::vector<double> raw_grid = 
    data_container.getCutoffElasticAngles( energy );

  // Find the first angle cosine above the cutoff angle cosine
  std::vector<double>::iterator start;
  for ( start = raw_grid.begin(); start != raw_grid.end(); start++ )
  {
    if ( *start > cutoff_angle_cosine )
    {
      break;
    }
  }

  Teuchos::Array<double> grid( start, raw_grid.end() );

   grid.insert( grid.begin(), cutoff_angle_cosine );

  return grid;
}


// Create the scattering function
void ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction(
        const Data::ElectronPhotonRelaxationDataContainer& data_container,
        const std::vector<double> angular_energy_grid,      
        ElasticDistribution& scattering_function )
{
  for( unsigned n = 0; n < angular_energy_grid.size(); ++n )
  {
    scattering_function[n].first = angular_energy_grid[n];

    // Get the cutoff elastic scattering angles at the energy
    Teuchos::Array<double> angles( 
        data_container.getCutoffElasticAngles( angular_energy_grid[n] ) );

    // Get the cutoff elastic scatering pdf at the energy
    Teuchos::Array<double> pdf( 
        data_container.getCutoffElasticPDF( angular_energy_grid[n] ) );

    scattering_function[n].second.reset( 
	  new const Utility::TabularDistribution<Utility::LinLin>( angles, pdf ) );
  }
}
/*
// Create the screened Rutherford parameter array
void ElasticElectronScatteringDistributionNativeFactory::createScreenedRutherfordParameterArray(
        const Data::ElectronPhotonRelaxationDataContainer& data_container,
        const std::vector<double> angular_energy_grid,
        ParameterArray& screened_rutherford_parameters )
{
  // Get Moliere's screening constants
  std::vector<double> moliere_screening_constant = 
    data_container.getMoliereScreeningConstant();

  // Get the normalization constants
  std::vector<double> normalization_constant = 
    data_container.getScreenedRutherfordNormalizationConstant();

  for ( int i = 0; i < angular_energy_grid.size(); ++i )
  {
    screened_rutherford_parameters[i].first = angular_energy_grid[i];
    screened_rutherford_parameters[i].second = moliere_screening_constant[i];
    screened_rutherford_parameters[i].third = normalization_constant[i];
  }
}
*/
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElasticScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//

