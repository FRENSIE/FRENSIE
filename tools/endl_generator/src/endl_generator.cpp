//---------------------------------------------------------------------------//
//!
//! \file   endl_generator.cpp
//! \author Luke Kersting
//! \brief  endl_generator tool
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
#include "DataGen_StandardEvaluatedElectronDataGenerator.hpp"
#include "Data_CrossSectionsXMLProperties.hpp"
#include "Data_ENDLFileHandler.hpp"
#include "Data_EvaluatedElectronVolatileDataContainer.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

int main( int argc, char** argv )
{/*
  Teuchos::RCP<const DataGen::EvaluatedElectronDataGenerator>
    endl_generator;

  Teuchos::RCP<Teuchos::FancyOStream> out =
    Teuchos::VerboseObjectBase::getDefaultOStream();

  // Set up the command line options
  Teuchos::CommandLineProcessor endl_generator_clp;

  std::string cross_section_directory, cross_section_alias;
  double min_electron_energy = 0.00001, max_electron_energy = 100000.0;
  double cutoff_angle = 1.0e-6;
  double grid_convergence_tol = 0.001;
  double grid_absolute_diff_tol = 1e-42;
  double grid_distance_tol = 1e-16;
  bool modify_cs_xml_file = false;

  endl_generator_clp.setDocString( "ENDL Native Data File"
				  " Generator\n" );
  endl_generator_clp.setOption( "cross_sec_dir",
			       &cross_section_directory,
			       "Directory containing desired cross section "
			       "tables",
			       true );
  endl_generator_clp.setOption( "cross_sec_alias",
			       &cross_section_alias,
			       "Electron cross section table alias",
			       true );
  endl_generator_clp.setOption( "min_electron_energy",
			       &min_electron_energy,
			       "Min electron energy for table" );
  endl_generator_clp.setOption( "max_electron_energy",
			       &max_electron_energy,
			       "Max electron energy for table" );
  endl_generator_clp.setOption( "grid_convergence_tol",
			       &grid_convergence_tol,
			       "Grid convergence tolerance" );
  endl_generator_clp.setOption( "grid_absolute_diff_tol",
			       &grid_absolute_diff_tol,
			       "Grid absolute difference tolerance" );
  endl_generator_clp.setOption( "grid_absolute_dist_tol",
			       &grid_distance_tol,
			       "Grid absolute distance tolerance" );
  endl_generator_clp.setOption( "modify_cs_xml_file",
			       "do_not_modify_cs_xml_file",
			       &modify_cs_xml_file,
			       "Modify the cross_sections.xml file?" );

  endl_generator_clp.throwExceptions( false );

  // Parse the command line
  Teuchos::CommandLineProcessor::EParseCommandLineReturn
    parse_return = endl_generator_clp.parse( argc, argv );

  if( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL )
  {
    endl_generator_clp.printHelpMessage( argv[0], *out );

    return parse_return;
  }

  std::string data_file_path = cross_section_directory;
  data_file_path += "/";
  data_file_path += cross_section_alias;

  Teuchos::RCP<Data::ENDLFileHandler> endl_file_handler(
        new Data::ENDLFileHandler( data_file_path ) );

  int atomic_number,outgoing_particle_designator, interpolation_flag;
  double atomic_weight;
  // Read first table header and determine which element is being processed
  endl_file_handler->readFirstTableHeader( atomic_number,
                                           outgoing_particle_designator,
                                           atomic_weight,
                                           interpolation_flag );

  endl_generator.reset(
	    new const DataGen::StandardEvaluatedElectronDataGenerator(
					    atomic_number,
					    endl_file_handler,
					    min_electron_energy,
					    max_electron_energy,
                        cutoff_angle,
					    grid_convergence_tol,
					    grid_absolute_diff_tol,
					    grid_distance_tol ) );

  // Create the new data container
  Data::EvaluatedElectronVolatileDataContainer data_container;

  endl_generator->populateEvaluatedDataContainer( data_container );

  std::ostringstream oss;
  oss << "e_" << atomic_number << "_native.xml";

  std::string new_file_name;

  new_file_name = oss.str();

  data_container.exportData( new_file_name,
			     Utility::ArchivableObject::XML_ARCHIVE );
*/
  return 0;
}

//---------------------------------------------------------------------------//
// end endl_generator.cpp
//---------------------------------------------------------------------------//
