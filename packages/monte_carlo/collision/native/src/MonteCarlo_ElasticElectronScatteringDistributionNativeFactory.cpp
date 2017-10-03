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
#include "Utility_ContractException.hpp"
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
        new const Utility::DiscreteDistribution( elastic_angles, elastic_pdf, false, true ) );
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

