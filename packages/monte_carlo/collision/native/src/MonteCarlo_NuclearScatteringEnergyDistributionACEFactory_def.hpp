//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclearScatteringEnergyDistributionACEFactory_def.hpp
//! \author Alex Robinson
//! \brief  Nuclear scattering energy distribution factory class template def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AceLaw4NuclearScatteringEnergyDistribution.hpp"
#include "MonteCarlo_AceLaw44NuclearScatteringDistribution.hpp"
#include "MonteCarlo_AceLaw44ARDistribution.hpp"
#include "MonteCarlo_AceLaw44InterpolationPolicy.hpp"
#include "MonteCarlo_StandardAceLaw44ARDistribution.hpp"
#include "MonteCarlo_AceLaw61NuclearScatteringDistribution.hpp"
#include "MonteCarlo_AceLaw61AngleDistribution.hpp"
#include "MonteCarlo_StandardAceLaw61AngleDistribution.hpp"
#include "MonteCarlo_AceLaw61InterpolationPolicy.hpp"
#include "MonteCarlo_LabSystemConversionPolicy.hpp"
#include "MonteCarlo_NuclearScatteringAngularDistributionACEFactory.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create the ACE law 44 coupled energy-angle distribution
template<typename ScatteringDistributionBaseType>
void NuclearScatteringEnergyDistributionACEFactory::createAceLaw44Distribution(
        const double atomic_weight_ratio,
	      const Teuchos::ArrayView<const double>& dlw_block_array,
		    const unsigned dlw_block_array_start_index,
		    const std::string& table_name,
		    const unsigned reaction,
		    const bool is_cm_distribution,
		    Teuchos::RCP<ScatteringDistributionBaseType>& distribution )
{
  typedef AceLaw44NuclearScatteringDistribution<typename ScatteringDistributionBaseType::IncomingParticleState,
						typename ScatteringDistributionBaseType::OutgoingParticleState,
						LabSystemConversionPolicy> 
    AceLaw44NuclearScatteringDistributionLab;

  typedef AceLaw44NuclearScatteringDistribution<typename ScatteringDistributionBaseType::IncomingParticleState,
						typename ScatteringDistributionBaseType::OutgoingParticleState,
						CMSystemConversionPolicy> 
    AceLaw44NuclearScatteringDistributionCM;
						
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
  AceLaw4NuclearScatteringEnergyDistribution::EnergyDistribution 
    energy_distribution( incoming_energies );

  // Initialize the AR distribution array
  typename AceLaw44NuclearScatteringDistributionCM::ARDistributions 
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

  Teuchos::RCP<NuclearScatteringEnergyDistribution> energy_out_distribution; 

  energy_out_distribution.reset( 
      new AceLaw4NuclearScatteringEnergyDistribution( energy_distribution ) );

  if( is_cm_distribution )
  {
    distribution.reset( 
	  new AceLaw44NuclearScatteringDistributionCM(
						       atomic_weight_ratio,
						       energy_out_distribution,
						       ar_distribution ) );
  }
  else
  {
    distribution.reset( 
	  new AceLaw44NuclearScatteringDistributionLab(
						       atomic_weight_ratio,
						       energy_out_distribution,
						       ar_distribution ) );
  }
}


// Create the ACE law 61 coupled energy-angle distribution
template<typename ScatteringDistributionBaseType>
void NuclearScatteringEnergyDistributionACEFactory::createAceLaw61Distribution(
        const double atomic_weight_ratio,
	      const Teuchos::ArrayView<const double>& dlw_block_array,
		    const unsigned dlw_block_array_start_index,
		    const std::string& table_name,
		    const unsigned reaction,
		    const bool is_cm_distribution,
		      Teuchos::RCP<ScatteringDistributionBaseType>& distribution )
{
  typedef AceLaw61NuclearScatteringDistribution<typename ScatteringDistributionBaseType::IncomingParticleState,
						typename ScatteringDistributionBaseType::OutgoingParticleState,
						LabSystemConversionPolicy> 
    AceLaw61NuclearScatteringDistributionLab;

  typedef AceLaw61NuclearScatteringDistribution<typename ScatteringDistributionBaseType::IncomingParticleState,
						typename ScatteringDistributionBaseType::OutgoingParticleState,
						CMSystemConversionPolicy> 
    AceLaw61NuclearScatteringDistributionCM;

  // Make sure the dlw block array is valid
  testPrecondition( dlw_block_array.size() > 0 );

  // Verify that only one law is present
  TEST_FOR_EXCEPTION( dlw_block_array[0] != 0,
		      std::runtime_error,
		      "Error: MT# " << reaction << " in ACE table "
		      << table_name << " has multiple interpolation schemes "
		      " with it, which is not currently supported!\n" );

  // Verify that it is law 61
  TEST_FOR_EXCEPTION( dlw_block_array[1] != 61,
		      std::runtime_error,
		      "Error: MT# " << reaction << " in ACE table "
		      << table_name << " should be law 61!\n" );

  // Start index for ldat data
  int ldat_start_index = (int)dlw_block_array[2] - dlw_block_array_start_index - 1;

  // Verify that only one interpolation scheme is present
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
  AceLaw4NuclearScatteringEnergyDistribution::EnergyDistribution 
    energy_distribution( incoming_energies );

  // Initialize the Angle distribution array
  typename AceLaw61NuclearScatteringDistributionCM::AngleDistributions 
    angle_distribution( incoming_energies );

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

    Teuchos::ArrayView<const double> angle_locations_array = 
      dlw_block_array( distribution_index + 2 + number_points_distribution*3,
	         number_points_distribution );
	         
	  // Array of angular distributions
	  Teuchos::Array< Teuchos::RCP<Utility::OneDDistribution> > 
	    cosine_arrays( number_points_distribution );

    // Read over the tabular angular data
    for( int j = 0; j < number_points_distribution; j++ )
    {
      // Location of the angular data tables
      double angular_data_loc = angle_locations_array[j] - 
        dlw_block_array_start_index;
      
      // Check if tabular data exists
      if( angular_data_loc != 0 )
      {
        // Interpolation flag -> 0 = histogram ... 1 = lin-lin
        int angle_interpolation_flag = dlw_block_array[ angular_data_loc - 1 ];
        
        // Number of angles in the distribution
        int number_of_angles = dlw_block_array[ angular_data_loc ];
        
        Teuchos::ArrayView<const double> cosines = dlw_block_array(
          angular_data_loc + 1, number_of_angles );
          
        Teuchos::ArrayView<const double> angle_pdf;
        
        if( angle_interpolation_flag == 1 ) // Histogram 
        {
          // Get the correct angle_pdf based on interpolation scheme 
          angle_pdf = dlw_block_array(
            angular_data_loc + 2 + number_of_angles, number_of_angles - 1 );
          
          // Construct the angular distribution
          cosine_arrays[j].reset( 
            new Utility::HistogramDistribution( cosines, angle_pdf ) );
        }
        else if( angle_interpolation_flag == 2 ) // Lin-lin
        {
          // Get the correct angle_pdf based on interpolation scheme 
          angle_pdf = dlw_block_array(
            angular_data_loc + 2 + number_of_angles, number_of_angles );
          
          // Construct the angular distribution
          cosine_arrays[j].reset( 
            new Utility::TabularDistribution<Utility::LinLin>( 
              cosines, angle_pdf ) );
        }
        else
        {
          THROW_EXCEPTION( std::runtime_error, "Error: interpolation flag for "
            "Ace Law 61 was found to be " << angle_interpolation_flag <<
            " which does not correspond to histogram or lin-lin "
            "interpolation." );
        }
      }
      else // Otherwise do isotropic scattering
      {
        cosine_arrays[j] = NuclearScatteringAngularDistributionACEFactory::getIsotropicDistribution();
      }
    }


    switch( interpolation_flag )
    {
    case 1: // histogram interpolation
      pdf = dlw_block_array( distribution_index +2+ number_points_distribution,
		       number_points_distribution - 1 );

      energy_distribution[i].second.reset( 
	      new Utility::HistogramDistribution( outgoing_energy_grid, pdf ) );

      angle_distribution[i].reset( 
        new StandardAceLaw61AngleDistribution<AceLaw61HistogramInterpolationPolicy>(
                                                        outgoing_energy_grid,
                                                        cosine_arrays ) );
      break;

    case 2: // Linear-Linear interpolation
      pdf = dlw_block_array( distribution_index +2+ number_points_distribution,
		       number_points_distribution );

      energy_distribution[i].second.reset( 
	      new Utility::TabularDistribution<Utility::LinLin>( 
	                                                     outgoing_energy_grid,
	                                                     pdf ) );

      angle_distribution[i].reset( 
        new StandardAceLaw61AngleDistribution<AceLaw61LinLinInterpolationPolicy>(
                                                        outgoing_energy_grid,
                                                        cosine_arrays ) );
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
  
  Teuchos::RCP<NuclearScatteringEnergyDistribution> energy_out_distribution; 

  energy_out_distribution.reset( 
      new AceLaw4NuclearScatteringEnergyDistribution( energy_distribution ) );

  if( is_cm_distribution )
  {
    distribution.reset( 
	  new AceLaw61NuclearScatteringDistributionCM(
						       atomic_weight_ratio,
						       energy_out_distribution,
						       angle_distribution ) );
  }
  else
  {
    distribution.reset( 
	  new AceLaw61NuclearScatteringDistributionLab(
						       atomic_weight_ratio,
						       energy_out_distribution,
						       angle_distribution ) );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearScatteringEnergyDistributionACEFactory_def.hpp
//---------------------------------------------------------------------------//
