//---------------------------------------------------------------------------//
//!
//! \file   samplePhotonDistributionCore.cpp
//! \author Alex Robinson
//! \brief  function def. for generating samples from a photon distribution
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_GlobalOpenMPSession.hpp"
#include "samplePhotonDistributionCore.hpp"

int samplePhotonDistributionCore(
            const Teuchos::RCP<const MonteCarlo::PhotonScatteringDistribution>&
	    scattering_dist,
	    const Teuchos::Array<double>& energies,
	    const int samples,
	    const Teuchos::Array<double>& pdf_evaluation_cosines,
	    Teuchos::RCP<std::ofstream>& sample_ofile,
	    Teuchos::RCP<std::ofstream>& dist_ofile )
{
  std::cout << "# Energy Efficiency Timing" << std::endl;
  
  for( unsigned i = 0; i < energies.size(); ++i )
  {
    // Make the requested number of samples
    std::vector<unsigned> trials( 
	     Utility::GlobalOpenMPSession::getRequestedNumberOfThreads(), 0u );
    std::vector<double> sampled_cosines( samples ), sampled_energies( samples);
    std::vector<MonteCarlo::SubshellType> sampled_subshells( samples );
  
    double start_time = Utility::GlobalOpenMPSession::getTime();
    
    #pragma omp parallel for num_threads( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() )
    for( unsigned j = 0; j < samples; ++j )
    {
      scattering_dist->sampleAndRecordTrials( 
                         energies[i],
			 sampled_energies[j],
			 sampled_cosines[j],
			 sampled_subshells[j],
                         trials[Utility::GlobalOpenMPSession::getThreadId()] );
    }
  
    double end_time = Utility::GlobalOpenMPSession::getTime();

    // Do a reduction on the trials array
    unsigned total_trials = 0u;
    
    for( unsigned j = 0; j < trials.size(); ++j )
      total_trials += trials[j];
  
    // Print the efficiency and timing data
    std::cout.precision( 18 );
    std::cout << energies[i] << " " 
	      << samples/(double)total_trials << " "
	      << end_time - start_time << std::endl;

    if( !sample_ofile.is_null() )
    {
      for( unsigned j = 0; j < samples; ++j )
	(*sample_ofile) << sampled_cosines[j] << std::endl;
    }
    
    if( !dist_ofile.is_null() )
    {
      std::vector<double> pdf_values( pdf_evaluation_cosines.size() );

      // Evaluate the distribution in the smooth region (-1,0.9)
      #pragma omp parallel for num_threads( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() )
      for( unsigned j = 0; j < pdf_values.size(); ++j )
      {
	pdf_values[j] = 
	  scattering_dist->evaluatePDF(energies[i], pdf_evaluation_cosines[j]);
      }

      // Print the pdf values
      for( unsigned j = 0; j < pdf_values.size(); ++j )
      {
	(*dist_ofile) << pdf_evaluation_cosines[j] << " "
		      << pdf_values[j]
		      << std::endl;
      }
    }
  }

  return 0;
}
				 
//---------------------------------------------------------------------------//
// end samplePhotonDistributionCore.cpp
//---------------------------------------------------------------------------//

