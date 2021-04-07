//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.cpp
//! \author Luke Kersting
//! \brief  The elastic scattering distribution Native factory definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Data_DataContainerHelpers.hpp"

namespace MonteCarlo{

//----------------------------------------------------------------------------//
//      ****FORWARD DATA PUBLIC FUNCTIONS****
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
//      ****ADJOINT DATA PUBLIC FUNCTIONS****
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
//      ****DATA CONTAINER INDEPENDENT PUBLIC FUNCTIONS****
//----------------------------------------------------------------------------//

// Create a screened Rutherford elastic distribution
void ElasticElectronScatteringDistributionNativeFactory::createScreenedRutherfordElasticDistribution(
    std::shared_ptr<const ScreenedRutherfordElasticElectronScatteringDistribution>&
        screened_rutherford_elastic_distribution,
    const unsigned atomic_number )
{
  // Create the screened Rutherford distribution
  screened_rutherford_elastic_distribution.reset(
        new MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution(
                atomic_number ) );
}

// Calculate the moment preserving cross sections
void ElasticElectronScatteringDistributionNativeFactory::calculateMomentPreservingCrossSections(
    const std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution>&
      cutoff_distribution,
    const std::shared_ptr<const Utility::UnivariateDistribution>& reduction_distribution,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const std::vector<double> >& cutoff_cross_sections,
    const std::shared_ptr<const std::vector<double> >& total_cross_sections,
    const double cutoff_angle_cosine,
    std::vector<double>& cross_sections,
    size_t& threshold_energy_index,
    const double evaluation_tol )
{
  // Make sure the shared pointers are valid
  testPrecondition( cutoff_distribution.use_count() > 0 );
  testPrecondition( reduction_distribution.use_count() > 0 );
  //Make sure the energy grid and cross sections are valid
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid->begin(),
                                                      energy_grid->end() ) );
  testPrecondition( cutoff_cross_sections->size() == energy_grid->size() );
  testPrecondition( total_cross_sections->size() == energy_grid->size() );
  //Make sure the evaluation tolerance is valid
  testPrecondition( evaluation_tol > 0.0 );

  // Get the max energy of the distributions
  double max_energy = reduction_distribution->getUpperBoundOfIndepVar();

  // Get the upper boundary of the max energy
  unsigned upper_bound_index =
      Utility::Search::binaryUpperBoundIndex( energy_grid->begin(),
                                              energy_grid->end(),
                                              max_energy );
  testPostcondition( (*energy_grid)[upper_bound_index] >= max_energy );

  std::vector<double> raw_cross_sections( upper_bound_index+1 );

  if( (*energy_grid)[upper_bound_index] == max_energy )
  {
    ++upper_bound_index;
  }
  else // Calculate the cross section at the max energy if needed
  {
    double total_cross_section =
      Utility::LogLog::interpolate(
            (*energy_grid)[upper_bound_index-1],
            (*energy_grid)[upper_bound_index],
            max_energy,
            (*total_cross_sections)[upper_bound_index-1],
            (*total_cross_sections)[upper_bound_index] );

    double cutoff_cross_section =
      Utility::LogLog::interpolate(
            (*energy_grid)[upper_bound_index-1],
            (*energy_grid)[upper_bound_index],
            max_energy,
            (*cutoff_cross_sections)[upper_bound_index-1],
            (*cutoff_cross_sections)[upper_bound_index] );

    raw_cross_sections[upper_bound_index] =
      ThisType::calculateMomentPreservingCrossSection(
          cutoff_distribution->evaluateCDF( max_energy, cutoff_angle_cosine ),
          reduction_distribution->evaluate( max_energy ),
          cutoff_cross_section,
          total_cross_section );
  }

  threshold_energy_index = 0;
  for( unsigned i = 0; i < upper_bound_index; ++i )
  {
    raw_cross_sections[i] =
      ThisType::calculateMomentPreservingCrossSection(
        cutoff_distribution->evaluateCDF( (*energy_grid)[i], cutoff_angle_cosine ),
        reduction_distribution->evaluate( (*energy_grid)[i] ),
        (*cutoff_cross_sections)[i],
        (*total_cross_sections)[i] );

    if( raw_cross_sections[i] == 0.0 )
    {
      threshold_energy_index = i;
    }
  }

  if( raw_cross_sections.back() == 0.0 )
  {
    threshold_energy_index = raw_cross_sections.size()-1;
  }

  std::vector<double>::iterator start = raw_cross_sections.begin();
  std::advance( start, threshold_energy_index );
  cross_sections.assign( start, raw_cross_sections.end());

  testPrecondition( threshold_energy_index >= 0u );
  testPostcondition( cross_sections.size() + threshold_energy_index ==
                     energy_grid->size() );
}

// Calculate the moment preserving cross section
double ElasticElectronScatteringDistributionNativeFactory::calculateMomentPreservingCrossSection(
    const double& cutoff_cdf,
    const double& cross_section_reduction,
    const double& cutoff_cross_section,
    const double& total_elastic_cross_section )
{
  double rutherford_cross_section =
    total_elastic_cross_section - cutoff_cross_section;

  // Calculate the relative difference between the total and cutoff cross sections
  double relative_difference = rutherford_cross_section/total_elastic_cross_section;

  // Check for roundoff error and reduce to zero if needed
  if ( relative_difference < 1.0e-6 )
    rutherford_cross_section = 0.0;

  return cross_section_reduction*
      (rutherford_cross_section + (1.0 - cutoff_cdf)*cutoff_cross_section);
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
    for ( end_angle = raw_angular_grid.begin(); end_angle != raw_angular_grid.end(); ++end_angle )
    {
      if ( *end_angle > cutoff_angle_cosine )
      {
        break;
      }
    }

    unsigned N = 0;
    for ( ; N < raw_angular_grid.size(); ++N )
        if ( raw_angular_grid[N] >= cutoff_angle_cosine )
            break;

    angular_grid.resize(N+1);
    evaluated_pdf.resize(N+1);

    // Assign the grid before the angle cosine
    for ( unsigned i = 0; i < N; ++i )
    {
      angular_grid[i] = raw_angular_grid[i];
      evaluated_pdf[i] = raw_pdf[i];
    }

    // Get the pdf at the cutoff angle cosine if needed
    if( raw_angular_grid[N] != cutoff_angle_cosine )
    {
      // Assign the angle and pdf at the cutoff angle cosine
      angular_grid[N] = cutoff_angle_cosine;
      evaluated_pdf[N] =
        Utility::LinLin::interpolate( raw_angular_grid[N-1],
                                      raw_angular_grid[N],
                                      cutoff_angle_cosine,
                                      raw_pdf[N-1],
                                      raw_pdf[N] );
    }
    else
    {
      // Assign the angle and pdf at the cutoff angle cosine
      angular_grid[N] = raw_angular_grid[N];
      evaluated_pdf[N] = raw_pdf[N];
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
    for ( end_angle = raw_angular_grid.begin(); end_angle != raw_angular_grid.end(); ++end_angle )
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
  for ( start = raw_angular_grid.begin(); start != raw_angular_grid.end(); ++start )
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

// Create the ratio of the cutoff to the total elastic cross section
void ElasticElectronScatteringDistributionNativeFactory::createCutoffCrossSectionRatios(
    const std::shared_ptr<const std::vector<double> > raw_energy_grid,
    const std::shared_ptr<const std::vector<double> > cutoff_cross_section,
    const std::shared_ptr<const std::vector<double> > total_cross_section,
    std::shared_ptr<const Utility::UnivariateDistribution>& cross_section_ratios )
{
  // Calculate the ratio of the cutoff to the total cross section
  std::vector<double> cross_section_ratio( raw_energy_grid->size() );
  std::vector<double> energy_grid( raw_energy_grid->size() );

  for( unsigned n = 0; n < energy_grid.size(); ++n )
  {
    // Get the energy
    energy_grid[n] = (*raw_energy_grid)[n];

    // Get the ratio of the cutoff to the total cross section
    cross_section_ratio[n] =
      (*cutoff_cross_section)[n]/(*total_cross_section)[n];
  }
    // Create cross section ratios
    cross_section_ratios.reset(
      new const Utility::TabularDistribution<Utility::LogLog>( energy_grid, cross_section_ratio ) );
}

// Create the scattering function at the given energy
/*! \details This function has been overloaded so it can be called without using
 *  the native data container. This functionality is necessary for generating
 *  native moment preserving data without first creating native data files.
 */
void ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction(
        const std::vector<double>& elastic_angles,
        const std::vector<double>& elastic_pdf,
        const double energy,
        double& primary_scattering_function_grid_value,
        std::shared_ptr<const Utility::TabularUnivariateDistribution>&
        secondary_scattering_function_grid_dist,
        const bool discrete_function )
{
  // Make sure the energy is valid
  testPrecondition( !elastic_angles.empty() );
  testPrecondition( !elastic_pdf.empty() );
  testPrecondition( energy > 0.0 );

  // Get the incoming energy
  primary_scattering_function_grid_value = energy;

  // Create the distribution at the energy
  if ( discrete_function )
  {
    // Create discrete distribution
    secondary_scattering_function_grid_dist.reset(
        new const Utility::DiscreteDistribution( elastic_angles, elastic_pdf, false, true ) );
  }
  else
  {
    // Create tabular distribution
    secondary_scattering_function_grid_dist.reset(
      new const TabularDist( elastic_angles, elastic_pdf ) );
  }
}

// Create the cutoff elastic scattering function in subrange
void ElasticElectronScatteringDistributionNativeFactory::createScatteringFunctionInSubrange(
    const std::vector<double>& raw_angles,
    const std::vector<double>& raw_pdf,
    const double energy,
    const double cutoff_angle_cosine,
    double& primary_scattering_function_grid_value,
    std::shared_ptr<const Utility::TabularUnivariateDistribution>&
    secondary_scattering_function_grid_dist )
{
  // Make sure the energy is valid
  testPrecondition( !raw_angles.empty() );
  testPrecondition( !raw_pdf.empty() );
  testPrecondition( energy > 0.0 );
  testPrecondition( cutoff_angle_cosine > -1.0 );
  testPrecondition( cutoff_angle_cosine <= 1.0 );

  // Get the incoming energy
  primary_scattering_function_grid_value = energy;

  // Get the angular grid and pdf below the cutoff
  std::vector<double> angles, pdf;
  ThisType::getAngularGridAndPDF(
    angles,
    pdf,
    raw_angles,
    raw_pdf,
    cutoff_angle_cosine );

  // Create tabular distribution
  secondary_scattering_function_grid_dist.reset( new const TabularDist( angles, pdf ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElasticScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//

