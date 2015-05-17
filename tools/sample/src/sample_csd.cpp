//---------------------------------------------------------------------------//
//!
//! \file   sample_csd.cpp
//! \author Alex Robinson
//! \brief  sample coherent scattering distribution tool
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
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_CoherentScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_CoherentScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_PhotoatomFactory.hpp"
#include "MonteCarlo_CrossSectionsXMLProperties.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_ArrayString.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "samplePhotonDistributionCore.hpp"

//! Main function for the sample_csd (Coherent Scattering Dist.) tool
int main( int argc, char** argv )
{
  Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  // Set up the command line options
  Teuchos::CommandLineProcessor sample_csd_clp;

  // The output file names
  std::string sample_output_file( "samples.txt" );
  std::string dist_output_file( "dist.txt" );

  // The number of samples
  int samples;
  
  // The cross section alias for scattering distributions
  std::string cross_section_alias;

  // The cross section directory
  std::string cross_section_directory;

  // The energy range
  std::string energy_range;
  Teuchos::Array<double> energies;

  // The sampling distribution
  bool use_efficient_scheme = true;

  // The number of threads
  int threads = 1;
  
  sample_csd_clp.setDocString( "sample from a distribution and output "
			       "the results\n" );
  sample_csd_clp.setOption( "s",
			    &samples,
			    "The number of samples",
			    true );
  sample_csd_clp.setOption( "cs",
			    &cross_section_alias,
			    "The photon cross section table alias. If no "
			    "alias is specified the Klein-Nishina "
			    "distribution will be used." );
  sample_csd_clp.setOption( "cs_dir",
			    &cross_section_directory,
			    "The directory containing the desired "
			    "cross section tables",
			    true );
  sample_csd_clp.setOption( "e",
			    &energy_range,
			    "The initial photon energy (or energy range "
			    "\"{e0,e1,...,en})\"",
			    true );
  sample_csd_clp.setOption( "use_efficient_scheme",
			    "use_basic_scheme",
			    &use_efficient_scheme,
			    "Use the efficient sampling scheme?" );
  sample_csd_clp.setOption( "sofile",
			    &sample_output_file,
			    "The output file where the samples will be"
			    " output" );
  sample_csd_clp.setOption( "dofile",
			    &dist_output_file,
			    "The output file where the distribution "
			    "pdf will be output" );
  sample_csd_clp.setOption( "threads",
                            &threads,
                            "Number of parallel threads" );

  sample_csd_clp.throwExceptions( false );
  
  // Parse the command line
  Teuchos::CommandLineProcessor::EParseCommandLineReturn
    parse_return = sample_csd_clp.parse( argc, argv );

  if( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL )
  {
    sample_csd_clp.printHelpMessage( argv[0], *out );

    return parse_return;
  }

  // Set up the global OpenMP session
  if( Utility::GlobalOpenMPSession::isOpenMPUsed() )
    Utility::GlobalOpenMPSession::setNumberOfThreads( threads );
  
  // Extract the energy (range)
  if( energy_range.find( "{" ) >= energy_range.size() &&
      energy_range.find( "}" ) >= energy_range.size() )
  {
    std::istringstream iss( energy_range );
    
    energies.resize( 1 );
    iss >> energies[0];
  }
  else
  {
    Utility::ArrayString array_string( energy_range );

    energies = array_string.getConcreteArray<double>();
  }

  // Create the coherent scattering distribution
  Teuchos::RCP<const MonteCarlo::CoherentScatteringDistribution>
    scattering_dist;

  if( cross_section_alias.size() > 0 )
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

      if( use_efficient_scheme )
      {
	MonteCarlo::CoherentScatteringDistributionACEFactory::createEfficientCoherentDistribution(
							    xss_data_extractor,
							    scattering_dist );
      }
      else
      {
	MonteCarlo::CoherentScatteringDistributionACEFactory::createBasicCoherentDistribution(
							    xss_data_extractor,
							    scattering_dist );
      }
    }
    else if( photoatom_file_type == MonteCarlo::CrossSectionsXMLProperties::native_file )
    {
      std::cerr << "Loading native photoatomic cross section table "
		<< photoatom_table_name << " ... ";

      // Create the epr data container
      Data::ElectronPhotonRelaxationDataContainer 
	data_container( photoatom_file_path );

      std::cerr << "done." << std::endl;

      if( use_efficient_scheme )
      {
	MonteCarlo::CoherentScatteringDistributionNativeFactory::createEfficientCoherentDistribution(
							    data_container,
							    scattering_dist );
      }
      else
      {
	MonteCarlo::CoherentScatteringDistributionNativeFactory::createBasicCoherentDistribution(
							    data_container,
							    scattering_dist );
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
  // Create a Thompson distribution
  else
  {
    MonteCarlo::CoherentScatteringDistributionACEFactory::createThompsonDistribution(
							     scattering_dist );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();

  // Initialize the output files
  Teuchos::RCP<std::ofstream> sofile, dofile;

  if( energies.size() == 1 )
  {
    sofile.reset( new std::ofstream( sample_output_file.c_str() ) );
    dofile.reset( new std::ofstream( dist_output_file.c_str() ) );
    
    sofile->precision( 18 );
    dofile->precision( 18 );
  }
  else
  {
    std::cerr << "Note: the samples and pdf will not be printed because "
	      << "multiple energies have been requested."
	      << std::endl;
  }

  // Populate the evaluation cosines array
  Teuchos::Array<double> pdf_evaluation_cosines( 3001 );

  #pragma omp parallel for num_threads( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() )
  for( unsigned i = 0; i < 1000; ++i )
    pdf_evaluation_cosines[i] = -1.0 + 0.1*i/1e3;

  #pragma omp parallel for num_threads( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() )
  for( unsigned i = 0; i < 1000; ++i )
    pdf_evaluation_cosines[i+1000] = -0.9 + 1.8*i/1e3;
      
  #pragma omp parallel for num_threads( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() )
  for( unsigned i = 0; i <= 1000; ++i )
    pdf_evaluation_cosines[i+2000] = 0.9 + 0.1*i/1e3;

  // Generate the samples
  Teuchos::RCP<const MonteCarlo::PhotonScatteringDistribution> 
    base_scattering_dist =
    Teuchos::rcp_dynamic_cast<const MonteCarlo::PhotonScatteringDistribution>( 
							     scattering_dist );
  return samplePhotonDistributionCore( base_scattering_dist,
                                       energies,
                                       samples,
                                       pdf_evaluation_cosines,
                                       sofile,
                                       dofile );
}

//---------------------------------------------------------------------------//
// end sample_csd.cpp
//---------------------------------------------------------------------------//
