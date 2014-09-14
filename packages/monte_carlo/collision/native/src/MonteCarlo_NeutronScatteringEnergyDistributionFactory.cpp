//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_NeutronScatteringEnergyDistributionFactory.cpp
//! \author Alex Robinson, Alex Bennett
//! \brief  Neutron scattering energy distribution factory class declaration
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <stdexcept>

// Trilinos Includes
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_NeutronScatteringEnergyDistributionFactory.hpp"
#include "MonteCarlo_NeutronScatteringAngularDistributionFactory.hpp"
#include "MonteCarlo_AceLaw1NeutronScatteringEnergyDistribution.hpp"
#include "MonteCarlo_AceLaw3NeutronScatteringEnergyDistribution.hpp"
#include "MonteCarlo_AceLaw4NeutronScatteringEnergyDistribution.hpp"
#include "MonteCarlo_AceLaw44NeutronScatteringDistribution.hpp"
#include "MonteCarlo_AceLaw44ARDistribution.hpp"
#include "MonteCarlo_AceLaw44InterpolationPolicy.hpp"
#include "MonteCarlo_StandardAceLaw44ARDistribution.hpp"
#include "MonteCarlo_LabSystemConversionPolicy.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create the energy distribution
void NeutronScatteringEnergyDistributionFactory::createDistribution(
	     const Teuchos::ArrayView<const double>& dlw_block_array,
	     const unsigned dlw_block_array_start_index,
	     const std::string& table_name,
	     const NuclearReactionType reaction,
	     Teuchos::RCP<NeutronScatteringEnergyDistribution>& distribution )
{
  // Make sure the dlw block array is valid
  testPrecondition( dlw_block_array.size() > 0 );

  // Verify that only one law is present
  TEST_FOR_EXCEPTION( dlw_block_array[0] != 0,
		      std::runtime_error,
		      "Error: MT# " << reaction << "in ACE table "
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
    
  default:
    // This law is not currently supported
    TEST_FOR_EXCEPTION( true,
			std::runtime_error,
			"Error: Unsupported ENDF law number " << endf_law <<
			" found in ACE table " << table_name << " for MT# "
			<< reaction << "!\n" );
  }
}

// Create the ENDF law 44 coupled energy-angle distribution
void NeutronScatteringEnergyDistributionFactory::createAceLaw44Distribution(
                    const double atomic_weight_ratio,
	            const Teuchos::ArrayView<const double>& dlw_block_array,
		    const unsigned dlw_block_array_start_index,
		    const std::string& table_name,
		    const NuclearReactionType reaction,
		    const bool is_cm_distribution,
		    Teuchos::RCP<NeutronScatteringDistribution>& distribution )
{
  // Make sure the dlw block array is valid
  testPrecondition( dlw_block_array.size() > 0 );

  // Verify that only one law is present
  TEST_FOR_EXCEPTION( dlw_block_array[0] != 0,
		      std::runtime_error,
		      "Error: MT# " << reaction << " in ACE table "
		      << table_name << " has multiple interpolation schemes "
		      " with it, which is not currently supported!\n" );

  // Verify that it is law 44
  TEST_FOR_EXCEPTION( dlw_block_array[1] != 44,
		      std::runtime_error,
		      "Error: MT# " << reaction << " in ACE table "
		      << table_name << " should be law 44!\n" );

  // Start index for ldat data
  int ldat_start_index = (int)dlw_block_array[2] - dlw_block_array_start_index - 1;

  // Verify that only one law is present
  TEST_FOR_EXCEPTION( dlw_block_array[ldat_start_index] != 0,
		      std::runtime_error,
		      "Error: MT# " << reaction << " in ACE table "
		      << table_name << " has multiple interpolation schemes "
		      " with it, which is not currently supported!\n" );

  // Number of incident energies
  double incoming_energies = dlw_block_array[ldat_start_index + 1];

  // Array of incoming energies
  Teuchos::Array<double> incoming_energies_array = 
    dlw_block_array( ldat_start_index + 2,
		     incoming_energies);

  // Array of distribution locations
  Teuchos::Array<double> distribution_locations = 
    dlw_block_array( ldat_start_index + 2 + incoming_energies,
		     incoming_energies); 

  // Initialize the energy distribution array
  AceLaw4NeutronScatteringEnergyDistribution::EnergyDistribution 
    energy_distribution( incoming_energies );

  // Initialize the AR distribution array
  AceLaw44NeutronScatteringDistribution<CMSystemConversionPolicy>::ARDistributions 
    ar_distribution( incoming_energies );

  // Loop through the incoming energies
  for(int i = 0; i != incoming_energies; i++)
  {
    energy_distribution[i].first = incoming_energies_array[i];

    int distribution_index = static_cast<int>( distribution_locations[i] ) - 
      dlw_block_array_start_index - 1;

    int interpolation_flag = dlw_block_array[distribution_index];

    // Check if discrete lines are present 
    TEST_FOR_EXCEPTION( interpolation_flag > 10,
		        std::runtime_error,
		        "Error: MT# " << reaction << " in ACE table "
		        << table_name << " has discrete lines in continuous"
		        " tabular data, which is not currently supported!\n" );

    int number_points_distribution = dlw_block_array[distribution_index + 1];

    Teuchos::ArrayView<const double> outgoing_energy_grid = 
      dlw_block_array( distribution_index + 2, number_points_distribution );

    Teuchos::ArrayView<const double> pdf;

    Teuchos::ArrayView<const double> R_array = 
      dlw_block_array( distribution_index + 2 + number_points_distribution*3,
		       number_points_distribution );

    Teuchos::ArrayView<const double> A_array = 
      dlw_block_array( distribution_index + 2 + number_points_distribution*4,
		       number_points_distribution );

    switch( interpolation_flag )
    {
    case 1: // histogram interpolation
      pdf = dlw_block_array( distribution_index +2+ number_points_distribution,
			     number_points_distribution - 1 );

      energy_distribution[i].second.reset( 
		      new Utility::HistogramDistribution( outgoing_energy_grid,
							  pdf ) );

      ar_distribution[i].reset( 
	    new StandardAceLaw44ARDistribution<AceLaw44HistogramInterpolationPolicy>(
							  outgoing_energy_grid,
							  A_array,
							  R_array ) );

      break;
 
    case 2: // Linear-Linear interpolation
      pdf = dlw_block_array( distribution_index +2+ number_points_distribution,
			     number_points_distribution );

      energy_distribution[i].second.reset( 
			     new Utility::TabularDistribution<Utility::LinLin>(
						 outgoing_energy_grid, pdf ) );

      ar_distribution[i].reset(
	       new StandardAceLaw44ARDistribution<AceLaw44LinLinInterpolationPolicy>(
							  outgoing_energy_grid,
							  A_array,
							  R_array ) );

      break;
 
    default:
      TEST_FOR_EXCEPTION( true,
                          std::runtime_error,
                          "Unknown interpolation flag in table "
                          << table_name << 
                          " for energy distribution of MT = "
                          << reaction << ": "
                          << interpolation_flag << "\n" );
    } 
  }

  Teuchos::RCP<NeutronScatteringEnergyDistribution> energy_out_distribution; 

  energy_out_distribution.reset( 
	  new AceLaw4NeutronScatteringEnergyDistribution( energy_distribution ) );

  if( is_cm_distribution )
  {
    distribution.reset( 
	   new AceLaw44NeutronScatteringDistribution<CMSystemConversionPolicy>(
						       atomic_weight_ratio,
						       energy_out_distribution,
						       ar_distribution ) );
  }
  else
  {
    distribution.reset( 
	  new AceLaw44NeutronScatteringDistribution<LabSystemConversionPolicy>(
						       atomic_weight_ratio,
						       energy_out_distribution,
						       ar_distribution ) );
  }
}

// Create a AceLaw 1 energy distribution
void NeutronScatteringEnergyDistributionFactory::createAceLaw1EnergyDistribution( 
	      const Teuchos::ArrayView<const double>& dlw_block_array,
	      const unsigned dlw_block_array_start_index,
	      const std::string& table_name,
	      const NuclearReactionType reaction,
	      Teuchos::RCP<NeutronScatteringEnergyDistribution>& distribution )
{
  // Start index for ldat data
    int ldat_start_index = dlw_block_array[2] - dlw_block_array_start_index - 2;

 
    // Verify that there isn't multiple interpolation regions
    TEST_FOR_EXCEPTION( dlw_block_array[ldat_start_index + 1] != 0,
                        std::runtime_error,
                        "Error: MT# " << reaction << " in ACE table "
                        << table_name << " has multiple interpolation regions "
                        " with it, which is not currently supported in AceLaw 1!\n" );
  
    // Number of incident energies
    int incoming_energies = dlw_block_array[ldat_start_index + 2];

    // Initialize the energy grid
    AceLaw1NeutronScatteringEnergyDistribution::EnergyDistArray energy_grid;

    energy_grid.resize(incoming_energies);

    // Loop through the incident energies
    for(int i = 0; i != incoming_energies; i++)
    {
      energy_grid[i].first = dlw_block_array[ldat_start_index + 3 + i];
    }

    // Number of outgoing energies
    double outgoing_energies = dlw_block_array[ldat_start_index + 3 + incoming_energies];

    // Loop through the incoming energies
    for(int i = 0; i != incoming_energies; i++)
    {
      energy_grid[i].second.resize(outgoing_energies,0);
      
      // Loop through the outgoing energies
      for(int j = 0; i != outgoing_energies; j++)
      {
        energy_grid[i].second[j] = dlw_block_array[ldat_start_index + 4 + incoming_energies +
                                        i * outgoing_energies + j];
      }
    }

    // Create the equiprobable bin scattering energy distriubtion (law 1)
    distribution.reset( 
	       new AceLaw1NeutronScatteringEnergyDistribution( energy_grid ) );
}

// Create a AceLaw 3 energy distribution
void NeutronScatteringEnergyDistributionFactory::createAceLaw3EnergyDistribution(
	      const Teuchos::ArrayView<const double>& dlw_block_array,
	      const unsigned dlw_block_array_start_index,
	      const std::string& table_name,
	      const NuclearReactionType reaction,
	      Teuchos::RCP<NeutronScatteringEnergyDistribution>& distribution )
{
  // Verify that there isn't multiple interpolation regions
  TEST_FOR_EXCEPTION( dlw_block_array[3] != 0,
		      std::runtime_error,
		      "Error: MT# " << reaction << "in ACE table "
		      << table_name << " has multiple interpolation regions "
		      " with it, which is not possible in LAW 3!\n" );

  // Parse data
  double ldat1 = 
    dlw_block_array[dlw_block_array[2] - dlw_block_array_start_index - 1];
  double ldat2 = 
    dlw_block_array[dlw_block_array[2] - dlw_block_array_start_index];

  // Create the inelastic level scattering energy distribution (law 3)
  distribution.reset( 
	      new AceLaw3NeutronScatteringEnergyDistribution( ldat1, ldat2 ) );
}

// Create a AceLaw 4 energy distribution
void NeutronScatteringEnergyDistributionFactory::createAceLaw4EnergyDistribution(
	      const Teuchos::ArrayView<const double>& dlw_block_array,
	      const unsigned dlw_block_array_start_index,
	      const std::string& table_name,
	      const NuclearReactionType reaction,
	      Teuchos::RCP<NeutronScatteringEnergyDistribution>& distribution )
{
  // Verify that it is law 4
     TEST_FOR_EXCEPTION( dlw_block_array[1] != 4,
           	      std::runtime_error,
           	      "Error: MT# " << reaction << " in ACE table "
           	      << table_name << " should be law 4!\n" );

     // Start index for ldat data
     int ldat_start_index = (int)dlw_block_array[2] - dlw_block_array_start_index - 1;

     // Verify that only one law is present
     TEST_FOR_EXCEPTION( dlw_block_array[ldat_start_index] != 0,
           	      std::runtime_error,
           	      "Error: MT# " << reaction << " in ACE table "
           	      << table_name << " has multiple interpolation schemes "
           	      " with it, which is not currently supported!\n" );

     // Number of incident energies
     double incoming_energies = dlw_block_array[ldat_start_index + 1];

     // Array of incoming energies
     Teuchos::Array<double> incoming_energies_array = dlw_block_array( ldat_start_index + 2,
                                                                       incoming_energies);

     // Array of distribution locations
     Teuchos::Array<double> distribution_locations = dlw_block_array(ldat_start_index + 2 + incoming_energies,
                                                                  incoming_energies); 

     // Initialize the energy distribution array
     AceLaw4NeutronScatteringEnergyDistribution::EnergyDistribution 
       energy_distribution( incoming_energies );

     // Loop through the incoming energies
     for(int i = 0; i != incoming_energies; i++)
     {
       energy_distribution[i].first = incoming_energies_array[i];

       int distribution_index = static_cast<int>( distribution_locations[i] ) - dlw_block_array_start_index - 1;

       int interpolation_flag = dlw_block_array[distribution_index];

       // Check if discrete lines are present 
       TEST_FOR_EXCEPTION( interpolation_flag > 10,
           	        std::runtime_error,
           	        "Error: MT# " << reaction << "in ACE table "
           	        << table_name << " has discrete lines in continuous"
           	        " tabular data, which is not currently supported!\n" );

       int number_points_distribution = dlw_block_array[distribution_index + 1];

       Teuchos::ArrayView<const double> outgoing_energy_grid = 
         dlw_block_array( distribution_index + 2, number_points_distribution );

       Teuchos::ArrayView<const double> pdf;

       switch( interpolation_flag )
       {
       case 1: // histogram interpolation
         pdf = dlw_block_array( distribution_index +2+ number_points_distribution,
           		     number_points_distribution - 1 );

         energy_distribution[i].second.reset( 
           	      new Utility::HistogramDistribution( outgoing_energy_grid,
           						  pdf ) );

         break;
 
       case 2: // Linear-Linear interpolation
         pdf = dlw_block_array( distribution_index +2+ number_points_distribution,
           		     number_points_distribution );

         energy_distribution[i].second.reset( 
           		     new Utility::TabularDistribution<Utility::LinLin>(
           					 outgoing_energy_grid, pdf ) );

         break;
 
       default:
         TEST_FOR_EXCEPTION( true,
                             std::runtime_error,
                             "Unknown interpolation flag in table "
                             << table_name << 
                             " for energy distribution of MT = "
                             << reaction << ": "
                             << interpolation_flag << "\n" );
       } 
     }

     distribution.reset( 
       new AceLaw4NeutronScatteringEnergyDistribution( energy_distribution ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronScatteringEnergyDistributionFactory.cpp
//---------------------------------------------------------------------------//
