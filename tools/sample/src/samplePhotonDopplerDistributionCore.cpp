//---------------------------------------------------------------------------//
//!
//! \file   samplePhotonDopplerDistributionCore.cpp
//! \author Alex Robinson
//! \brief  function defs. for generating samples from a Doppler broadened
//!         photon energy distribution
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "samplePhotonDopplerDistributionCore.hpp"
#include "MonteCarlo_DopplerBroadenedPhotonEnergyDistributionACEFactory.hpp"
#include "MonteCarlo_DopplerBroadenedPhotonEnergyDistributionNativeFactory.hpp"
#include "MonteCarlo_SubshellType.hpp"
#include "MonteCarlo_PhotonKinematicsHelpers.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_ExceptionTestMacros.hpp"

// Initialize the Doppler broadened photon energy distribution
void initializeACEDistribution( 
                             const Data::XSSEPRDataExtractor& data_extractor,
                             const int model_type,
                             const int raw_subshell,
                             std::shared_ptr<const MonteCarlo::DopplerBroadenedPhotonEnergyDistribution>& doppler_dist )
{
  switch( model_type )
  {
    // Half Decoupled-Complete
    case 0:
    {
      MonteCarlo::DopplerBroadenedPhotonEnergyDistributionACEFactory::createDecoupledCompleteDistribution( 
                                                         data_extractor,
                                                         doppler_dist,
                                                         false );
      break;        
    }
    // Full Decoupled-Complete
    case 1:
    {
      MonteCarlo::DopplerBroadenedPhotonEnergyDistributionACEFactory::createDecoupledCompleteDistribution( 
                                                         data_extractor,
                                                         doppler_dist,
                                                         true );
      
      break;
    }
    // Half Coupled-Complete
    case 2:
    {
      MonteCarlo::DopplerBroadenedPhotonEnergyDistributionACEFactory::createCoupledCompleteDistribution( 
                                                         data_extractor,
                                                         doppler_dist,
                                                         false );
      
      break;
    }
    // Full Coupled-Complete
    case 3:
    {
      MonteCarlo::DopplerBroadenedPhotonEnergyDistributionACEFactory::createCoupledCompleteDistribution( 
                                                         data_extractor,
                                                         doppler_dist,
                                                         true );
      
      break;
    }
    // Full Subshell
    case 4:
    {
      MonteCarlo::SubshellType subshell = 
        MonteCarlo::convertENDFDesignatorToSubshellEnum( raw_subshell );
      
      MonteCarlo::DopplerBroadenedPhotonEnergyDistributionACEFactory::createSubshellDistribution( 
                                                            data_extractor,
                                                            subshell,
                                                            doppler_dist,
                                                            true );
      
      break;
    }
    // Invalid model
    default:
    {
      THROW_EXCEPTION( std::runtime_error,
                       "Error: model " << model_type << " is invalid (see "
                       "help message)!" );
    }                   
  }
}

// Initialize the Doppler broadened photon energy distribution
void initializeNativeDistribution( 
             const Data::ElectronPhotonRelaxationDataContainer& data_container,
             const int model_type,
             const int raw_subshell,
             std::shared_ptr<const MonteCarlo::DopplerBroadenedPhotonEnergyDistribution>& doppler_dist )
{
  switch( model_type )
  {
    // Half Decoupled-Complete
    case 0:
    {
      THROW_EXCEPTION( std::runtime_error,
                       "Error: model " << model_type << " is not supported "
                       "with native data files! " );
    }
    // Full Decoupled-Complete
    case 1:
    {
      THROW_EXCEPTION( std::runtime_error,
                       "Error: model " << model_type << " is not supported "
                       "with native data files! " );
    }
    // Half Coupled-Complete
    case 2:
    {
      THROW_EXCEPTION( std::runtime_error,
                       "Error: model " << model_type << " is not supported "
                       "with native data files! " );
    }
    // Full Coupled-Complete
    case 3:
    {
      MonteCarlo::DopplerBroadenedPhotonEnergyDistributionNativeFactory::createCoupledCompleteDistribution( 
                                                         data_container,
                                                         doppler_dist );
      
      break;
    }
    // Full Subshell
    case 4:
    {
      MonteCarlo::SubshellType subshell = 
        MonteCarlo::convertENDFDesignatorToSubshellEnum( raw_subshell );
      
      MonteCarlo::DopplerBroadenedPhotonEnergyDistributionNativeFactory::createSubshellDistribution( 
                                                            data_container,
                                                            subshell,
                                                            doppler_dist );
      
      break;
    }
    // Invalid model
    default:
    {
      THROW_EXCEPTION( std::runtime_error,
                       "Error: model " << model_type << " is invalid (see "
                       "help message)!" );
    }                   
  }
}

// Generate the samples from the desired distribution
int samplePhotonDopplerDistributionCore(
         const std::shared_ptr<const MonteCarlo::DopplerBroadenedPhotonEnergyDistribution>&
         doppler_dist,
         const double incoming_energy,
         const double scattering_angle_cosine,
         const int raw_subshell,
         const int model_type,
         const int num_samples,
         Teuchos::Array<double>& pdf_evaluation_energies,
         std::shared_ptr<std::ofstream>& sample_ofile,
         std::shared_ptr<std::ofstream>& dist_ofile )
{
  std::cout << "# Energy Mu Efficiency Timing" << std::endl;
  std::cout.precision( 18 );
  std::cout << incoming_energy << " " 
            << scattering_angle_cosine << " ";

  // The pdf values
  Teuchos::Array<double> pdf_values( pdf_evaluation_energies.size() );

  // The samples
  Teuchos::Array<double> samples( num_samples );

  // The trials
  unsigned trials = 0;

  // The start and end times
  double start_time, end_time;

  // Subshell from a complete distribution
  if( model_type != 4 && raw_subshell > -1 )
  {
    std::shared_ptr<const MonteCarlo::CompleteDopplerBroadenedPhotonEnergyDistribution>
      complete_doppler_dist = std::dynamic_pointer_cast<const MonteCarlo::CompleteDopplerBroadenedPhotonEnergyDistribution>( doppler_dist );

    MonteCarlo::SubshellType subshell = 
        MonteCarlo::convertENDFDesignatorToSubshellEnum( raw_subshell );
    
    // Evaluate the pdf
    for( unsigned i = 0; i < pdf_values.size(); ++i )
    {
      pdf_values[i] = 
        complete_doppler_dist->evaluateSubshellPDF( incoming_energy,
                                                    pdf_evaluation_energies[i],
                                                    scattering_angle_cosine,
                                                    subshell );
      
    }

    // Start the timer
    start_time = Utility::GlobalOpenMPSession::getTime();
    
    // Generate the samples
    for( unsigned i = 0; i < num_samples; ++i )
    {
      samples[i] = 
        complete_doppler_dist->sampleSubshellMomentum( incoming_energy,
                                                       scattering_angle_cosine,
                                                       subshell );
      // Manually increment the trials
      ++trials;
    }

    // End the timer
    end_time = Utility::GlobalOpenMPSession::getTime();
  }
  // Complete distribution
  else
  {
    // Evaluate the pdf
    for( unsigned i = 0; i < pdf_values.size(); ++i )
    {
      pdf_values[i] = 
        doppler_dist->evaluatePDF( incoming_energy,
                                   pdf_evaluation_energies[i],
                                   scattering_angle_cosine );
    }

    // Start the timer
    start_time = Utility::GlobalOpenMPSession::getTime();

    // Generate the samples
    for( unsigned i = 0; i < num_samples; ++i )
    {
      MonteCarlo::SubshellType sampled_subshell;
      
      doppler_dist->sampleMomentumAndRecordTrials( incoming_energy,
                                                   scattering_angle_cosine,
                                                   samples[i],
                                                   sampled_subshell,
                                                   trials );
    }

    // Stop the timer
    end_time = Utility::GlobalOpenMPSession::getTime();
  }
  
  // Print the efficiency and timing data
  std::cout.precision( 18 );
  std::cout << num_samples/(double)trials << " "
            << end_time - start_time << std::endl;

  // Output the generated data
  if( sample_ofile.get() )
  {
    for( unsigned i = 0; i < num_samples; ++i )
    {
      bool possible;
      double outgoing_energy = 
        MonteCarlo::calculateDopplerBroadenedEnergy( samples[i],
                                                     incoming_energy,
                                                     scattering_angle_cosine,
                                                     possible );
                                                     
      (*sample_ofile) << samples[i] << " "
                      << outgoing_energy << std::endl;
    }
  }
  
  if( dist_ofile.get() )
  {
    for( unsigned i = 0; i < pdf_values.size(); ++i )
    {
      double pz = MonteCarlo::calculateElectronMomentumProjection( 
                                                    incoming_energy,
                                                    pdf_evaluation_energies[i],
                                                    scattering_angle_cosine );
      
      (*dist_ofile) << incoming_energy << " "
                    << scattering_angle_cosine << " "
                    << pdf_evaluation_energies[i] << " "
                    << pz << " "
                    << pdf_values[i] << std::endl;
    }
  }

  return 0;
}

//---------------------------------------------------------------------------//
// end samplePhotonDopplerDistributionCore.cpp
//---------------------------------------------------------------------------//
