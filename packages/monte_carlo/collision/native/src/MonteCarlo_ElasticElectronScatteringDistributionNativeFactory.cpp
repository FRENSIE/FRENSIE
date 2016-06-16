//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.cpp
//! \author Luke Kersting
//! \brief  The elastic scattering distribution Native factory definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_ContractException.hpp"
#include "Data_DataContainerHelpers.hpp"

namespace MonteCarlo{

// Create the hard elastic distributions ( both Cutoff and Screened Rutherford )
void ElasticElectronScatteringDistributionNativeFactory::createHardElasticDistributions(
	Teuchos::RCP<const CutoffElasticElectronScatteringDistribution>&
        cutoff_elastic_distribution,
	Teuchos::RCP<const ScreenedRutherfordElasticElectronScatteringDistribution>&
        screened_rutherford_elastic_distribution,
	const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double& cutoff_angle_cosine )
{
  // Get the energy grid
  std::vector<double> angular_energy_grid =
    data_container.getElasticAngularEnergyGrid();

  // Get size of paramters
  int size = angular_energy_grid.size();

  // Create the scattering function
  ElasticDistribution scattering_function(size);
  ElasticElectronScatteringDistributionNativeFactory::createCutoffScatteringFunction(
	data_container,
	angular_energy_grid,
	scattering_function );

  // Create cutoff distribution
  cutoff_elastic_distribution.reset(
        new CutoffElasticElectronScatteringDistribution(
                scattering_function,
                cutoff_angle_cosine ) );

  // Get the atomic number
  const int atomic_number = data_container.getAtomicNumber();

  // Create the screened Rutherford distribution
  screened_rutherford_elastic_distribution.reset(
        new MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution(
                cutoff_elastic_distribution,
                atomic_number ) );
}

// Create the hard elastic distributions ( both Cutoff and Screened Rutherford )
/*! \details This function has been overloaded so it can be called without using
 *  the native data container. This functionality is neccessary for generating
 *  native moment preserving data without first creating native data files.
 */
void ElasticElectronScatteringDistributionNativeFactory::createHardElasticDistributions(
	Teuchos::RCP<const CutoffElasticElectronScatteringDistribution>&
        cutoff_elastic_distribution,
	Teuchos::RCP<const ScreenedRutherfordElasticElectronScatteringDistribution>&
        screened_rutherford_elastic_distribution,
    const std::map<double,std::vector<double> >& cutoff_elastic_angles,
    const std::map<double,std::vector<double> >& cutoff_elastic_pdf,
    const std::vector<double>& angular_energy_grid,
    const unsigned& atomic_number,
    const double& cutoff_angle_cosine )
{
  // Make sure the angular energy grid is valid
  testPrecondition( angular_energy_grid.back() > 0 );
  testPrecondition(
        Utility::Sort::isSortedAscending( angular_energy_grid.begin(),
			                              angular_energy_grid.end() ) );

  Data::testPreconditionValuesGreaterThanZero( angular_energy_grid );
  // Make sure the upper cutoff angle cosine is valid
  testPrecondition( cutoff_angle_cosine <= 1.0 );
  testPrecondition( cutoff_angle_cosine > -1.0 );
  // Make sure the atomic number is valid
  testPrecondition( atomic_number > 0 );
  testPrecondition( atomic_number <= 100 );

  // Get size of paramters
  int size = angular_energy_grid.size();

  // Create the scattering function
  ElasticDistribution scattering_function(size);
  ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction(
        cutoff_elastic_angles,
        cutoff_elastic_pdf,
        angular_energy_grid,
		scattering_function );

  // Create cutoff distribution
  cutoff_elastic_distribution.reset(
        new CutoffElasticElectronScatteringDistribution(
                scattering_function,
                cutoff_angle_cosine ) );

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
    const double& cutoff_angle_cosine )
{
  // Get the energy grid for elastic scattering angular distributions
  std::vector<double> angular_energy_grid =
        data_container.getElasticAngularEnergyGrid();

  // Get size of paramters
  int size = angular_energy_grid.size();

  // Create the scattering function
  ElasticDistribution scattering_function(size);

  ElasticElectronScatteringDistributionNativeFactory::createCutoffScatteringFunction(
		data_container,
        angular_energy_grid,
		scattering_function );

  cutoff_elastic_distribution.reset(
        new CutoffElasticElectronScatteringDistribution(
                scattering_function,
                cutoff_angle_cosine ) );
}


// Create a screened Rutherford elastic distribution
void ElasticElectronScatteringDistributionNativeFactory::createScreenedRutherfordElasticDistribution(
	Teuchos::RCP<const ScreenedRutherfordElasticElectronScatteringDistribution>&
        screened_rutherford_elastic_distribution,
	const Teuchos::RCP<const CutoffElasticElectronScatteringDistribution>&
        cutoff_elastic_distribution,
	const Data::ElectronPhotonRelaxationDataContainer& data_container )
{
  // Get the atomic number
  const int atomic_number = data_container.getAtomicNumber();

  // Create the screened Rutherford distribution
  screened_rutherford_elastic_distribution.reset(
        new MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution(
                cutoff_elastic_distribution,
                atomic_number ) );
}

//! Create a moment preserving elastic distribution
void ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution(
	Teuchos::RCP<const MomentPreservingElasticElectronScatteringDistribution>&
        moment_preserving_elastic_distribution,
	const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double& cutoff_angle_cosine )
{
  // Get the angular energy grid
  std::vector<double> angular_energy_grid =
    data_container.getElasticAngularEnergyGrid();

  // Get size of paramters
  int size = angular_energy_grid.size();

  // Create the scattering function
  DiscreteElasticDistribution scattering_function(size);
  ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingScatteringFunction(
		data_container,
        angular_energy_grid,
		scattering_function );

  // Create the moment preserving distribution
  moment_preserving_elastic_distribution.reset(
        new MonteCarlo::MomentPreservingElasticElectronScatteringDistribution(
                scattering_function,
                cutoff_angle_cosine ) );
}

// Return angle cosine grid for given grid energy bin
std::vector<double> ElasticElectronScatteringDistributionNativeFactory::getAngularGrid(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double& energy,
    const double& cutoff_angle_cosine )
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

  std::vector<double> grid( start, raw_grid.end() );

   grid.insert( grid.begin(), cutoff_angle_cosine );

  return grid;
}

// Return angle cosine grid for the given cutoff angle
std::vector<double> ElasticElectronScatteringDistributionNativeFactory::getAngularGrid(
    const std::vector<double>& raw_cutoff_elastic_angles,
    const double& cutoff_angle_cosine )
{
  // Find the first angle cosine above the cutoff angle cosine
  std::vector<double>::const_iterator start;
  for ( start = raw_cutoff_elastic_angles.begin(); start != raw_cutoff_elastic_angles.end(); start++ )
  {
    if ( *start > cutoff_angle_cosine )
    {
      break;
    }
  }

  std::vector<double> grid( start, raw_cutoff_elastic_angles.end() );

   grid.insert( grid.begin(), cutoff_angle_cosine );

  return grid;
}


// Create the cutoff scattering function
void ElasticElectronScatteringDistributionNativeFactory::createCutoffScatteringFunction(
        const Data::ElectronPhotonRelaxationDataContainer& data_container,
        const std::vector<double>& angular_energy_grid,
        ElasticDistribution& scattering_function )
{
  std::map<double,std::vector<double> > 
    angles( data_container.getCutoffElasticAngles() );

  std::map<double,std::vector<double> > 
    pdf( data_container.getCutoffElasticPDF() );

  ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction(
            angles,
            pdf,
            angular_energy_grid,
            scattering_function );
}

// Create the scattering function
/*! \details This function has been overloaded so it can be called without using
 *  the native data container. This functionality is neccessary for generating
 *  native moment preserving data without first creating native data files.
 */
void ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction(
        const std::map<double,std::vector<double> >& cutoff_elastic_angles,
        const std::map<double,std::vector<double> >& cutoff_elastic_pdf,
        const std::vector<double>& angular_energy_grid,
        ElasticDistribution& scattering_function )
{
  // Make sure the angular energy grid is valid
  testPrecondition( angular_energy_grid.back() > 0 );
  testPrecondition(
        Utility::Sort::isSortedAscending( angular_energy_grid.begin(),
			                              angular_energy_grid.end() ) );

  Data::testPreconditionValuesGreaterThanZero( angular_energy_grid );

  for( unsigned n = 0; n < angular_energy_grid.size(); ++n )
  {
    scattering_function[n].first = angular_energy_grid[n];

    // Get the cutoff elastic scattering angles at the energy
    std::vector<double> angles(
        cutoff_elastic_angles.find( angular_energy_grid[n] )->second );

    // Get the cutoff elastic scatering pdf at the energy
    std::vector<double> pdf(
        cutoff_elastic_pdf.find( angular_energy_grid[n] )->second );

    scattering_function[n].second.reset(
	  new const Utility::TabularDistribution<Utility::LinLin>( angles, pdf ) );
  }
}

// Create the moment preserving scattering function
void ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingScatteringFunction(
        const Data::ElectronPhotonRelaxationDataContainer& data_container,
        const std::vector<double>& angular_energy_grid,
        DiscreteElasticDistribution& scattering_function )
{
  for( unsigned n = 0; n < angular_energy_grid.size(); ++n )
  {
    scattering_function[n].first = angular_energy_grid[n];

    // Get the cutoff elastic scattering angles at the energy
    std::vector<double> angles(
        data_container.getMomentPreservingElasticDiscreteAngles(
            angular_energy_grid[n] ) );

    // Get the cutoff elastic scatering pdf at the energy
    std::vector<double> pdf(
        data_container.getMomentPreservingElasticWeights(
            angular_energy_grid[n] ) );

    scattering_function[n].second.reset(
	  new const Utility::DiscreteDistribution( angles, pdf ) );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElasticScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//

