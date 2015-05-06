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
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_CommandLineProcessor.hpp>
#include <Teuchos_FancyOStream.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_IncoherentPhotonScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_IncoherentPhotonScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_PhotoatomFactory.hpp"
#include "MonteCarlo_CrossSectionsXMLProperties.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_RandomNumberGenerator.hpp"
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
  int samples;
  
  // The cross section alias for scattering distributions
  std::string cross_section_alias;

  // The cross section directory
  std::string cross_section_directory;

  // The initial photon energy
  double initial_photon_energy;

  // The energy range
  std::string energy_range;

  // The subshell
  int subshell = 0;

  sample_isd_clp.setDocString( "sample from a distribution and output "
			       "the results\n" );
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
			    "The directory containing the desired "
			    "cross section tables",
			    true );
  sample_isd_clp.setOption( "e",
			    &initial_photon_energy,
			    "The initial photon energy",
			    true );
  // sampe_isd_clp.setOption( "energies",
  // 				   &energies,
  // 				   "The energies that will be used to "
  // 				   "calculate efficiencies" );
  sample_isd_clp.setOption( "subshell",
			    &subshell,
			    "The subshell of interest" );
  sample_isd_clp.setOption( "sofile",
			    &sample_output_file,
			    "The output file where the samples will be"
			    " output" );
  sample_isd_clp.setOption( "dofile",
			    &dist_output_file,
			    "The output file where the distribution "
			    "pdf will be output" );

  sample_isd_clp.throwExceptions( false );
  
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
    
    std::string photoatom_file_path, photoatom_file_type, photoatom_table_name;
    int photoatom_file_start_line;
    double atomic_weight;

    MonteCarlo::CrossSectionsXMLProperties::extractInfoFromPhotoatomTableInfoParameterList(
						  cross_section_directory,
						  cross_section_alias,
						  *cross_sections_table_info,
						  photoatom_file_path,
						  photoatom_file_type,
						  photoatom_table_name,
						  photoatom_file_start_line,
						  atomic_weight );

    if( photoatom_file_type == MonteCarlo::CrossSectionsXMLProperties::ace_file )
    {
      std::cerr << "Loading ACE photoatomic cross section table "
		<< photoatom_table_name << " (" << cross_section_alias 
		<< ") ... ";

      if( subshell != 0 )
      {
	std::cerr << "Warning: impulse approximation data is not available in "
		  << photoatom_table_name << std::endl;
      }

      // Create the ACEFileHandler
      Data::ACEFileHandler ace_file_handler( photoatom_file_path,
					     photoatom_table_name,
					     photoatom_file_start_line,
					     true );
    
      // Create the XSS data extractor
      Data::XSSEPRDataExtractor xss_data_extractor( 
					 ace_file_handler.getTableNXSArray(),
					 ace_file_handler.getTableJXSArray(),
					 ace_file_handler.getTableXSSArray() );

      std::cerr << "done." << std::endl;

      MonteCarlo::IncoherentPhotonScatteringDistributionACEFactory::createIncoherentDistribution(
						            xss_data_extractor,
							    scattering_dist,
							    3.0 );
    }
    else if( photoatom_file_type == MonteCarlo::CrossSectionsXMLProperties::native_file )
    {
      std::cerr << "Loading native photoatomic cross section table "
		<< photoatom_table_name << " ... ";

      // Create the epr data container
      Data::ElectronPhotonRelaxationDataContainer 
	data_container( photoatom_file_path );

      std::cerr << "done." << std::endl;

      if( subshell == 0 )
      {
	MonteCarlo::IncoherentPhotonScatteringDistributionNativeFactory::createIncoherentDistribution(
							       data_container,
							       scattering_dist,
							       3.0 );
      }
      else if( data_container.getSubshells().count( subshell ) )
      {
	MonteCarlo::IncoherentPhotonScatteringDistributionNativeFactory::createSubshellIncoherentDistribution(
							       data_container,
							       subshell,
							       scattering_dist,
							       3.0 );
      }
      else
      {
	THROW_EXCEPTION( std::runtime_error,
			 "Error: the requested subshell ( " << subshell <<
			 ") does not exist!" );
      }
    }
    else
    {
      THROW_EXCEPTION( std::logic_error,
		       "Error: photoatomic file type " 
		       << photoatom_file_type <<
		       " is not supported!" );
    }
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();

  // Make the requested number of samples
  unsigned trials = 0u;
  std::vector<double> sampled_cosines( samples );
  double outgoing_energy, scattering_angle_cosine;
  MonteCarlo::SubshellType sampled_subshell;
  double start_time, end_time;
  
  start_time = Utility::GlobalOpenMPSession::getTime();
  
  for( unsigned i = 0; i < samples; ++i )
  {
    scattering_dist->sampleAndRecordTrials( initial_photon_energy,
					    outgoing_energy,
					    scattering_angle_cosine,
					    sampled_subshell,
					    trials );

    sampled_cosines[i] = scattering_angle_cosine;
  }
  
  end_time = Utility::GlobalOpenMPSession::getTime();
  
  // Print the efficiency and timing data
  std::cout << "# Energy Efficiency Timing" << std::endl;
  std::cout.precision( 18 );
  std::cout << initial_photon_energy << " " 
	    << samples/(double)trials << " "
	    << end_time - start_time << std::endl;

  // Output the sampled data
  std::ofstream sofile( sample_output_file.c_str() );
  std::ofstream dofile( dist_output_file.c_str() );
  
  sofile.precision( 18 );
  dofile.precision( 18 );

  for( unsigned i = 0; i < samples; ++i )
    sofile << sampled_cosines[i] << std::endl;
  
  for( unsigned i = 0; i < 1e3; ++i )
  {
    double scattering_angle_cosine = -1.0 + 1.9*i/1e3;
    
    dofile << scattering_angle_cosine << " "
	   << scattering_dist->evaluatePDF( initial_photon_energy,
					    scattering_angle_cosine )
	   << std::endl;
  }
  for( unsigned i = 0; i <= 1e3; ++i )
  {
    double scattering_angle_cosine = 0.9 + 0.1*i/1e3;

    dofile << scattering_angle_cosine << " "
	   << scattering_dist->evaluatePDF( initial_photon_energy,
					    scattering_angle_cosine )
	   << std::endl;
  }

  sofile.close();
  dofile.close();
  
  return 0;
}

//---------------------------------------------------------------------------//
// end sample_isd.cpp 
//---------------------------------------------------------------------------//
