//---------------------------------------------------------------------------//
//!
//! \file   epr_generator.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  epr_generator tool
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_CommandLineProcessor.hpp>
#include <Teuchos_FancyOStream.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "DataGen_StandardElectronPhotonRelaxationDataGenerator.hpp"
#include "MonteCarlo_CrossSectionsXMLProperties.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_ENDLFileHandler.hpp"
#include "Data_ENDLDataContainer.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Data_ElectronPhotonRelaxationVolatileDataContainer.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_GaussKronrodIntegrator.hpp"

int main( int argc, char** argv )
{
  Teuchos::RCP<const DataGen::ElectronPhotonRelaxationDataGenerator>
    epr_generator;

  Teuchos::RCP<Teuchos::FancyOStream> out =
    Teuchos::VerboseObjectBase::getDefaultOStream();

  // Set up the command line options
  Teuchos::CommandLineProcessor epr_generator_clp;

  std::string cross_section_directory, cross_section_alias;
  double min_photon_energy = 0.001, max_photon_energy = 20.0;
  double min_electron_energy = 0.00001, max_electron_energy = 100000.0;
  double occupation_number_evaluation_tol = 1e-3;
  double subshell_incoherent_evaluation_tol = 1e-3;
  double cutoff_angle_cosine = 0.999999;
  int number_of_moment_preserving_angles = 0;
  double grid_convergence_tol = 0.001;
  double grid_absolute_diff_tol = 1e-42;
  double grid_distance_tol = 1e-16;
  bool modify_cs_xml_file = false;

  epr_generator_clp.setDocString( "Electron-Photon-Relaxation Native Data File"
				  " Generator\n" );
  epr_generator_clp.setOption( "cross_sec_dir",
			       &cross_section_directory,
			       "Directory containing desired cross section "
			       "tables",
			       true );
  epr_generator_clp.setOption( "cross_sec_alias",
			       &cross_section_alias,
			       "Photon cross section table alias",
			       true );
  epr_generator_clp.setOption( "min_photon_energy",
			       &min_photon_energy,
			       "Min photon energy for table" );
  epr_generator_clp.setOption( "max_photon_energy",
			       &max_photon_energy,
			       "Max photon energy for table" );
  epr_generator_clp.setOption( "min_electron_energy",
			       &min_electron_energy,
			       "Min electron energy for table" );
  epr_generator_clp.setOption( "max_electron_energy",
			       &max_electron_energy,
			       "Max electron energy for table" );
  epr_generator_clp.setOption( "occupation_num_tol",
			       &occupation_number_evaluation_tol,
			       "Occupation number evaluation tolerance" );
  epr_generator_clp.setOption( "subshell_incoherent_tol",
			       &subshell_incoherent_evaluation_tol,
			       "Subshell incoherent evaluation tolerance" );
  epr_generator_clp.setOption( "cutoff_angle_cosine",
			       &cutoff_angle_cosine,
			       "Cutoff angle cosine for table" );
  epr_generator_clp.setOption( "number_of_moment_preserving_angles",
			       &number_of_moment_preserving_angles,
			       "Number of moment preserving angles for table" );
  epr_generator_clp.setOption( "grid_convergence_tol",
			       &grid_convergence_tol,
			       "Grid convergence tolerance" );
  epr_generator_clp.setOption( "grid_absolute_diff_tol",
			       &grid_absolute_diff_tol,
			       "Grid absolute difference tolerance" );
  epr_generator_clp.setOption( "grid_absolute_dist_tol",
			       &grid_distance_tol,
			       "Grid absolute distance tolerance" );
  epr_generator_clp.setOption( "modify_cs_xml_file",
			       "do_not_modify_cs_xml_file",
			       &modify_cs_xml_file,
			       "Modify the cross_sections.xml file?" );

  epr_generator_clp.throwExceptions( false );

  // Parse the command line
  Teuchos::CommandLineProcessor::EParseCommandLineReturn
    parse_return = epr_generator_clp.parse( argc, argv );

  if( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL )
  {
    epr_generator_clp.printHelpMessage( argv[0], *out );

    return parse_return;
  }

  // Open the cross_sections.xml file
  std::string cross_sections_xml_file = cross_section_directory;
  cross_sections_xml_file += "/cross_sections.xml";

  Teuchos::RCP<Teuchos::ParameterList> cross_sections_table_info =
    Teuchos::getParametersFromXmlFile( cross_sections_xml_file );

  std::string data_file_path, data_file_type, data_table_name;
  int data_file_start_line, atomic_number;
  double atomic_weight;

  MonteCarlo::CrossSectionsXMLProperties::extractInfoFromPhotoatomTableInfoParameterList(
						    cross_section_directory,
						    cross_section_alias,
						    *cross_sections_table_info,
						    data_file_path,
						    data_file_type,
						    data_table_name,
						    data_file_start_line,
						    atomic_weight );

  // Create the data generator
  if( data_file_type == "ACE" )
  {
    Data::ACEFileHandler ace_file_handler( data_file_path,
					   data_table_name,
					   data_file_start_line,
					   true );

    Teuchos::RCP<const Data::XSSEPRDataExtractor> ace_epr_extractor(
				new const Data::XSSEPRDataExtractor(
				       ace_file_handler.getTableNXSArray(),
				       ace_file_handler.getTableJXSArray(),
				       ace_file_handler.getTableXSSArray() ) );

    atomic_number = ace_epr_extractor->extractAtomicNumber();

    std::ostringstream oss;
    oss << "endl_" << atomic_number << "_native.xml";

    std::string endl_file_path = cross_section_directory;
    endl_file_path += "endldata/";
    endl_file_path += oss.str();
/*
    endl_file_path = "/home/software/mcnpdata/endldata/";
    endl_file_path += oss.str();
*/
std::cout << "endl_file_path = " << endl_file_path << std::endl;

    Teuchos::RCP<Data::ENDLDataContainer> endl_data_container(
        new Data::ENDLDataContainer(
            endl_file_path,
            Utility::ArchivableObject::XML_ARCHIVE ) );

    epr_generator.reset(
	    new const DataGen::StandardElectronPhotonRelaxationDataGenerator(
					    atomic_number,
					    ace_epr_extractor,
                        endl_data_container,
					    min_photon_energy,
					    max_photon_energy,
					    min_electron_energy,
					    max_electron_energy,
					    occupation_number_evaluation_tol,
                        subshell_incoherent_evaluation_tol,
                        cutoff_angle_cosine,
                        number_of_moment_preserving_angles,
					    grid_convergence_tol,
					    grid_absolute_diff_tol,
					    grid_distance_tol ) );
  }
  else
  {
    std::cerr << "Error: Photoatomic file type "
	      << data_file_type << "is not supported!";
  }

  // Create the new data container
  Data::ElectronPhotonRelaxationVolatileDataContainer data_container;

  epr_generator->populateEPRDataContainer( data_container );

  std::ostringstream oss;
  oss << "epr_" << atomic_number << "_native.xml";

  std::string new_file_name;

  // Export the generated data to an XML file
  if( modify_cs_xml_file )
  {
    new_file_name = cross_section_directory;
    new_file_name += "/";
    new_file_name += oss.str();

    std::string new_cross_section_alias( cross_section_alias );
    new_cross_section_alias += "-Native";

    Teuchos::ParameterList& old_table_info =
      cross_sections_table_info->sublist( cross_section_alias );

    Teuchos::ParameterList& new_table_info =
      cross_sections_table_info->sublist( new_cross_section_alias );

    new_table_info.setParameters( old_table_info );

    new_table_info.set(
	    MonteCarlo::CrossSectionsXMLProperties::photoatomic_file_path_prop,
	    oss.str() );
    new_table_info.set(
	    MonteCarlo::CrossSectionsXMLProperties::photoatomic_file_type_prop,
	    MonteCarlo::CrossSectionsXMLProperties::native_file );
    new_table_info.set(
      MonteCarlo::CrossSectionsXMLProperties::photoatomic_file_start_line_prop,
      -1 );
    new_table_info.set(
	   MonteCarlo::CrossSectionsXMLProperties::photoatomic_table_name_prop,
	   "" );

    new_table_info.set(
	    MonteCarlo::CrossSectionsXMLProperties::electroatomic_file_path_prop,
	    oss.str() );
    new_table_info.set(
	    MonteCarlo::CrossSectionsXMLProperties::electroatomic_file_type_prop,
	    MonteCarlo::CrossSectionsXMLProperties::native_file );
    new_table_info.set(
      MonteCarlo::CrossSectionsXMLProperties::electroatomic_file_start_line_prop,
      -1 );
    new_table_info.set(
	   MonteCarlo::CrossSectionsXMLProperties::electroatomic_table_name_prop,
	   "" );

    Teuchos::writeParameterListToXmlFile( *cross_sections_table_info,
					  cross_sections_xml_file );
  }
  else
    new_file_name = oss.str();

  data_container.exportData( new_file_name,
			     Utility::ArchivableObject::XML_ARCHIVE );

  return 0;
}

//---------------------------------------------------------------------------//
// end epr_generator.cpp
//---------------------------------------------------------------------------//
