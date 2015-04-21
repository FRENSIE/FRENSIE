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
  Teuchos::RCP<MonteCarlo::IncoherentPhotonScatteringDistribution> 
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

    Teuchos::RCP<MonteCarlo::PhotoatomicReaction> incoherent_reaction_base = 
      core.getScatteringReactions().find(
		   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION )->second;

    Teuchos::RCP<MonteCarlo::IncoherentPhotoatomicReaction> 
      incoherent_reaction = 
      Teuchos::rcp_dynamic_cast<MonteCarlo::IncoherentPhotoatomicReaction>(
						    incoherent_reaction_base );

    scattering_dist = incoherent_reaction->getScatteringDistribution();
  }

  

  return 0;
}

//---------------------------------------------------------------------------//
// end sample_isd.cpp 
//---------------------------------------------------------------------------//
