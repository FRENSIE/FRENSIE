//---------------------------------------------------------------------------//
//!
//! \file   moment_preserving_data_generator.cpp
//! \author Luke Kersting
//! \brief  moment_preserving_data_generator tool
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
#include "DataGen_StandardMomentPreservingElectronDataGenerator.hpp"
#include "MonteCarlo_CrossSectionsXMLProperties.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

int main( int argc, char** argv )
{
  Teuchos::RCP<const DataGen::MomentPreservingElectronDataGenerator>
    mp_data_generator;

  Teuchos::RCP<Teuchos::FancyOStream> out =
    Teuchos::VerboseObjectBase::getDefaultOStream();

  // Set up the command line options
  Teuchos::CommandLineProcessor mp_data_generator_clp;

  std::string cross_section_directory, cross_section_alias;
  double min_electron_energy = 0.00001, max_electron_energy = 100000.0;
  double cutoff_angle_cosine = 0.9;
  int number_of_moment_preserving_angles = 1;
  bool modify_cs_xml_file = false;

  mp_data_generator_clp.setDocString( "Moment Preserving Electron Native Data File"
				  " Generator\n" );
  mp_data_generator_clp.setOption( "cross_sec_dir",
			       &cross_section_directory,
			       "Directory containing desired cross section "
			       "tables",
			       true );
  mp_data_generator_clp.setOption( "cross_sec_alias",
			       &cross_section_alias,
			       "Photon cross section table alias",
			       true );
  mp_data_generator_clp.setOption( "min_electron_energy",
			       &min_electron_energy,
			       "Min electron energy for table" );
  mp_data_generator_clp.setOption( "max_electron_energy",
			       &max_electron_energy,
			       "Max electron energy for table" );
  mp_data_generator_clp.setOption( "cutoff_angle_cosine",
			       &cutoff_angle_cosine,
			       "Cutoff angle cosine for moment preserving elastic data" );
  mp_data_generator_clp.setOption( "number_of_moment_preserving_angles",
			       &number_of_moment_preserving_angles,
			       "Number of discrete moment preserving angles" );
  mp_data_generator_clp.setOption( "modify_cs_xml_file",
			       "do_not_modify_cs_xml_file",
			       &modify_cs_xml_file,
			       "Modify the cross_sections.xml file?" );

  mp_data_generator_clp.throwExceptions( false );

  // Parse the command line
  Teuchos::CommandLineProcessor::EParseCommandLineReturn
    parse_return = mp_data_generator_clp.parse( argc, argv );

  if( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL )
  {
    mp_data_generator_clp.printHelpMessage( argv[0], *out );

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

  MonteCarlo::CrossSectionsXMLProperties::extractInfoFromElectroatomTableInfoParameterList(
						    cross_section_directory,
						    cross_section_alias,
						    *cross_sections_table_info,
						    data_file_path,
						    data_file_type,
						    data_table_name,
						    data_file_start_line,
						    atomic_weight );

  // Create the data generator
  if( data_file_type == "Native" )
  {
    Teuchos::RCP<Data::ElectronPhotonRelaxationDataContainer> native_data_container(
        new Data::ElectronPhotonRelaxationDataContainer( data_file_path ) );

    atomic_number = native_data_container->getAtomicNumber();

    mp_data_generator.reset(
	    new const DataGen::StandardMomentPreservingElectronDataGenerator(
					    atomic_number,
					    native_data_container,
					    min_electron_energy,
					    max_electron_energy,
                        cutoff_angle_cosine ) );
  }
  else
  {
    std::cerr << "Error: Electroatomic file type "
	      << data_file_type << "is not supported!";
  }

  // Create the new data container
  Data::MomentPreservingElectronVolatileDataContainer data_container;

  mp_data_generator->populateMomentPreservingDataContainer(
                            data_container,
                            number_of_moment_preserving_angles );

  std::ostringstream oss;
  oss << "moment_preserving_" << atomic_number << "_native.xml";

  std::string new_file_name;

  // Export the generated data to an XML file
  if( modify_cs_xml_file )
  {
    new_file_name = cross_section_directory;
    new_file_name += "/";
    new_file_name += oss.str();

    std::string new_cross_section_alias( cross_section_alias );

    std::size_t pos = new_cross_section_alias.find("-Native");
    new_cross_section_alias.replace(pos, std::string::npos,"-MomentPreserving");

    Teuchos::ParameterList& old_table_info =
      cross_sections_table_info->sublist( cross_section_alias );

    Teuchos::ParameterList& new_table_info =
      cross_sections_table_info->sublist( new_cross_section_alias );

    double atomic_weight_ratio = 
        old_table_info.get( MonteCarlo::CrossSectionsXMLProperties::atomic_weight_ratio_prop, 0.0 );

    new_table_info.set(
	    MonteCarlo::CrossSectionsXMLProperties::electroatomic_file_path_prop,
	    oss.str() );
    new_table_info.set(
	    MonteCarlo::CrossSectionsXMLProperties::electroatomic_file_type_prop,
	    MonteCarlo::CrossSectionsXMLProperties::moment_preserving_file );
    new_table_info.set(
      MonteCarlo::CrossSectionsXMLProperties::electroatomic_file_start_line_prop,
      -1 );
    new_table_info.set(
	   MonteCarlo::CrossSectionsXMLProperties::electroatomic_table_name_prop,
	   "" );
    new_table_info.set(
	   MonteCarlo::CrossSectionsXMLProperties::atomic_number_prop,
	   atomic_number );
    new_table_info.set(
	   MonteCarlo::CrossSectionsXMLProperties::atomic_weight_ratio_prop,
	   atomic_weight_ratio );

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
// end moment_preserving_data_generator.cpp
//---------------------------------------------------------------------------//
