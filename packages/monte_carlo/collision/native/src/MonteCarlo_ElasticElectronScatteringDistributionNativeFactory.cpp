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

// Create the analog elastic distribution ( combined Cutoff and Screened Rutherford )
void ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution(
	std::shared_ptr<const AnalogElasticElectronScatteringDistribution>&
        analog_elastic_distribution,
	const Data::ElectronPhotonRelaxationDataContainer& data_container )
{
  // Get the energy grid
  std::vector<double> angular_energy_grid =
    data_container.getElasticAngularEnergyGrid();

  // Get size of paramters
  int size = angular_energy_grid.size();

  // Create the scattering function
  CutoffDistribution scattering_function(size);
  ElasticElectronScatteringDistributionNativeFactory::createCutoffScatteringFunction(
	data_container,
	angular_energy_grid,
	scattering_function );

  // Get the atomic number
  const int atomic_number = data_container.getAtomicNumber();

  // Create analog distribution
  analog_elastic_distribution.reset(
        new AnalogElasticElectronScatteringDistribution(
                scattering_function,
                atomic_number ) );
}

// Create the analog elastic distribution ( combined Cutoff and Screened Rutherford )
/*! \details This function has been overloaded so it can be called without using
 *  the native data container. This functionality is neccessary for generating
 *  native moment preserving data without first creating native data files.
 */
void ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution(
	std::shared_ptr<const AnalogElasticElectronScatteringDistribution>&
        analog_elastic_distribution,
    const std::map<double,std::vector<double> >& cutoff_elastic_angles,
    const std::map<double,std::vector<double> >& cutoff_elastic_pdf,
    const std::vector<double>& angular_energy_grid,
    const unsigned& atomic_number )
{
  // Make sure the angular energy grid is valid
  testPrecondition( angular_energy_grid.back() > 0 );
  testPrecondition(
        Utility::Sort::isSortedAscending( angular_energy_grid.begin(),
			                              angular_energy_grid.end() ) );

  Data::testPreconditionValuesGreaterThanZero( angular_energy_grid );
  // Make sure the atomic number is valid
  testPrecondition( atomic_number > 0 );
  testPrecondition( atomic_number <= 100 );

  // Get size of paramters
  int size = angular_energy_grid.size();

  // Create the scattering function
  CutoffDistribution scattering_function(size);
  ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction(
        cutoff_elastic_angles,
        cutoff_elastic_pdf,
        angular_energy_grid,
		scattering_function );

  // Create analog distribution
  analog_elastic_distribution.reset(
        new AnalogElasticElectronScatteringDistribution(
                scattering_function,
                atomic_number ) );
}

// Create the hybrid elastic distribution ( combined Cutoff and Moment Preserving )
void ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution(
	std::shared_ptr<const HybridElasticElectronScatteringDistribution>&
        hybrid_elastic_distribution,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    const Teuchos::ArrayRCP<const double> energy_grid,
    const Teuchos::ArrayRCP<const double> cutoff_cross_section,
    const Teuchos::ArrayRCP<const double> moment_preserving_cross_section,
	const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double& cutoff_angle_cosine )
{
  // Get the energy grid
  std::vector<double> angular_energy_grid =
    data_container.getElasticAngularEnergyGrid();

  // Get size of paramters
  int size = angular_energy_grid.size();

  // Create the hybrid scattering functions and cross section ratio
  CutoffDistribution cutoff_function(size);
  DiscreteDistribution moment_preserving_function(size);
  ElasticElectronScatteringDistributionNativeFactory::createHybridScatteringFunction(
        data_container,
        grid_searcher,
        energy_grid,
        cutoff_cross_section,
        moment_preserving_cross_section,
        angular_energy_grid,
        cutoff_angle_cosine,
        cutoff_function,
        moment_preserving_function );

  // Create hybrid distribution
  hybrid_elastic_distribution.reset(
        new HybridElasticElectronScatteringDistribution(
                cutoff_function,
                moment_preserving_function,
                cutoff_angle_cosine ) );
}

// Create a cutoff elastic distribution
void ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution(
	std::shared_ptr<const CutoffElasticElectronScatteringDistribution>&
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
  CutoffDistribution scattering_function(size);

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
	std::shared_ptr<const ScreenedRutherfordElasticElectronScatteringDistribution>&
        screened_rutherford_elastic_distribution,
	const std::shared_ptr<const CutoffElasticElectronScatteringDistribution>&
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
	std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution>&
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
    const std::map<double, std::vector<double> >& raw_cutoff_elastic_angles,
    const double& energy,
    const double& cutoff_angle_cosine )
{
  // Get the angular grid
  std::vector<double> raw_grid;
  if( raw_cutoff_elastic_angles.count( energy ) > 0 )
  {
    raw_grid = raw_cutoff_elastic_angles.at( energy );
  }
  else
  {
    std::map<double,std::vector<double>>::const_iterator lower_bin, upper_bin;
    upper_bin = raw_cutoff_elastic_angles.upper_bound( energy );
    lower_bin = upper_bin;
    --lower_bin;

    // Use the angular grid for the energy bin closes to the energy
    if ( energy - Utility::get<0>( *lower_bin ) <=
         Utility::get<0>( *upper_bin ) - energy )
    {
      raw_grid = Utility::get<1>( *lower_bin );
    }
    else
    {
      raw_grid = Utility::get<1>( *upper_bin );
    }
  }

  return ElasticElectronScatteringDistributionNativeFactory::getAngularGrid(
            raw_grid,
            cutoff_angle_cosine );
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
        CutoffDistribution& scattering_function )
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
        CutoffDistribution& scattering_function )
{
  // Make sure the angular energy grid is valid
  testPrecondition( angular_energy_grid.back() > 0 );
  testPrecondition(
        Utility::Sort::isSortedAscending( angular_energy_grid.begin(),
			                              angular_energy_grid.end() ) );

  Data::testPreconditionValuesGreaterThanZero( angular_energy_grid );

  for( unsigned n = 0; n < angular_energy_grid.size(); ++n )
  {
    Utility::get<0>( scattering_function[n] ) = angular_energy_grid[n];

    // Get the cutoff elastic scattering angles at the energy
    std::vector<double> angles(
        cutoff_elastic_angles.find( angular_energy_grid[n] )->second );

    // Get the cutoff elastic scatering pdf at the energy
    std::vector<double> pdf(
        cutoff_elastic_pdf.find( angular_energy_grid[n] )->second );

    Utility::get<1>( scattering_function[n] ).reset(
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
    Utility::get<0>( scattering_function[n] ) = angular_energy_grid[n];

    // Get the cutoff elastic scattering angles at the energy
    std::vector<double> angles(
        data_container.getMomentPreservingElasticDiscreteAngles(
            angular_energy_grid[n] ) );

    // Get the cutoff elastic scatering pdf at the energy
    std::vector<double> pdf(
        data_container.getMomentPreservingElasticWeights(
            angular_energy_grid[n] ) );

    Utility::get<1>( scattering_function[n] ).reset(
	  new const Utility::DiscreteDistribution( angles, pdf ) );
  }
}

// Create the hybrid elastic scattering functions and cross section ratio
void ElasticElectronScatteringDistributionNativeFactory::createHybridScatteringFunction(
        const Data::ElectronPhotonRelaxationDataContainer& data_container,
        const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
        const Teuchos::ArrayRCP<const double> energy_grid,
        const Teuchos::ArrayRCP<const double> cutoff_cross_section,
        const Teuchos::ArrayRCP<const double> moment_preserving_cross_section,
        const std::vector<double>& angular_energy_grid,
        const double cutoff_angle_cosine,
        CutoffDistribution& cutoff_function,
        DiscreteDistribution& moment_preserving_function )
{
  for( unsigned n = 0; n < angular_energy_grid.size(); ++n )
  {
    // Create the cutoff elastic scattering function
    Utility::get<0>( cutoff_function[n] ) = angular_energy_grid[n];

    // Get the cutoff elastic scattering angles at the energy
    Teuchos::Array<double> angles(
        data_container.getCutoffElasticAngles( angular_energy_grid[n] ) );

    // Get the cutoff elastic scatering pdf at the energy
    Teuchos::Array<double> pdf(
        data_container.getCutoffElasticPDF( angular_energy_grid[n] ) );

    Utility::get<1>( cutoff_function[n] ).reset(
      new const Utility::TabularDistribution<Utility::LinLin>( angles, pdf ) );


    // Create the moment preserving discrete elastic scattering function
    Utility::get<0>( moment_preserving_function[n] ) = angular_energy_grid[n];

    // Get the moment preserving elastic scattering angle cosines at the energy
    std::vector<double> discrete_angles(
        data_container.getMomentPreservingElasticDiscreteAngles(
            angular_energy_grid[n] ) );

    // Get the cutoff elastic scatering pdf at the energy
    std::vector<double> weights(
        data_container.getMomentPreservingElasticWeights(
            angular_energy_grid[n] ) );

    Utility::get<1>( moment_preserving_function[n] ).reset(
	  new const Utility::DiscreteDistribution(
        discrete_angles,
        weights ) );

    unsigned energy_index =
        grid_searcher->findLowerBinIndex( angular_energy_grid[n] );

    // Get the moment preserving cross section at the given energy
    double mp_cross_section_i =
        Utility::LinLin::interpolate(
            energy_grid[energy_index],
            energy_grid[energy_index+1],
            angular_energy_grid[n],
            moment_preserving_cross_section[energy_index],
            moment_preserving_cross_section[energy_index+1] );

    // Get the cutoff cross section at the given energy
    double cutoff_cross_section_i =
        Utility::LinLin::interpolate(
            energy_grid[energy_index],
            energy_grid[energy_index+1],
            angular_energy_grid[n],
            cutoff_cross_section[energy_index],
            cutoff_cross_section[energy_index+1] );

    // Get the cutoff cdf value at the angle cosine cutoff
    double cutoff_cdf =
      Utility::get<1>( cutoff_function[n] )->evaluateCDF( cutoff_angle_cosine );

    // Get the ratio of the cutoff cross section to the moment preserving cross section
    Utility::get<2>( moment_preserving_function[n] ) =
      cutoff_cross_section_i*cutoff_cdf/mp_cross_section_i;
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElasticScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//

