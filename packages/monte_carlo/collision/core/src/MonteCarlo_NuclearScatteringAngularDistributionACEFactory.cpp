//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclearScatteringAngularDistributionACEFactory.cpp
//! \author Alex Robinson, Alex Bennett
//! \brief  Nuclear scattering angular distribution factory class declaration
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringAngularDistributionACEFactory.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_EquiprobableBinDistribution.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Initialize the static member data
std::shared_ptr<const Utility::TabularUnivariateDistribution>
NuclearScatteringAngularDistributionACEFactory::isotropic_angle_cosine_dist(
			  new Utility::UniformDistribution( -1.0, 1.0, 1.0 ) );

// Create the angular distribution
void NuclearScatteringAngularDistributionACEFactory::createDistribution(
	    const Utility::ArrayView<const double>& and_block_array,
	    const unsigned and_block_array_start_index,
	    const std::string& table_name,
	    const unsigned reaction,
	    std::shared_ptr<const NuclearScatteringAngularDistribution>& distribution )
{
  // Make sure the and block array is "valid"
  testPrecondition( and_block_array.size() > 0 );

  // Get the number of energies at which the angular distribution is tabulated
  unsigned num_tabulated_energies = static_cast<unsigned>(and_block_array[0]);

  // Get the energy grid
  Utility::ArrayView<const double> energy_grid =
    and_block_array( 1, num_tabulated_energies);

  // Get the location of the angular distribution for each energy
  Utility::ArrayView<const double> distribution_indices =
    and_block_array( num_tabulated_energies + 1,
		     num_tabulated_energies );

  // Initialize the angular distribution array
  NuclearScatteringAngularDistribution::AngularDistribution
    angular_distribution( num_tabulated_energies );

  for( unsigned i = 0u; i < energy_grid.size(); ++i )
  {
    Utility::get<0>( angular_distribution[i] ) = energy_grid[i];

    int distribution_index =
      static_cast<int>( distribution_indices[i] );

    // Thirty two equiprobable bin distribution
    if( distribution_index > 0 )
    {
      // Distribution index is relative to beginning of AND block - subtract
      // off start index of portion of and block for given MT #.
      distribution_index = abs(distribution_index) - 1 -
	      and_block_array_start_index;

      Utility::ArrayView<const double> bin_boundaries =
	      and_block_array( distribution_index, 33 );

      Utility::get<1>( angular_distribution[i] ).reset(
	 new Utility::EquiprobableBinDistribution( bin_boundaries ) );
    }

    // Tabular distribution
    else if( distribution_index < 0 )
    {
      // Distribution index is relative to beginning of AND block - subtract
      // off start index of portion of and block for given MT #.
      distribution_index = abs(distribution_index) - 1 -
	and_block_array_start_index;

      unsigned interpolation_flag =
	and_block_array[distribution_index];

      unsigned number_of_points_in_dist =
	and_block_array[distribution_index + 1];

      Utility::ArrayView<const double> scattering_angle_cosine_grid =
	and_block_array( distribution_index + 2,
			 number_of_points_in_dist );

      // Ignore the last evaluated point in the PDF
      Utility::ArrayView<const double> pdf;

      switch( interpolation_flag )
      {
      case 1u: // histogram interpolation
	pdf = and_block_array(
			     distribution_index + 2 + number_of_points_in_dist,
			     number_of_points_in_dist - 1u );

        Utility::get<1>( angular_distribution[i] ).reset(
	      new Utility::HistogramDistribution( scattering_angle_cosine_grid,
						  pdf ) );
	break;

      case 2u: // Linear-Linear interpolation
	pdf = and_block_array(
			     distribution_index + 2 + number_of_points_in_dist,
			     number_of_points_in_dist );

        Utility::get<1>( angular_distribution[i] ).reset(
	                 new Utility::TabularDistribution<Utility::LinLin>(
						  scattering_angle_cosine_grid,
						  pdf ) );

	break;

      default:
	TEST_FOR_EXCEPTION( true,
			    std::runtime_error,
			    "Unknown interpolation flag found in table "
			    << table_name <<
			    " for angular distribution of MT = "
			    << reaction << ": "
			    << interpolation_flag << "\n" );
      }
    }

    // Isotropic distribution
    else
    {
      Utility::get<1>( angular_distribution[i] ) = isotropic_angle_cosine_dist;
    }
  }

  // Create the angular distribution
  distribution.reset(
	   new NuclearScatteringAngularDistribution( angular_distribution ) );
}

// Create the angular distribution
void NuclearScatteringAngularDistributionACEFactory::createSAlphaBetaDistribution(
	    const Utility::ArrayView<const double>& energy_grid,
	    const Utility::ArrayView<const double>& itca_block,
	    std::shared_ptr<NuclearScatteringAngularDistribution>& distribution )
{
  // Get the number of incoming energies
  int num_tabulated_energies = energy_grid.size();

  // Initialize the angular distribution array
  NuclearScatteringAngularDistribution::AngularDistribution
    angular_distribution( num_tabulated_energies );

  // Construct equiprobable distribution
  std::vector<double> eq_pdf_vec;
  for (int eq = 0; eq < num_tabulated_energies; ++eq) {
    eq_pdf_vec.push_back( 1.0 );
  }
  Utility::ArrayView<double> equiprobable_pdf = Utility::ArrayView<double>(eq_pdf_vec);
  
  // Keep track of where we are in the data
  int location = 0;

  for( unsigned i = 0u; i < num_tabulated_energies; ++i )
  {
    angular_distribution[i].first = energy_grid[i];

    // Twenty equiprobable cosine distribution
    Utility::ArrayView<const double> cosines = 
	      itca_block( location, 20 );
	      
    location += 20;
	      
    angular_distribution[i].second.reset( 
	    new Utility::DiscreteDistribution( cosines, equiprobable_pdf ) );
  }

  // Create the angular distribution
  distribution.reset( 
	   new NuclearScatteringAngularDistribution( angular_distribution ) );
}

// Create the angular distribution
void NuclearScatteringAngularDistributionACEFactory::createSAlphaBetaIsotropicDistribution(
	    const Utility::ArrayView<const double>& energy_grid,
	    std::shared_ptr<NuclearScatteringAngularDistribution>& distribution )
{
  // Get the number of incoming energies
  int num_tabulated_energies = energy_grid.size();

  // Initialize the angular distribution array
  NuclearScatteringAngularDistribution::AngularDistribution
    angular_distribution( num_tabulated_energies );

  // Construct equiprobable distribution
  std::vector<double> eq_pdf_vec;
  for (int eq = 0; eq < num_tabulated_energies; ++eq) {
    eq_pdf_vec.push_back( 1.0 );
  }
  Utility::ArrayView<double> equiprobable_pdf = Utility::ArrayView<double>(eq_pdf_vec);

  // Keep track of where we are in the data
  int distribution_index = 0;

  for( unsigned i = 0u; i < energy_grid.size(); ++i )
  {
    angular_distribution[i].first = energy_grid[i];

    angular_distribution[i].second = isotropic_angle_cosine_dist;
  }

  // Create the angular distribution
  distribution.reset( 
	   new NuclearScatteringAngularDistribution( angular_distribution ) );
}

// Create an isotropic angular distribution
void NuclearScatteringAngularDistributionACEFactory::createIsotropicDistribution(
	    std::shared_ptr<const NuclearScatteringAngularDistribution>& distribution )
{
  NuclearScatteringAngularDistribution::AngularDistribution
    angular_distribution( 2 );

  Utility::get<0>( angular_distribution[0] ) = 0.0;
  Utility::get<1>( angular_distribution[0] ) = isotropic_angle_cosine_dist;

  Utility::get<0>( angular_distribution[1] ) =
    std::numeric_limits<double>::max();
  Utility::get<1>( angular_distribution[1] ) = isotropic_angle_cosine_dist;

  distribution.reset(
	   new NuclearScatteringAngularDistribution( angular_distribution ) );
}

// Return the isotropic angular distribution
std::shared_ptr<const Utility::TabularUnivariateDistribution> 
  NuclearScatteringAngularDistributionACEFactory::getIsotropicDistribution()
{
  return isotropic_angle_cosine_dist;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearScatteringAngularDistributionACEFactory.cpp
//---------------------------------------------------------------------------//
