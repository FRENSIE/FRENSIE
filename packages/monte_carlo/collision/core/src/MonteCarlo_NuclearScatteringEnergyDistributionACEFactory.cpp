//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclearScatteringEnergyDistributionACEFactory.cpp
//! \author Alex Robinson, Alex Bennett, Eli Moll
//! \brief  Nuclear scattering energy distribution factory class declaration
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <stdexcept>

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringEnergyDistributionACEFactory.hpp"
#include "MonteCarlo_NuclearScatteringAngularDistributionACEFactory.hpp"
#include "MonteCarlo_AceLaw1NuclearScatteringEnergyDistribution.hpp"
#include "MonteCarlo_AceLaw2NuclearScatteringEnergyDistribution.hpp"
#include "MonteCarlo_AceLaw3NuclearScatteringEnergyDistribution.hpp"
#include "MonteCarlo_AceLaw5NuclearScatteringEnergyDistribution.hpp"
#include "MonteCarlo_AceLaw7NuclearScatteringEnergyDistribution.hpp"
#include "MonteCarlo_AceLaw9NuclearScatteringEnergyDistribution.hpp"
#include "MonteCarlo_AceLaw11NuclearScatteringEnergyDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"

namespace MonteCarlo{

// Determine the coupled angle energy distribution
unsigned NuclearScatteringEnergyDistributionACEFactory::determineCoupledDistribution(
                     const double atomic_weight_ratio,
                     const Utility::ArrayView<const double>& dlw_block_array,
                     const unsigned dlw_block_array_start_index,
                     const std::string& table_name )
{
  return dlw_block_array[1];
}

// Create the energy distribution
void NuclearScatteringEnergyDistributionACEFactory::createDistribution(
      const Utility::ArrayView<const double>& dlw_block_array,
      const unsigned dlw_block_array_start_index,
      const std::string& table_name,
      const unsigned reaction,
      std::shared_ptr<const NuclearScatteringEnergyDistribution>& distribution,
      const double atomic_weight_ratio )
{
  // Make sure the dlw block array is valid
  testPrecondition( dlw_block_array.size() > 0 );

  // Verify that only one law is present
  TEST_FOR_EXCEPTION( dlw_block_array[0] != 0,
		      std::runtime_error,
		      "MT# " << reaction << "in ACE table "
		      << table_name << " has multiple ENDF laws associated "
		      " with it, which is not currently supported!\n" );

  // Extract the ENDF law number
  unsigned endf_law = dlw_block_array[1];

  // Create the energy distribution based on the stated ENDF law
  switch( endf_law )
  {
  case 1u:
    createAceLaw1EnergyDistribution( dlw_block_array,
				     dlw_block_array_start_index,
				     table_name,
				     reaction,
				     distribution );
    break;

  case 2u:
    createAceLaw2EnergyDistribution ( dlw_block_array,
                     dlw_block_array_start_index,
                     table_name,
                     reaction,
                     distribution,
                     atomic_weight_ratio );
    break;

  case 3u:
    createAceLaw3EnergyDistribution( dlw_block_array,
				     dlw_block_array_start_index,
				     table_name,
				     reaction,
				     distribution );
     break;

  case 4u:
    createAceLaw4EnergyDistribution( dlw_block_array,
				     dlw_block_array_start_index,
				     table_name,
				     reaction,
				     distribution );
    break;

  case 5u:
    createAceLaw5EnergyDistribution( dlw_block_array,
				     dlw_block_array_start_index,
				     table_name,
				     reaction,
				     distribution );
    break;

  case 7u:
    createAceLaw7EnergyDistribution( dlw_block_array,
                                     dlw_block_array_start_index,
				     table_name,
				     reaction,
				     distribution );
    break;

  case 9u:
    createAceLaw9EnergyDistribution( dlw_block_array,
                                     dlw_block_array_start_index,
				     table_name,
				     reaction,
				     distribution );
    break;
    
  case 11u:
    createAceLaw11EnergyDistribution( dlw_block_array,
                                      dlw_block_array_start_index,
                                      table_name,
                                      reaction,
                                      distribution );
    break;
    
  default:
    // This law is not currently supported
    TEST_FOR_EXCEPTION( true,
			std::runtime_error,
			"Unsupported ENDF law number " << endf_law <<
			" found in ACE table " << table_name << " for MT# "
			<< reaction << "!\n" );
  }
}

// Create a AceLaw 1 energy distribution
void NuclearScatteringEnergyDistributionACEFactory::createAceLaw1EnergyDistribution(
     const Utility::ArrayView<const double>& dlw_block_array,
     const unsigned dlw_block_array_start_index,
     const std::string& table_name,
     const unsigned reaction,
     std::shared_ptr<const NuclearScatteringEnergyDistribution>& distribution )
{
  // Start index for ldat data
    int ldat_start_index = dlw_block_array[2] - dlw_block_array_start_index - 2;


    // Verify that there isn't multiple interpolation regions
    TEST_FOR_EXCEPTION( dlw_block_array[ldat_start_index + 1] != 0,
                        std::runtime_error,
                        "MT# " << reaction << " in ACE table "
                        << table_name << " has multiple interpolation regions "
                        " with it, which is not currently supported in AceLaw 1!\n" );

    // Number of incident energies
    int incoming_energies = dlw_block_array[ldat_start_index + 2];

    // Initialize the energy grid
    AceLaw1NuclearScatteringEnergyDistribution::EnergyDistArray energy_grid;

    energy_grid.resize(incoming_energies);

    // Loop through the incident energies
    for(int i = 0; i != incoming_energies; ++i)
    {
      Utility::get<0>( energy_grid[i] ) =
        dlw_block_array[ldat_start_index + 3 + i];
    }

    // Number of outgoing energies
    double outgoing_energies = dlw_block_array[ldat_start_index + 3 + incoming_energies];

    // Loop through the incoming energies
    for(int i = 0; i != incoming_energies; ++i)
    {
      Utility::get<1>( energy_grid[i] ).resize(outgoing_energies,0);

      // Loop through the outgoing energies
      for(int j = 0; i != outgoing_energies; ++j)
      {
        Utility::get<1>( energy_grid[i] )[j] =
          dlw_block_array[ldat_start_index + 4 + incoming_energies +
                          i * outgoing_energies + j];
      }
    }

    // Create the equiprobable bin scattering energy distribution (law 1)
    distribution.reset(
	       new AceLaw1NuclearScatteringEnergyDistribution( energy_grid ) );
}

// Create an AceLaw 2 energy distribution
void NuclearScatteringEnergyDistributionACEFactory::createAceLaw2EnergyDistribution(
      const Utility::ArrayView<const double>& dlw_block_array,
      const unsigned dlw_block_array_start_index,
      const std::string& table_name,
      const unsigned reaction,
      std::shared_ptr<const NuclearScatteringEnergyDistribution>& distribution,
      const double atomic_weight_ratio )
{
  // Verify that the law is Ace Law 2
  TEST_FOR_EXCEPTION( dlw_block_array[1] != 2,
                      std::runtime_error,
                      "MT# " << reaction << " in ACE table "
                      << table_name << " should be law 2!\n" );

  // Start index for ldat data
  int LP =
    (int)dlw_block_array[dlw_block_array[2] - dlw_block_array_start_index - 1];
  double EG =
    dlw_block_array[dlw_block_array[2] - dlw_block_array_start_index];

  // Create the discrete photon distribution
  distribution.reset(
    new AceLaw2NuclearScatteringEnergyDistribution( LP,
                                                    EG,
                                                    atomic_weight_ratio ) );
}

// Create a AceLaw 3 energy distribution
void NuclearScatteringEnergyDistributionACEFactory::createAceLaw3EnergyDistribution(
     const Utility::ArrayView<const double>& dlw_block_array,
     const unsigned dlw_block_array_start_index,
     const std::string& table_name,
     const unsigned reaction,
     std::shared_ptr<const NuclearScatteringEnergyDistribution>& distribution )
{
  // Verify that there isn't multiple interpolation regions
  TEST_FOR_EXCEPTION( dlw_block_array[3] != 0,
		      std::runtime_error,
		      "MT# " << reaction << "in ACE table "
		      << table_name << " has multiple interpolation regions "
		      " with it, which is not possible in LAW 3!\n" );

  // Parse data
  double ldat1 =
    dlw_block_array[dlw_block_array[2] - dlw_block_array_start_index - 1];
  double ldat2 =
    dlw_block_array[dlw_block_array[2] - dlw_block_array_start_index];

  // Create the inelastic level scattering energy distribution (law 3)
  distribution.reset(
	      new AceLaw3NuclearScatteringEnergyDistribution( ldat1, ldat2 ) );
}

// Create a AceLaw 4 energy distribution
void NuclearScatteringEnergyDistributionACEFactory::createAceLaw4EnergyDistribution(
     const Utility::ArrayView<const double>& dlw_block_array,
     const unsigned dlw_block_array_start_index,
     const std::string& table_name,
     const unsigned reaction,
     std::shared_ptr<const NuclearScatteringEnergyDistribution>& distribution )
{
  // Verify that it is law 4
  TEST_FOR_EXCEPTION( dlw_block_array[1] != 4,
           	      std::runtime_error,
           	      "MT# " << reaction << " in ACE table "
           	      << table_name << " should be law 4!\n" );

  // Start index for ldat data
  int ldat_start_index =
    (int)dlw_block_array[2] - dlw_block_array_start_index - 1;

  // Verify that only one law is present
  TEST_FOR_EXCEPTION( dlw_block_array[ldat_start_index] != 0,
           	      std::runtime_error,
           	      "MT# " << reaction << " in ACE table "
           	      << table_name << " has multiple interpolation schemes "
           	      " with it, which is not currently supported!\n" );

  // Number of incident energies
  double incoming_energies = dlw_block_array[ldat_start_index + 1];

  // Array of incoming energies
  Utility::ArrayView<const double> incoming_energies_array =
    dlw_block_array( ldat_start_index + 2, incoming_energies );

  // Array of distribution locations
  Utility::ArrayView<const double> distribution_locations =
    dlw_block_array( ldat_start_index + 2 + incoming_energies,
                        incoming_energies );

  // Initialize the energy distribution array
  AceLaw4NuclearScatteringEnergyDistribution::EnergyDistribution
    energy_distribution( incoming_energies );

  // Loop through the incoming energies
  for(int i = 0; i != incoming_energies; ++i)
  {
    Utility::get<0>( energy_distribution[i] ) = incoming_energies_array[i];
    
    int distribution_index = static_cast<int>( distribution_locations[i] ) - dlw_block_array_start_index - 1;
    
    int interpolation_flag = dlw_block_array[distribution_index];
    
    // Check if discrete lines are present
    TEST_FOR_EXCEPTION( interpolation_flag < 10 && interpolation_flag > 2,
           	        std::runtime_error,
           	        "MT# " << reaction << "in ACE table "
           	        << table_name << " has discrete lines in continuous"
           	        " tabular data, which is not currently supported!\n" );
    
    int number_points_distribution = dlw_block_array[distribution_index + 1];
    
    Utility::ArrayView<const double> outgoing_energy_grid =
      dlw_block_array( distribution_index + 2, number_points_distribution );
    
    Utility::ArrayView<const double> pdf;
    Utility::ArrayView<const double> cdf;
    
    if( interpolation_flag == 1) // histogram interpolation
    {
      pdf = dlw_block_array( distribution_index +2+ number_points_distribution,
           		     number_points_distribution - 1 );
      
      Utility::get<1>( energy_distribution[i] ).reset(
                                                      new Utility::HistogramDistribution( outgoing_energy_grid,
                                                                                          pdf ) );
    }
    else if ( interpolation_flag == 2 ) // lin-lin interpolation
    {
      pdf = dlw_block_array( distribution_index + 2 +
                             number_points_distribution, number_points_distribution );
      
      Utility::get<1>( energy_distribution[i] ).reset(
           		     new Utility::TabularDistribution<Utility::LinLin>(
           					 outgoing_energy_grid, pdf ) );
    }
    else if ( interpolation_flag >= 10 )
    {
      if ( number_points_distribution == 1 )
      {
        Utility::get<1>( energy_distribution[i] ).reset(
                   new Utility::DeltaDistribution( outgoing_energy_grid[0] ) );
      }
      else
      {
        cdf = dlw_block_array( distribution_index + 2 +
                               2*number_points_distribution, number_points_distribution );

        // Version 8 of ENDF has the energy distributions in reverse order
        if( outgoing_energy_grid.begin() < outgoing_energy_grid.end() )
        {
          std::vector<double> outgoing_energy_grid_reverse_vector;
          std::vector<double> cdf_reverse_vector;
          
          for( int j = 0; j < cdf.size(); ++j )
          {
            outgoing_energy_grid_reverse_vector.push_back(
                outgoing_energy_grid[outgoing_energy_grid.size()-1-j] );

            cdf_reverse_vector.push_back( 1.0 - cdf[cdf.size()-1-j] );
          }

          Utility::ArrayView<const double> outgoing_energy_grid_reverse(
                                         outgoing_energy_grid_reverse_vector );

          Utility::ArrayView<const double> cdf_reverse( cdf_reverse_vector );
          
          Utility::get<1>( energy_distribution[i] ).reset(
                   new Utility::DiscreteDistribution(
                                                  outgoing_energy_grid_reverse,
                                                  cdf_reverse,
                                                  true ) );
        }
        else
        {
          Utility::get<1>( energy_distribution[i] ).reset(
                   new Utility::DiscreteDistribution( outgoing_energy_grid,
                                                      cdf,
                                                      true ) );
        }    
      }
    }
    else
    {
      THROW_EXCEPTION( std::runtime_error,
                       "Unknown interpolation flag in table "
                       << table_name <<
                       " for energy distribution of MT = "
                       << reaction << ": "
                       << interpolation_flag << "\n" );
    }
  }

  distribution.reset(
       new AceLaw4NuclearScatteringEnergyDistribution( energy_distribution ) );
}

// Create a AceLaw 5 energy distribution
void NuclearScatteringEnergyDistributionACEFactory::createAceLaw5EnergyDistribution(
     const Utility::ArrayView<const double>& dlw_block_array,
     const unsigned dlw_block_array_start_index,
     const std::string& table_name,
     const unsigned reaction,
     std::shared_ptr<const NuclearScatteringEnergyDistribution>& distribution )
{
  // Verify that it is law 5
  TEST_FOR_EXCEPTION( dlw_block_array[1] != 5,
           	      std::runtime_error,
           	      "MT# " << reaction << " in ACE table "
           	      << table_name << " should be law 5!\n" );

  // Start index for ldat data
  int ldat_start_index =
    (int)dlw_block_array[2] - dlw_block_array_start_index - 1;

  // Verify that only one law is present
  TEST_FOR_EXCEPTION( dlw_block_array[ldat_start_index] != 0,
         	      std::runtime_error,
         	      "MT# " << reaction << " in ACE table "
         	      << table_name << " has multiple interpolation schemes "
         	      " with it, which is not currently supported!\n" );

  // Number of incident energies
  double incoming_energies = dlw_block_array[ldat_start_index + 1];

  // Array of incoming energies
  Utility::ArrayView<const double> incoming_energies_array =
    dlw_block_array( ldat_start_index + 2, incoming_energies );

  // Array of Tabulated energy functions
  Utility::ArrayView<const double> tabulated_energy_function_array =
    dlw_block_array( ldat_start_index + 2 + incoming_energies,
                     incoming_energies );

  // Number of probabilistic functions tabulated
  double prob_function_number =
    dlw_block_array[ldat_start_index + 3 + incoming_energies*2];

  // Array of probabilistic functions
  Utility::ArrayView<const double> probabilistic_function_array =
    dlw_block_array( ldat_start_index + 4 + incoming_energies*2,
                     prob_function_number );

  // Bin width for probabilistic function
  double prob_bin_width = (probabilistic_function_array.back() -
    probabilistic_function_array.front())/(prob_function_number - 1);

  // Initialize the probabilistic function array
  AceLaw5NuclearScatteringEnergyDistribution::EnergyDistribution
     probabilistic_distribution( prob_function_number );

  // Update random_variables_array
  for(int i = 0; i != prob_function_number; ++i)
  {
    Utility::get<0>( probabilistic_distribution[i] ) = prob_bin_width*i;
    Utility::get<1>( probabilistic_distribution[i] ) =
      probabilistic_function_array[i];
  }

  // Initialize the energy distribution array
  AceLaw5NuclearScatteringEnergyDistribution::EnergyDistribution
     energy_distribution( incoming_energies );

  // Loop through incoming energies
  for(int i = 0; i != incoming_energies; ++i)
  {
    Utility::get<0>( energy_distribution[i] ) = incoming_energies_array[i];
    Utility::get<1>( energy_distribution[i] ) =
      tabulated_energy_function_array[i];
  }

  distribution.reset(
    new AceLaw5NuclearScatteringEnergyDistribution( energy_distribution,
                                             probabilistic_distribution ) );
}

// Create a AceLaw 7 energy distribution
void NuclearScatteringEnergyDistributionACEFactory::createAceLaw7EnergyDistribution(
     const Utility::ArrayView<const double>& dlw_block_array,
     const unsigned dlw_block_array_start_index,
     const std::string& table_name,
     const unsigned reaction,
     std::shared_ptr<const NuclearScatteringEnergyDistribution>& distribution )
{
  // Verify that it is law 7
  TEST_FOR_EXCEPTION( dlw_block_array[1] != 7,
           	      std::runtime_error,
           	      "MT# " << reaction << " in ACE table "
           	      << table_name << " should be law 7!\n" );

  // Start index for ldat data
  int ldat_start_index =
    (int)dlw_block_array[2] - dlw_block_array_start_index - 1;

  // Verify that only one law is present
  TEST_FOR_EXCEPTION( dlw_block_array[ldat_start_index] != 0,
         	      std::runtime_error,
         	      "MT# " << reaction << " in ACE table "
         	      << table_name << " has multiple interpolation schemes "
         	      " with it, which is not currently supported!\n" );

  // Number of incident energies
  double incoming_energies = dlw_block_array[ldat_start_index + 1];

  // Array of incoming energies
  Utility::ArrayView<const double> incoming_energies_array =
    dlw_block_array( ldat_start_index + 2, incoming_energies );

  // Array of Tabulated energy functions
  Utility::ArrayView<const double> tabulated_energy_function_array =
    dlw_block_array( ldat_start_index + 2 + incoming_energies,
                     incoming_energies );

  // Initialize the energy distribution array
  AceLaw7NuclearScatteringEnergyDistribution::EnergyDistribution
     energy_distribution( incoming_energies );

  // Loop through incoming energies
  for(int i = 0; i != incoming_energies; ++i)
  {
    Utility::get<0>( energy_distribution[i] ) = incoming_energies_array[i];
    Utility::get<1>( energy_distribution[i] ) =
      tabulated_energy_function_array[i];
  }

  // Restriction energy
  double restriction_energy =
    dlw_block_array[ldat_start_index + 3 + incoming_energies*2];

  distribution.reset(
    new AceLaw7NuclearScatteringEnergyDistribution( energy_distribution,
                                                    restriction_energy ) );
}

// Create a AceLaw 9 energy distribution
void NuclearScatteringEnergyDistributionACEFactory::createAceLaw9EnergyDistribution(
     const Utility::ArrayView<const double>& dlw_block_array,
     const unsigned dlw_block_array_start_index,
     const std::string& table_name,
     const unsigned reaction,
     std::shared_ptr<const NuclearScatteringEnergyDistribution>& distribution )
{
  // Verify that it is law 9
  TEST_FOR_EXCEPTION( dlw_block_array[1] != 9,
           	      std::runtime_error,
           	      "MT# " << reaction << " in ACE table "
           	      << table_name << " should be law 9!\n" );

  // Start index for ldat data
  int ldat_start_index = (int)dlw_block_array[2] - dlw_block_array_start_index - 1;

  // Verify that only one law is present
  TEST_FOR_EXCEPTION( dlw_block_array[ldat_start_index] != 0,
         	      std::runtime_error,
         	      "MT# " << reaction << " in ACE table "
         	      << table_name << " has multiple interpolation schemes "
         	      " with it, which is not currently supported!\n" );

  // Number of incident energies
  double incoming_energies = dlw_block_array[ldat_start_index + 1];

  // Array of incoming energies
  Utility::ArrayView<const double> incoming_energies_array =
    dlw_block_array( ldat_start_index + 2, incoming_energies );

  // Array of Tabulated energy functions
  Utility::ArrayView<const double> tabulated_energy_function_array =
    dlw_block_array( ldat_start_index + 2 + incoming_energies,
                     incoming_energies );

  // Initialize the energy distribution array
  AceLaw9NuclearScatteringEnergyDistribution::EnergyDistribution
     energy_distribution( incoming_energies );

  // Loop through incoming energies
  for(int i = 0; i != incoming_energies; ++i)
  {
    Utility::get<0>( energy_distribution[i] ) = incoming_energies_array[i];
    Utility::get<1>( energy_distribution[i] ) =
      tabulated_energy_function_array[i];
  }

  // Restriction energy
  double restriction_energy = dlw_block_array[ldat_start_index + 3 + incoming_energies*2];

  distribution.reset(
    new AceLaw9NuclearScatteringEnergyDistribution( energy_distribution,
                                                    restriction_energy ) );
}

// Create a AceLaw 11 energy distribution
void NuclearScatteringEnergyDistributionACEFactory::createAceLaw11EnergyDistribution(
     const Utility::ArrayView<const double>& dlw_block_array,
     const unsigned dlw_block_array_start_index,
     const std::string& table_name,
     const unsigned reaction,
     std::shared_ptr<const NuclearScatteringEnergyDistribution>& distribution )
{
  // Verify that it is law 11
  TEST_FOR_EXCEPTION( dlw_block_array[1] != 11,
           	      std::runtime_error,
           	      "MT# " << reaction << " in ACE table "
           	      << table_name << " should be law 11!\n" );

  // Start index for ldat data
  int ldat_start_index =
    (int)dlw_block_array[2] - dlw_block_array_start_index - 1;

  // Verify that only one law is present
  TEST_FOR_EXCEPTION( dlw_block_array[ldat_start_index] != 0,
         	      std::runtime_error,
         	      "MT# " << reaction << " in ACE table "
         	      << table_name << " has multiple interpolation schemes "
         	      " with it, which is not currently supported!\n" );

  // Number of incident energies (a)
  double incoming_energies_a = dlw_block_array[ldat_start_index + 1];

  // Array of incoming energies (a)
  Utility::ArrayView<const double> incoming_energies_array_a =
    dlw_block_array( ldat_start_index + 2, incoming_energies_a );

  // Array of Tabulated energy functions (a)
  Utility::ArrayView<const double> tabulated_a =
    dlw_block_array( ldat_start_index + 2 + incoming_energies_a,
                     incoming_energies_a );

  // Number of incident energies (b)
  double incoming_energies_b = dlw_block_array[ldat_start_index + 4 + 2*incoming_energies_a];

  // Array of incoming energies (b)
  Utility::ArrayView<const double> incoming_energies_array_b =
    dlw_block_array( ldat_start_index + 5 + 2*incoming_energies_a,
                     incoming_energies_b );

  // Array of Tabulated energy functions (b)
  Utility::ArrayView<const double> tabulated_b =
    dlw_block_array( ldat_start_index + 5 + 2*incoming_energies_a + incoming_energies_b,
                     incoming_energies_b );

  // Restriction energy
  double restriction_energy = dlw_block_array[ldat_start_index + 6 + 2*incoming_energies_a + 2*incoming_energies_b];

  // Initialize the energy distribution array (a)
  AceLaw11NuclearScatteringEnergyDistribution::EnergyDistribution
     a_distribution( incoming_energies_a );

  // Loop through incoming energies (a)
  for(int i = 0; i != incoming_energies_a; ++i)
  {
    Utility::get<0>( a_distribution[i] ) = incoming_energies_array_a[i];
    Utility::get<1>( a_distribution[i] ) = tabulated_a[i];
  }

  // Initialize the energy distribution array (b)
  AceLaw11NuclearScatteringEnergyDistribution::EnergyDistribution
     b_distribution( incoming_energies_b );

  // Loop through incoming energies (b)
  for(int i = 0; i != incoming_energies_b; ++i)
  {
    Utility::get<0>( b_distribution[i] ) = incoming_energies_array_b[i];
    Utility::get<1>( b_distribution[i] ) = tabulated_b[i];
  }

  distribution.reset(
    new AceLaw11NuclearScatteringEnergyDistribution( a_distribution,
                                                     b_distribution,
                                                     restriction_energy ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearScatteringEnergyDistributionACEFactory.cpp
//---------------------------------------------------------------------------//
