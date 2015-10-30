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
#include "MonteCarlo_LabSystemConversionPolicy.hpp"
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

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearScatteringEnergyDistributionACEFactory_def.hpp
//---------------------------------------------------------------------------//
