//---------------------------------------------------------------------------//
//!
//! \file   sample_isd.cpp
//! \author Alex Robinson
//! \brief  sample incoherent scattering distribution tool
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <fstream>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_CommandLineProcessor.hpp>
#include <Teuchos_FancyOStream.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_IncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_PhotoatomFactory.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

int main( int argc, char** argv )
{
  Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  // Set up the command line options
  Teuchos::CommandLineProcessor sample_isd_clp;

  // The output file names
  std::string sample_output_file( "samples.txt" );
  std::string dist_output_file( "dist.txt" );

  // The number of samples
  unsigned samples;
  
  // The cross section alias for scattering distributions
  std::string cross_section_alias;

  // The cross section directory
  std::string cross_section_directory;

  // The initial photon energy
  double initial_photon_energy;

  // Use the impulse approximation
  bool use_impulse_approx = false;

  sample_isd_clp.setDocString( "sample from a distribution and output the"
			       "results\n" );
  sample_isd_clp.setOption( "s",
			    &samples,
			    "The number of samples",
			    true );
  sample_isd_clp.setOption( "cs",
			    &cross_section_alias,
			    "The photon cross section table alias",
			    true );
  sample_isd_clp.setOption( "cs_dir",
			    &cross_section_directory,
			    "The directory containing the desired cross "
			    "section tables",
			    true );
  sample_isd_clp.setOption( "e",
			    &initial_photon_energy,
			    "The initial photon energy",
			    true );
  sample_isd_clp.setOption( "sofile",
			    &sample_output_file,
			    "The output file where the samples will be "
			    "output" );
  sample_isd_clp.setOption( "dofile",
			    &dist_output_file,
			    "The output file where the distribution pdf will "
			    "be output" );
  // sample_isd_clp.setOption( "impulse_approx",
  // 			    "waller_hartree",
  // 			    &use_impulse_approx,
  // 			    "Use the impulse approximation?" );
  
  // Parse the command line
  Teuchos::CommandLineProcessor::EParseCommandLineReturn
    parse_return = sample_isd_clp.parse( argc, argv );

  if( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL )
  {
    sample_isd_clp.printHelpMessage( argv[0], *out );

    return parse_return;
  }

  // Create the incoherent scattering distribution
  Teuchos::RCP<const MonteCarlo::IncoherentPhotonScatteringDistribution> 
    scattering_dist;
  
  {
    boost::unordered_set<std::string> photoatom_aliases;
    photoatom_aliases.insert( cross_section_alias );

    // Open the cross_sections.xml file
    std::string cross_sections_xml_file = cross_section_directory;
    cross_sections_xml_file += "/cross_sections.xml";
    
    Teuchos::RCP<Teuchos::ParameterList> cross_sections_table_info = 
      Teuchos::getParametersFromXmlFile( cross_sections_xml_file );
    
    Teuchos::RCP<MonteCarlo::AtomicRelaxationFactory> relax_factory;

    MonteCarlo::PhotoatomFactory factory( cross_sections_xml_directory,
					  cross_sections_table_info,
					  photoatom_aliases,
					  relax_factory,
					  1,
					  use_impulse_approx,
					  false,
					  false,
					  false );

    boost::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Photoatom> >
      photoatom_map;

    factory.createPhotoatomMap( photoatom_map );

    MonteCarlo::PhotoatomCore core( photoatom_map.begin()->second->getCore() );

    Teuchos::RCP<MonteCarlo::PhotoatomicReaction> incoherent_reaction = 
      core.getScatteringReactions().find(
		   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION )->second;

    // Make sure the total incoherent reaction is available
    TEST_FOR_EXCEPTION( incoherent_reaction.is_null(),
			std::logic_error,
			"Error: the incoherent reaction is not available!" );
    
    scattering_dist = incoherent_reaction->getScatteringDistribution();
  }

  // Make the requested number of samples
  unsigned trials = 0u;
  MonteCarlo::PhotonState photon( 0 );
  MonteCarlo::ParticleBank bank;
  MonteCarlo::SubshellType shell_of_interaction;
  std::vector<double> sampled_cosines( samples );
  double start_time, end_time;
  
  start_time = Utility::GlobalOpenMPSession::getTime();
  
  for( unsigned i = 0; i < samples; ++i )
  {
    photon.setEnergy( initial_photon_energy );
    photon.setDirection( 0.0, 0.0, 1.0 );

    scattering_dist->scatterPhoton(photon, bank, shell_of_interaction, trials);

    sampled_energies[i] = photon.getEnergy();
  }
  
  end_time = Utility::GlobalOpenMPSession::getTime();
  
  // Print the efficiency and timing data
  std::cout.precision( 18 );
  std::cout << "Photon Energy: " << initial_photon_energy << std::endl;
  std::cout << "Efficiency: " << samples/(double)trials << std::endl;
  std::cout << "Timing (" << samples << " samples): " 
	    << end_time - start_time << std::endl;

  // 

  return 0;
}

//---------------------------------------------------------------------------//
// end sample_isd.cpp 
//---------------------------------------------------------------------------//
