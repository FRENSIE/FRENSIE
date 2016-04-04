//---------------------------------------------------------------------------//
//!
//! \file   sample_pdopp.cpp
//! \author Alex Robinson
//! \brief  sample Doppler broadened photon energy distribution tool
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>

// Boost Includes
#include <boost/unordered_set.hpp>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_CommandLineProcessor.hpp>
#include <Teuchos_FancyOStream.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "samplePhotonDopplerDistributionCore.hpp"
#include "MonteCarlo_DopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_CrossSectionsXMLProperties.hpp"
#include "MonteCarlo_SimulationPhotonProperties.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_ArrayString.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

//! Main funciton for the sample_pdopp (Doppler Broadened Photon Erg.) tool
int main( int argc, char** argv )
{
  Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  // Set up the command line options
  Teuchos::CommandLineProcessor sample_pdopp_clp;

  // The output file names
  std::string sample_output_file( "samples.txt" );
  std::string dist_output_file( "dist.txt" );

  // The number of samples
  int samples;

  // The cross section alias for scattering distributions
  std::string cross_section_alias;

  // The cross section directory
  std::string cross_section_directory;

  // The initial energy
  double initial_energy;

  // The scattering angle cosine
  double scattering_angle_cosine;

  // The subshell
  int subshell = -1;

  // The Doppler broadening model
  int model_type = 0;

  // The number of threads
  int threads = 1;

  // Set up the command-line processor
  sample_pdopp_clp.setDocString( "sample from a Doppler broadened photon "
                                 "energy distribution and output the "
                                 "results\n" );
  sample_pdopp_clp.setOption( "s",
                              &samples,
                              "The number of samples",
                              true );
  sample_pdopp_clp.setOption( "cs",
                              &cross_section_alias,
                              "The photon cross section table alias.",
                              true );
  sample_pdopp_clp.setOption( "cs_dir",
                              &cross_section_directory,
                              "The directory containing the desired "
                              "cros section tables",
                              true );
  sample_pdopp_clp.setOption( "e",
                              &initial_energy,
                              "The initial photon energy (MeV)",
                              true );
  sample_pdopp_clp.setOption( "u",
                              &scattering_angle_cosine,
                              "The initial angle cosine [-1,1]",
                              true );
  sample_pdopp_clp.setOption( "model",
                              &model_type,
                              "The model of interest. If the subshell model "
                              "is selected a subshell must also be selected \n"
                              "\t 0 = Half Decoupled-Complete \n"
                              "\t 1 = Full Decoupled-Complete \n"
                              "\t 2 = Half Coupled-Complete \n"
                              "\t 3 = Full Coupled-Complete \n"
                              "\t 4 = Full Subshell \n" );
  sample_pdopp_clp.setOption( "subshell",
                              &subshell,
                              "The (endf) subshell of interest "
                              "(-1 = all subshells)" );
  sample_pdopp_clp.setOption( "sofile",
                              &sample_output_file,
                              "The file where the samples will be output" );
  sample_pdopp_clp.setOption( "dofile",
                              &dist_output_file,
                              "The file where the distribution pdf will be "
                              "output" );
  // sample_pdopp_clp.setOption( "threads",
  //                            &threads,
  //                            "The number of parallel threads" );

  sample_pdopp_clp.throwExceptions( false );

  // Parse the command line
  Teuchos::CommandLineProcessor::EParseCommandLineReturn
    parse_return = sample_pdopp_clp.parse( argc, argv );

  if( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL )
  {
    sample_pdopp_clp.printHelpMessage( argv[0], *out );

    return parse_return;
  }

  // Check if the initial energy is valid
  if( initial_energy <= 0.0 )
  {
    std::cerr << "Error: the energy (" << initial_energy << ") "
              << "must be greater than 0.0!" << std::endl;

    return 1;
  }

  // Check if the scattering angle cosine is valid
  if( scattering_angle_cosine < -1.0 || scattering_angle_cosine > 1.0 )
  {
    std::cerr << "Error: the scattering angle cosine (" 
              << scattering_angle_cosine << ") "
              << "must be in [-1,1]!" << std::endl;
  }

  // Create the Doppler broadened photon energy distribution
  std::shared_ptr<const MonteCarlo::DopplerBroadenedPhotonEnergyDistribution>
    doppler_dist;

  if( cross_section_alias.size() > 0 )
  {
    boost::unordered_set<std::string> photoatom_aliases;
    photoatom_aliases.insert( cross_section_alias );

    // Open the cross_section.xml file
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

      try{
        initializeACEDistribution( xss_data_extractor,
                                   model_type,
                                   subshell,
                                   doppler_dist );
      }
      EXCEPTION_CATCH_AND_EXIT( std::runtime_error,
                                "Could not create the desired distribution!" );
    }
    else if( photoatom_file_type == MonteCarlo::CrossSectionsXMLProperties::native_file )
    {
      std::cerr << "Load native photoatomic cross section table "
                << photoatom_table_name << " ... ";

      // Create the epr data container
      Data::ElectronPhotonRelaxationDataContainer
        data_container( photoatom_file_path );

      std::cerr << "done." << std::endl;

      try{
        initializeNativeDistribution( data_container,
                                      model_type,
                                      subshell,
                                      doppler_dist );
      }
      EXCEPTION_CATCH_AND_EXIT( std::runtime_error,
                                "Could not create the desired distribution!" );
    }
    else
    {
      std::cerr << "Error: photoatomic file type " << photoatom_file_type
                << " is not supported!" << std::endl;
                
      return 1;
    }
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();

  // Initialize the output files
  std::shared_ptr<std::ofstream> sofile, dofile;

  sofile.reset( new std::ofstream( sample_output_file.c_str() ) );
  dofile.reset( new std::ofstream( dist_output_file.c_str() ) );

  sofile->precision( 18 );
  dofile->precision( 18 );

  // Populate the evaluation electron momentum array
  Teuchos::Array<double> pdf_evaluation_energies( 2001 );

  for( unsigned i = 0; i < 2001; ++i )
    pdf_evaluation_energies[i] = 0.0 + initial_energy*i/2000.0;
  
  // Generate the samples
  return samplePhotonDopplerDistributionCore( doppler_dist,
                                              initial_energy,
                                              scattering_angle_cosine,
                                              subshell,
                                              model_type,
                                              samples,
                                              pdf_evaluation_energies,
                                              sofile,
                                              dofile );
}

//---------------------------------------------------------------------------//
// end sample_pdopp.cpp
//---------------------------------------------------------------------------//
