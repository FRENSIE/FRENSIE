//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.cpp
//! \author Luke Kersting
//! \brief  The elastic scattering distribution Native factory definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Data_DataContainerHelpers.hpp"

namespace MonteCarlo{

//----------------------------------------------------------------------------//
//      ****FORWARD DATA PUBLIC FUNCTIONS****
//----------------------------------------------------------------------------//

//// Create the hybrid elastic distribution ( combined Cutoff and Moment Preserving )
//void ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution(
//    std::shared_ptr<const HybridElasticElectronScatteringDistribution>&
//        hybrid_elastic_distribution,
//    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
//    const Teuchos::ArrayRCP<const double> energy_grid,
//    const Teuchos::ArrayRCP<const double> cutoff_cross_section,
//    const Teuchos::ArrayRCP<const double> moment_preserving_cross_section,
//    const Data::ElectronPhotonRelaxationDataContainer& data_container,
//    const double cutoff_angle_cosine,
//    const bool linlinlog_interpolation_mode_on,
//    const bool correlated_sampling_mode_on )
//{
//  testPostcondition( data_container.hasMomentPreservingData() );

//ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution(
//    hybrid_elastic_distribution,
//    grid_searcher,
//    energy_grid,
//    cutoff_cross_section,
//    data_container.getCutoffElasticAngles(),
//    data_container.getCutoffElasticPDF(),
//    moment_preserving_cross_section,
//    data_container.getMomentPreservingElasticDiscreteAngles(),
//    data_container.getMomentPreservingElasticWeights(),
//    data_container.getElasticAngularEnergyGrid(),
//    cutoff_angle_cosine,
//    linlinlog_interpolation_mode_on,
//    correlated_sampling_mode_on );
//}

//----------------------------------------------------------------------------//
//      ****ADJOINT DATA PUBLIC FUNCTIONS****
//----------------------------------------------------------------------------//

//// Create the hybrid elastic distribution ( combined Cutoff and Moment Preserving )
//void ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution(
//    std::shared_ptr<const HybridElasticElectronScatteringDistribution>&
//        hybrid_elastic_distribution,
//    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
//    const Teuchos::ArrayRCP<const double> energy_grid,
//    const Teuchos::ArrayRCP<const double> cutoff_cross_section,
//    const Teuchos::ArrayRCP<const double> moment_preserving_cross_section,
//    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
//    const double cutoff_angle_cosine,
//    const bool linlinlog_interpolation_mode_on,
//    const bool correlated_sampling_mode_on )
//{
//  testPostcondition( data_container.hasAdjointMomentPreservingData() );

//ThisType::createHybridElasticDistribution(
//    hybrid_elastic_distribution,
//    grid_searcher,
//    energy_grid,
//    cutoff_cross_section,
//    data_container.getAdjointCutoffElasticAngles(),
//    data_container.getAdjointCutoffElasticPDF(),
//    moment_preserving_cross_section,
//    data_container.getAdjointMomentPreservingElasticDiscreteAngles(),
//    data_container.getAdjointMomentPreservingElasticWeights(),
//    data_container.getAdjointElasticAngularEnergyGrid(),
//    cutoff_angle_cosine,
//    linlinlog_interpolation_mode_on,
//    correlated_sampling_mode_on );
//}

//----------------------------------------------------------------------------//
//      ****DATA CONTAINER INDEPENDENT PUBLIC FUNCTIONS****
//----------------------------------------------------------------------------//

//// Create the hybrid elastic distribution ( combined Cutoff and Moment Preserving )
//void ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution(
//    std::shared_ptr<const HybridElasticElectronScatteringDistribution>&
//        hybrid_elastic_distribution,
//    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
//    const Teuchos::ArrayRCP<const double> energy_grid,
//    const Teuchos::ArrayRCP<const double> cutoff_cross_section,
//    const std::map<double,std::vector<double> >& cutoff_elastic_angles,
//    const std::map<double,std::vector<double> >& cutoff_elastic_pdf,
//    const Teuchos::ArrayRCP<const double> moment_preserving_cross_section,
//    const std::map<double,std::vector<double> >& moment_preserving_angles,
//    const std::map<double,std::vector<double> >& moment_preserving_weights,
//    const std::vector<double>& angular_energy_grid,
//    const double cutoff_angle_cosine,
//    const bool linlinlog_interpolation_mode_on,
//    const bool correlated_sampling_mode_on )
//{
//  // Create the hybrid scattering functions and cross section ratio
//  std::shared_ptr<HybridDistribution> hybrid_function;
//  ThisType::createHybridScatteringFunction(
//    grid_searcher,
//    energy_grid,
//    cutoff_cross_section,
//    cutoff_elastic_angles,
//    cutoff_elastic_pdf,
//    moment_preserving_cross_section,
//    moment_preserving_angles,
//    moment_preserving_weights,
//    angular_energy_grid,
//    cutoff_angle_cosine,
//    hybrid_function );

//  // Create hybrid distribution
//  hybrid_elastic_distribution.reset(
//        new HybridElasticElectronScatteringDistribution(
//                hybrid_function,
//                cutoff_angle_cosine,
//                evaluation_tol,
//                linlinlog_interpolation_mode_on ) );
//}

// Create a screened Rutherford elastic distribution
void ElasticElectronScatteringDistributionNativeFactory::createScreenedRutherfordElasticDistribution(
    std::shared_ptr<const ScreenedRutherfordElasticElectronScatteringDistribution>&
        screened_rutherford_elastic_distribution,
    const std::shared_ptr<const CutoffElasticElectronScatteringDistribution>&
        cutoff_elastic_distribution,
    const unsigned atomic_number )
{
  // Create the screened Rutherford distribution
  screened_rutherford_elastic_distribution.reset(
        new MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution(
                cutoff_elastic_distribution,
                atomic_number ) );
}

// Return angle cosine grid with the evaluated pdf for the given energy
void ElasticElectronScatteringDistributionNativeFactory::getAngularGridAndPDF(
    std::vector<double>& angular_grid,
    std::vector<double>& evaluated_pdf,
    const std::vector<double>& raw_angular_grid,
    const std::vector<double>& raw_pdf,
    const double cutoff_angle_cosine )
{
  // Make sure the maps are valid
  testPrecondition( raw_angular_grid.size() == raw_pdf.size() );
  testPrecondition( !raw_angular_grid.empty() );

  if ( cutoff_angle_cosine < raw_angular_grid.back() )
  {
    std::vector<double>::const_iterator end_angle, end_pdf;
    for ( end_angle = raw_angular_grid.begin(); end_angle != raw_angular_grid.end(); end_angle++ )
    {
      if ( *end_angle > cutoff_angle_cosine )
      {
        break;
      }
    }

    unsigned index = std::distance( raw_angular_grid.begin(), end_angle );

    end_pdf = raw_pdf.begin();
    std::advance( end_pdf, index );

    angular_grid.assign( raw_angular_grid.begin(), end_angle );
    evaluated_pdf.assign( raw_pdf.begin(), end_pdf );

    if( angular_grid.back() != cutoff_angle_cosine )
    {
      double pdf_at_cutoff = raw_pdf[index] + (raw_pdf[index] - raw_pdf[index+1])*
                         (cutoff_angle_cosine - raw_angular_grid[index] )/
                         (raw_angular_grid[index+1] - raw_angular_grid[index] );


      angular_grid.push_back( cutoff_angle_cosine );
      evaluated_pdf.push_back( pdf_at_cutoff );
    }
  }
  else
  {
    angular_grid = raw_angular_grid;
    evaluated_pdf = raw_pdf;
  }
}

// Return angle cosine grid below the cutoff
std::vector<double> ElasticElectronScatteringDistributionNativeFactory::getAngularGrid(
    const std::vector<double>& raw_angular_grid,
    const double cutoff_angle_cosine )
{
  // Make sure the map is valid
  testPrecondition( !raw_angular_grid.empty() );

  if ( cutoff_angle_cosine < raw_angular_grid.back() )
  {
    std::vector<double>::const_iterator end_angle;
    for ( end_angle = raw_angular_grid.begin(); end_angle != raw_angular_grid.end(); end_angle++ )
    {
      if ( *end_angle > cutoff_angle_cosine )
      {
        break;
      }
    }
    std::vector<double> angular_grid;
    angular_grid.assign( raw_angular_grid.begin(), end_angle );

    if( angular_grid.back() != cutoff_angle_cosine )
      angular_grid.push_back( cutoff_angle_cosine );

    return angular_grid;
  }
  else
    return raw_angular_grid;
}

// Return angle cosine grid above the cutoff for a given energy
std::vector<double> ElasticElectronScatteringDistributionNativeFactory::getAngularGridAboveCutoff(
    const std::map<double, std::vector<double> >& raw_angular_grid,
    const double energy,
    const double cutoff_angle_cosine )
{
  testPrecondition( energy >= raw_angular_grid.begin()->first );
  testPrecondition( energy <= raw_angular_grid.rbegin()->first );

  // Get the angular grid
  std::vector<double> raw_grid;
  if( raw_angular_grid.count( energy ) > 0 )
  {
    raw_grid = raw_angular_grid.at( energy );
  }
  else
  {
    std::map<double,std::vector<double>>::const_iterator lower_bin, upper_bin;
    upper_bin = raw_angular_grid.upper_bound( energy );
    lower_bin = upper_bin;
    --lower_bin;

    // Use the angular grid for the energy bin closes to the energy
    if ( energy - lower_bin->first <= upper_bin->first - energy )
    {
      raw_grid = lower_bin->second;
    }
    else
    {
      raw_grid = upper_bin->second;
    }
  }

  return ThisType::getAngularGridAboveCutoff(
            raw_grid,
            cutoff_angle_cosine );
}

// Return angle cosine grid above the cutoff
std::vector<double> ElasticElectronScatteringDistributionNativeFactory::getAngularGridAboveCutoff(
    const std::vector<double>& raw_angular_grid,
    const double cutoff_angle_cosine )
{
  // Find the first angle cosine above the cutoff angle cosine
  std::vector<double>::const_iterator start;
  for ( start = raw_angular_grid.begin(); start != raw_angular_grid.end(); start++ )
  {
    if ( *start > cutoff_angle_cosine )
    {
      break;
    }
  }

  std::vector<double> grid( start, raw_angular_grid.end() );

  grid.insert( grid.begin(), cutoff_angle_cosine );

  return grid;
}

//// Create the hybrid elastic scattering functions
//void ElasticElectronScatteringDistributionNativeFactory::createHybridScatteringFunction(
//    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
//    const Teuchos::ArrayRCP<const double> energy_grid,
//    const Teuchos::ArrayRCP<const double> cutoff_cross_section,
//    const std::map<double,std::vector<double> >& cutoff_elastic_angles,
//    const std::map<double,std::vector<double> >& cutoff_elastic_pdf,
//    const Teuchos::ArrayRCP<const double> moment_preserving_cross_section,
//    const std::map<double,std::vector<double> >& moment_preserving_angles,
//    const std::map<double,std::vector<double> >& moment_preserving_weights,
//    const std::vector<double>& angular_energy_grid,
//    const double cutoff_angle_cosine,
//    std::shared_ptr<HybridDistribution>& hybrid_functions )
//{
//  // Get the distribution data
//  HybridDistribution function_data( angular_energy_grid.size() );

//  // Loop through all energies below the max energy
//  for( unsigned n = 0; n < angular_energy_grid.size(); ++n )
//  {
//    ThisType::createHybridScatteringFunction(
//        grid_searcher,
//        energy_grid,
//        cutoff_cross_section,
//        cutoff_elastic_angles,
//        cutoff_elastic_pdf,
//        moment_preserving_cross_section,
//        moment_preserving_angles,
//        moment_preserving_weights,
//        angular_energy_grid[n],
//        cutoff_angle_cosine,
//        function_data[n] );
//  }

//  // Set the cutoff scattering function
//  hybrid_functions.reset( new HybridDistribution( function_data ) );
//}

//// Create the hybrid elastic scattering functions and cross section ratio
//void ElasticElectronScatteringDistributionNativeFactory::createHybridScatteringFunction(
//    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
//    const Teuchos::ArrayRCP<const double> energy_grid,
//    const Teuchos::ArrayRCP<const double> cutoff_cross_section,
//    const std::map<double,std::vector<double> >& cutoff_elastic_angles,
//    const std::map<double,std::vector<double> >& cutoff_elastic_pdf,
//    const Teuchos::ArrayRCP<const double> moment_preserving_cross_section,
//    const std::map<double,std::vector<double> >& moment_preserving_angles,
//    const std::map<double,std::vector<double> >& moment_preserving_weights,
//    const double energy,
//    const double cutoff_angle_cosine,
//    HybridFunction& function_data )
//{
//  testPrecondition( cutoff_elastic_angles.count( energy ) );

//  // Create the cutoff elastic scattering function
//  function_data.first = energy;

//  function_data.second.reset(
//    new const TabularDist( cutoff_elastic_angles.find( energy )->second,
//                           cutoff_elastic_pdf.find( energy )->second ) );

//  function_data.third.reset(
//    new const DiscreteDist( moment_preserving_angles.find( energy )->second,
//                            moment_preserving_weights.find( energy )->second ) );

//  unsigned energy_index =
//    grid_searcher->findLowerBinIndex( energy );

//  // Get the moment preserving cross section at the given energy
//  double mp_cross_section_i =
//    Utility::LinLin::interpolate( energy_grid[energy_index],
//                                  energy_grid[energy_index+1],
//                                  energy,
//                                  moment_preserving_cross_section[energy_index],
//                                  moment_preserving_cross_section[energy_index+1] );

//  // Get the cutoff cross section at the given energy
//  double cutoff_cross_section_i =
//    Utility::LinLin::interpolate( energy_grid[energy_index],
//                                  energy_grid[energy_index+1],
//                                  energy,
//                                  cutoff_cross_section[energy_index],
//                                  cutoff_cross_section[energy_index+1] );

//  // Get the cutoff cdf value at the angle cosine cutoff
//  double cutoff_cdf = function_data.second->evaluateCDF( cutoff_angle_cosine );

//  // Get the ratio of the cutoff the moment preserving cross section
//  function_data.fourth = cutoff_cross_section_i*cutoff_cdf/mp_cross_section_i;
//}

// Create the scattering function at the given energy
/*! \details This function has been overloaded so it can be called without using
 *  the native data container. This functionality is neccessary for generating
 *  native moment preserving data without first creating native data files.
 */
void ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction(
        const std::vector<double>& elastic_angles,
        const std::vector<double>& elastic_pdf,
        const double energy,
        TwoDFunction& function_data,
        const bool discrete_function )
{
  // Make sure the energy is valid
  testPrecondition( !elastic_angles.empty() );
  testPrecondition( !elastic_pdf.empty() );
  testPrecondition( energy > 0.0 );

  // Get the incoming energy
  function_data.first = energy;

  // Create the distribution at the energy
  if ( discrete_function )
  {
    // Create discrete distribution
    function_data.second.reset(
        new const DiscreteDist( elastic_angles, elastic_pdf, false, true ) );
  }
  else
  {
    // Create tabular distribution
    function_data.second.reset(
      new const TabularDist( elastic_angles, elastic_pdf ) );
  }
}

// Create the cutoff elastic scattering function in subrange
void ElasticElectronScatteringDistributionNativeFactory::createScatteringFunctionInSubrange(
    const std::vector<double>& raw_angles,
    const std::vector<double>& raw_pdf,
    const double energy,
    const double cutoff_angle_cosine,
    TwoDFunction& function_data )
{
  // Make sure the energy is valid
  testPrecondition( !raw_angles.empty() );
  testPrecondition( !raw_pdf.empty() );
  testPrecondition( energy > 0.0 );
  testPrecondition( cutoff_angle_cosine > -1.0 );
  testPrecondition( cutoff_angle_cosine <= 1.0 );

  // Get the incoming energy
  function_data.first = energy;

  // Get the angular grid and pdf below the cutoff
  std::vector<double> angles, pdf;
  ThisType::getAngularGridAndPDF(
    angles,
    pdf,
    raw_angles,
    raw_pdf,
    cutoff_angle_cosine );

  // Create tabular distribution
  function_data.second.reset( new const TabularDist( angles, pdf ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElasticScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//

