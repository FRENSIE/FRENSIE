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
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_DesignByContract.hpp"


namespace MonteCarlo{

// Create the ACE law 44 coupled energy-angle distribution
template<typename ScatteringDistributionBaseType>
void NuclearScatteringEnergyDistributionACEFactory::createAceLaw44Distribution(
          const double atomic_weight_ratio,
          const Utility::ArrayView<const double>& dlw_block_array,
          const unsigned dlw_block_array_start_index,
          const std::string& table_name,
          const unsigned reaction,
          const bool is_cm_distribution,
          std::shared_ptr<const ScatteringDistributionBaseType>& distribution )
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
		      "MT# " << reaction << " in ACE table "
		      << table_name << " has multiple interpolation schemes "
		      " with it, which is not currently supported!\n" );
  
  // Verify that it is law 44
  TEST_FOR_EXCEPTION( dlw_block_array[1] != 44,
		      std::runtime_error,
		      "MT# " << reaction << " in ACE table "
		      << table_name << " should be law 44!\n" );

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
  std::vector<double> incoming_energies_array(
                   dlw_block_array( ldat_start_index + 2, incoming_energies) );

  // Array of distribution locations
  std::vector<double> distribution_locations(
                     dlw_block_array( ldat_start_index + 2 + incoming_energies,
                                      incoming_energies ) );

  // Initialize the energy distribution array
  AceLaw4NuclearScatteringEnergyDistribution::EnergyDistribution
    energy_distribution( incoming_energies );

  // Initialize the AR distribution array
  typename AceLaw44NuclearScatteringDistributionCM::ARDistributions
    ar_distribution( incoming_energies );

  // Loop through the incoming energies
  for(int i = 0; i != incoming_energies; ++i)
  {
    Utility::get<0>( energy_distribution[i] ) = incoming_energies_array[i];

    int distribution_index = static_cast<int>( distribution_locations[i] ) -
      dlw_block_array_start_index - 1;

    int interpolation_flag = dlw_block_array[distribution_index];

    // Check if discrete lines are present
    TEST_FOR_EXCEPTION( interpolation_flag > 10,
		        std::runtime_error,
		        "MT# " << reaction << " in ACE table "
		        << table_name << " has discrete lines in continuous"
		        " tabular data, which is not currently supported!\n" );

    int number_points_distribution = dlw_block_array[distribution_index + 1];

    Utility::ArrayView<const double> outgoing_energy_grid =
      dlw_block_array( distribution_index + 2, number_points_distribution );

    Utility::ArrayView<const double> pdf;

    Utility::ArrayView<const double> R_array =
      dlw_block_array( distribution_index + 2 + number_points_distribution*3,
		       number_points_distribution );

    Utility::ArrayView<const double> A_array =
      dlw_block_array( distribution_index + 2 + number_points_distribution*4,
		       number_points_distribution );

    switch( interpolation_flag )
    {
    case 1: // histogram interpolation
      pdf = dlw_block_array( distribution_index +2+ number_points_distribution,
			     number_points_distribution - 1 );

      Utility::get<1>( energy_distribution[i] ).reset(
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

      Utility::get<1>( energy_distribution[i] ).reset(
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

  std::shared_ptr<NuclearScatteringEnergyDistribution> energy_out_distribution;

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
          const Utility::ArrayView<const double>& dlw_block_array,
          const unsigned dlw_block_array_start_index,
          const std::string& table_name,
          const unsigned reaction,
          const bool is_cm_distribution,
          std::shared_ptr<const ScatteringDistributionBaseType>& distribution )
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
		      "MT# " << reaction << " in ACE table "
		      << table_name << " has multiple interpolation schemes "
		      " with it, which is not currently supported!\n" );

  // Verify that it is law 61
  TEST_FOR_EXCEPTION( dlw_block_array[1] != 61,
		      std::runtime_error,
		      "MT# " << reaction << " in ACE table "
		      << table_name << " should be law 61!\n" );

  // Start index for ldat data
  int ldat_start_index = (int)dlw_block_array[2] - dlw_block_array_start_index - 1;

  // Verify that only one interpolation scheme is present
  TEST_FOR_EXCEPTION( dlw_block_array[ldat_start_index] != 0,
		      std::runtime_error,
		      "MT# " << reaction << " in ACE table "
		      << table_name << " has multiple interpolation schemes "
		      " with it, which is not currently supported!\n" );

  // Number of incident energies
  double incoming_energies = dlw_block_array[ldat_start_index + 1];

  // Array of incoming energies
  std::vector<double> incoming_energies_array(
                  dlw_block_array( ldat_start_index + 2, incoming_energies ) );

  // Array of distribution locations
  std::vector<double> distribution_locations(
                     dlw_block_array( ldat_start_index + 2 + incoming_energies,
                                      incoming_energies ) );
  
  // Initialize the energy distribution array
  AceLaw4NuclearScatteringEnergyDistribution::EnergyDistribution 
    energy_distribution( incoming_energies );

  // Initialize the Angle distribution array
  typename AceLaw61NuclearScatteringDistributionCM::AngleDistributions 
    angle_distribution( incoming_energies );

  // Loop through the incoming energies
  for(int i = 0; i != incoming_energies; ++i)
  {
    Utility::get<0>( energy_distribution[i] ) = incoming_energies_array[i];

    int distribution_index = static_cast<int>( distribution_locations[i] ) - 
      dlw_block_array_start_index - 1;

    int interpolation_flag = dlw_block_array[distribution_index];

    // Check if discrete lines are present 
    TEST_FOR_EXCEPTION( interpolation_flag > 10,
	          std::runtime_error,
	          "MT# " << reaction << " in ACE table "
	          << table_name << " has discrete lines in continuous"
	          " tabular data, which is not currently supported!\n" );

    int number_points_distribution = dlw_block_array[distribution_index + 1];

    Utility::ArrayView<const double> outgoing_energy_grid = 
      dlw_block_array( distribution_index + 2, number_points_distribution );

    Utility::ArrayView<const double> pdf;

    Utility::ArrayView<const double> angle_locations_array = 
      dlw_block_array( distribution_index + 2 + number_points_distribution*3,
	         number_points_distribution );
	         
    // Array of angular distributions
    std::vector<std::shared_ptr<const Utility::UnivariateDistribution> > 
      cosine_arrays( number_points_distribution );

    // Read over the tabular angular data
    for( int j = 0; j < number_points_distribution; ++j )
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
        
        Utility::ArrayView<const double> cosines = dlw_block_array(
          angular_data_loc + 1, number_of_angles );
          
        Utility::ArrayView<const double> angle_pdf;
        
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
          THROW_EXCEPTION( std::runtime_error, "interpolation flag for "
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

      Utility::get<1>( energy_distribution[i] ).reset( 
	      new Utility::HistogramDistribution( outgoing_energy_grid, pdf ) );

      angle_distribution[i].reset( 
        new StandardAceLaw61AngleDistribution<AceLaw61HistogramInterpolationPolicy>(
                                                        outgoing_energy_grid,
                                                        cosine_arrays ) );
      break;

    case 2: // Linear-Linear interpolation
      pdf = dlw_block_array( distribution_index +2+ number_points_distribution,
		       number_points_distribution );

      Utility::get<1>( energy_distribution[i] ).reset( 
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
  
  std::shared_ptr<NuclearScatteringEnergyDistribution> energy_out_distribution; 

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

//! Create the S(alpha,beta) coupled energy-angle inelastic distribution
template<typename ScatteringDistributionBaseType>
void NuclearScatteringEnergyDistributionACEFactory::createSAlphaBetaInelasticDistribution(
    const double atomic_weight_ratio,
    const Utility::ArrayView<const double>& incoming_energies,
    const Utility::ArrayView<const double>& inelastic_locations,
    const Utility::ArrayView<const double>& outgoing_energies,
		const Utility::ArrayView<const double>& itxe_block_array,
    const bool is_continuous_energy,
		const std::string& table_name,
		const unsigned reaction,
		const bool is_cm_distribution,
    std::shared_ptr<ScatteringDistributionBaseType>& distribution )
{
  typedef AceLaw61NuclearScatteringDistribution<typename ScatteringDistributionBaseType::IncomingParticleState,
						typename ScatteringDistributionBaseType::OutgoingParticleState,
						LabSystemConversionPolicy> 
    AceLaw61NuclearScatteringDistributionLab;

  typedef AceLaw61NuclearScatteringDistribution<typename ScatteringDistributionBaseType::IncomingParticleState,
						typename ScatteringDistributionBaseType::OutgoingParticleState,
						CMSystemConversionPolicy> 
    AceLaw61NuclearScatteringDistributionCM;  
    
  // Grab the number of incoming energies
  int num_incoming_energies = incoming_energies.size();
  
  // Initialize the energy distribution array
  AceLaw4NuclearScatteringEnergyDistribution::EnergyDistribution 
    energy_distribution( num_incoming_energies ); 
    
  if( is_continuous_energy )
  {
    // Construct equiprobable distribution
    std::vector<double> eq_pdf_vec;
    for( int eq = 0; eq < 20; ++eq )
    {
      eq_pdf_vec.push_back( 1.0 );
    }

    // Initialize the Angle distribution array
    typename AceLaw61NuclearScatteringDistributionCM::AngleDistributions 
      angle_distribution( num_incoming_energies );
      
    for( int i = 0; i < num_incoming_energies; ++i )
    {
      energy_distribution[i].first = incoming_energies[i];
    
      int location = inelastic_locations[i] - inelastic_locations[0];
      int num_energies = outgoing_energies[i];
      
      std::vector<double> energy_grid_vec;
      std::vector<double> energy_pdf_vec;
      
      // Array of angular distributions
      std::vector< std::shared_ptr<const Utility::UnivariateDistribution> > 
        cosine_arrays( num_energies );
      
      for( int j = 0; j < num_energies; ++j )
      {
        // Grab the outgoing energy point and associated pdf point
        energy_grid_vec.push_back( itxe_block_array[location] );
        energy_pdf_vec.push_back( itxe_block_array[location + 1] );

        // Found situation in lwtr.20t -> line 131677 where there are nonphysical
        //  cosines (i.e. cosines > 1 and out of order...). How is this possible?
        //  Reaching out to J. Conlin to attempt to find more information...
        
        
        //  what we are doing is: 
        //        Utility::ArrayView<double> cosines = itxe_block_array( location + 3, 20 );
        // but gcc is not happy with the ArrayView<const double> to ArrayView<double> conversion...
        Utility::ArrayView<double> cosines;
        for (int i = 0; i < 20; i++) {
          int extract_tart_position = location + 3;
          cosines[i] = itxe_block_array[extract_tart_position+i];
        }
        // done with the itxe_block_array extraction

        if( itxe_block_array[location + 1] <= 1e-12 )
        {
          // Construct a false outgoing bin for incredibly unlikely result...
          for( int c = 0; c < 20; ++c )
          {
            cosines[c] = c*(2.0/19.0) - 1;
          }
        }
        
        if( cosines[19] > 1.0 )
        {
          cosines[19] = 1.0;
        }
        
        if( !Utility::Sort::isSortedAscending( cosines.begin(), cosines.end() ) )
        {
          std::sort( cosines.begin(), cosines.end() );
        }

        location += 23;

        // Construct the equiprobable angular distribution
        cosine_arrays[j].reset( 
          new Utility::DiscreteDistribution( cosines, eq_pdf_vec, false, false ) );
      }

    energy_distribution[i].second.reset( 
      new Utility::TabularDistribution<Utility::LinLin>( 
                                                    energy_grid_vec,
                                                    energy_pdf_vec ) );

    angle_distribution[i].reset( 
      new StandardAceLaw61AngleDistribution<AceLaw61LinLinInterpolationPolicy>(
                                                      Utility::ArrayView<const double>(energy_grid_vec),
                                                      cosine_arrays ) );

    }

    std::shared_ptr<NuclearScatteringEnergyDistribution> energy_out_distribution; 

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
  else
  {

    // Construct equiprobable distribution
    std::vector<double> eq_pdf_nrg_vec;
    for( int eq = 0; eq < 64; ++eq )
    {
      eq_pdf_nrg_vec.push_back( 1.0 );
    }

    std::vector<double> eq_pdf_nrg_ang_vec;
    for( int eq = 0; eq < 16; ++eq )
    {
      eq_pdf_nrg_ang_vec.push_back( 1.0 );
    }

    // Initialize the Angle distribution array
    typename AceLaw61NuclearScatteringDistributionCM::AngleDistributions 
      angle_distribution( num_incoming_energies );
      
    int location = 0;
    int num_energies = 64;

    for( int i = 0; i < num_incoming_energies; ++i )
    {
      energy_distribution[i].first = incoming_energies[i];
    
      std::vector<double> energy_grid_vec;
    
      // Array of angular distributions
      std::vector< std::shared_ptr<const Utility::UnivariateDistribution> > 
        cosine_arrays( num_energies );
      
      for( int j = 0; j < num_energies; ++j )
      {
        // Grab the outgoing energy point and associated pdf point
        energy_grid_vec.push_back( itxe_block_array[location] );

       //  what we are doing is: 
        //        Utility::ArrayView<double> cosines = itxe_block_array( location + 1, 16  );
        // but gcc is not happy with the ArrayView<const double> to ArrayView<double> conversion...
        Utility::ArrayView<double> cosines;
        for (int i = 0; i < 16; i++) {
          int extract_tart_position = location + 1;
          cosines[i] = itxe_block_array[extract_tart_position+i];
        }
        // done with the itxe_block_array extraction



        if( !Utility::Sort::isSortedAscending( cosines.begin(), cosines.end() ) )
        {
          std::sort( cosines.begin(), cosines.end() );
        }

        location += 17;

        // Construct the equiprobable angular distribution
        cosine_arrays[j].reset( 
          new Utility::DiscreteDistribution( cosines, eq_pdf_nrg_ang_vec, false, false) );
      }

    energy_distribution[i].second.reset( 
      new Utility::DiscreteDistribution( energy_grid_vec,
                                         eq_pdf_nrg_vec, false, false ) );

    angle_distribution[i].reset( 
      new StandardAceLaw61AngleDistribution<AceLaw61DiscreteInterpolationPolicy>(
                                                      Utility::ArrayView<const double>(energy_grid_vec),
                                                      cosine_arrays ) );
    }

    std::shared_ptr<NuclearScatteringEnergyDistribution> energy_out_distribution; 

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
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearScatteringEnergyDistributionACEFactory_def.hpp
//---------------------------------------------------------------------------//
