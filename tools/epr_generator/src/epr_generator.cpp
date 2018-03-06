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
#include "MonteCarlo_TwoDInterpolationType.hpp"
#include "DataGen_StandardElectronPhotonRelaxationDataGenerator.hpp"
#include "Data_CrossSectionsXMLProperties.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_ENDLFileHandler.hpp"
#include "Data_ENDLDataContainer.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Data_ElectronPhotonRelaxationVolatileDataContainer.hpp"
#include "Data_DataContainerHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_StaticOutputFormatter.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

int main( int argc, char** argv )
{
  std::shared_ptr<const DataGen::ElectronPhotonRelaxationDataGenerator>
    epr_generator;

  Teuchos::RCP<Teuchos::FancyOStream> out =
    Teuchos::VerboseObjectBase::getDefaultOStream();

  // Set up the command line options
  Teuchos::CommandLineProcessor epr_generator_clp;

  // General table options
  std::string cross_section_directory, cross_section_alias;
  std::string subdirectory_name = "native";
  std::string output_alias = "Native";
  std::string table_notes;
  bool modify_cs_xml_file = false;

  // Table energy limits options
  double min_photon_energy = 0.001, max_photon_energy = 20.0;
  double min_electron_energy = 0.00001, max_electron_energy = 100000.0;

  // Photon options
  double occupation_number_evaluation_tol = 1e-3;
  double subshell_incoherent_evaluation_tol = 1e-3;

  // Electron options
  double tabular_evaluation_tol = 1e-7;
  double cutoff_angle_cosine = 1.0;
  int number_of_moment_preserving_angles = 0;
  bool append_moment_preserving_data = false;
  std::string electron_two_d_interp = "Log-Log-Log";
  MonteCarlo::TwoDInterpolationType electron_interp =
                                        MonteCarlo::LOGLOGLOG_INTERPOLATION;

  // General grid generation options
  double grid_convergence_tol = 0.001;
  double grid_absolute_diff_tol = 1e-42;
  double grid_distance_tol = 1e-16;

  // Set the general table option names
  epr_generator_clp.setDocString( "Electron-Photon-Relaxation Native Data File"
                                  " Generator\n" );
  epr_generator_clp.setOption( "cross_sec_dir",
                               &cross_section_directory,
                               "Directory containing desired cross section "
                               "tables",
                               true );
  epr_generator_clp.setOption( "cross_sec_alias",
                               &cross_section_alias,
                               "Electron-Photon-Relaxation cross section table "
                               "alias",
                               true );
  epr_generator_clp.setOption( "output_alias",
                               &output_alias,
                               "Alias appended onto the cross section table "
                               "alias used to generate the table" );
  epr_generator_clp.setOption( "subdir",
                               &subdirectory_name,
                               "Subdirectory in the cross section directory "
                               "where the generated table will be placed" );
  epr_generator_clp.setOption( "notes",
                               &table_notes,
                               "Notes about this table (e.g. date of "
                               "generation, owner, copyright, etc.)" );
  epr_generator_clp.setOption( "modify_cs_xml_file",
                               "do_not_modify_cs_xml_file",
                               &modify_cs_xml_file,
                               "Modify the cross_sections.xml file?" );

  // Set the table energy limits option names
  epr_generator_clp.setOption( "min_photon_energy",
                               &min_photon_energy,
                               "Min photon energy for table (E>0.0)" );
  epr_generator_clp.setOption( "max_photon_energy",
                               &max_photon_energy,
                               "Max photon energy for table (E>E_min)" );
  epr_generator_clp.setOption( "min_electron_energy",
                               &min_electron_energy,
                               "Min electron energy for table (E>0.0)" );
  epr_generator_clp.setOption( "max_electron_energy",
                               &max_electron_energy,
                               "Max electron energy for table (E>E_min)" );

  // Set the photon option names
  epr_generator_clp.setOption( "occupation_num_tol",
                               &occupation_number_evaluation_tol,
                               "Occupation number evaluation tolerance "
                               "(0.0<tol<1.0)" );
  epr_generator_clp.setOption( "subshell_incoherent_tol",
                               &subshell_incoherent_evaluation_tol,
                               "Subshell incoherent evaluation tolerance "
                               "(0.0<tol<1.0)" );
  
  // Set the electron option names
  epr_generator_clp.setOption( "tabular_evaluation_tol",
                               &tabular_evaluation_tol,
                               "Tabular evaluation tolerance "
                               "(0.0<tol<1.0)" );
  epr_generator_clp.setOption( "cutoff_angle_cosine",
                               &cutoff_angle_cosine,
                               "Cutoff angle cosine for table "
                               "(-1.0<=mu<=1.0)" );
  epr_generator_clp.setOption( "number_of_moment_preserving_angles",
                               &number_of_moment_preserving_angles,
                               "Number of moment preserving angles for table "
                               "(angles>=0)" );
  epr_generator_clp.setOption( "electron_interp_policy",
                               &electron_two_d_interp,
                               "The electron 2D interpolation policy" );
  epr_generator_clp.setOption( "append_moment_preserving_data",
                               "do_not_append_moment_preserving_data",
                               &append_moment_preserving_data,
                               "Append a native data file with new moment preserving data?" );

  // Set the grid generation option names
  epr_generator_clp.setOption( "grid_convergence_tol",
                               &grid_convergence_tol,
                               "Grid convergence tolerance (0.0<tol<1.0)" );
  epr_generator_clp.setOption( "grid_absolute_diff_tol",
                               &grid_absolute_diff_tol,
                               "Grid absolute difference tolerance "
                               "(0.0<tol<1.0)" );
  epr_generator_clp.setOption( "grid_absolute_dist_tol",
                               &grid_distance_tol,
                               "Grid absolute distance tolerance "
                               "(0.0<tol<1.0)" );

  epr_generator_clp.throwExceptions( false );

  // Parse the command line
  Teuchos::CommandLineProcessor::EParseCommandLineReturn
    parse_return = epr_generator_clp.parse( argc, argv );

  if( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL )
  {
    epr_generator_clp.printHelpMessage( argv[0], *out );

    return parse_return;
  }

  // Make sure the user's requested option values are valid
  // 1.) The min photon energy must be > 0.0
  if( min_photon_energy <= 0.0 )
  {
    std::cerr << Utility::BoldRed( "Error: " )
              << "the min photon energy is not valid!"
              << std::endl;

    epr_generator_clp.printHelpMessage( argv[0], *out );

    return 1;
  }

  // 2.) The max photon energy must be > min photon energy
  if( max_photon_energy <= min_photon_energy )
  {
    std::cerr << Utility::BoldRed( "Error: " )
              << "the max photon energy is not valid!"
              << std::endl;

    epr_generator_clp.printHelpMessage( argv[0], *out );

    return 1;
  }

  // 3.) The min electron energy must be > 0.0
  if( min_electron_energy <= 0.0 )
  {
    std::cerr << Utility::BoldRed( "Error: " )
              << "the min electron energy is not valid!"
              << std::endl;

    epr_generator_clp.printHelpMessage( argv[0], *out );

    return 1;
  }

  // 4.) The max electron energy must be > min electron energy
  if( max_electron_energy <= min_electron_energy )
  {
    std::cerr << Utility::BoldRed( "Error: " )
              << "the max electron energy is not valid!"
              << std::endl;

    epr_generator_clp.printHelpMessage( argv[0], *out );
  }

  // 5.) The occupation number evaluation tolerance must be in the valid range
  if( occupation_number_evaluation_tol <= 0.0 ||
      occupation_number_evaluation_tol >= 1.0 )
  {
    std::cerr << Utility::BoldRed( "Error: " )
              << "the occupation number evaluation tolerance is not valid!"
              << std::endl;

    epr_generator_clp.printHelpMessage( argv[0], *out );

    return 1;
  }

  // 6.) The subshell incoherent evaluation tolerance must be in the valid
  //     range
  if( subshell_incoherent_evaluation_tol <= 0.0 ||
      subshell_incoherent_evaluation_tol >= 1.0 )
  {
    std::cerr << Utility::BoldRed( "Error: " )
              << "the subshell incoherent evaluation tolerance is not valid!"
              << std::endl;

    epr_generator_clp.printHelpMessage( argv[0], *out );

    return 1;
  }

  // 7.) The tabular evaluation tolerance must be in the valid range
  if( tabular_evaluation_tol < -1.0 ||
      tabular_evaluation_tol > 1.0 )
  {
    std::cerr << Utility::BoldRed( "Error: " )
              << "the tabular evaluation tolerance is not valid!"
              << std::endl;

    epr_generator_clp.printHelpMessage( argv[0], *out );

    return 1;
  }

  // 8.) The cutoff angle cosine must be in the valid range
  if( cutoff_angle_cosine < -1.0 ||
      cutoff_angle_cosine > 1.0 )
  {
    std::cerr << Utility::BoldRed( "Error: " )
              << "the cutoff angle cosine is not valid!"
              << std::endl;

    epr_generator_clp.printHelpMessage( argv[0], *out );

    return 1;
  }

  // 8.) The electron TwoDInterpPolicy
  if( !Data::isTwoDInterpPolicyValid( electron_two_d_interp ) )
  {
    std::cerr << Utility::BoldRed( "Error: " )
              << "the electron 2D interpolation policy is not valid!"
              << std::endl;

    epr_generator_clp.printHelpMessage( argv[0], *out );

    return 1;
  }
  else
  {
    electron_interp =
      MonteCarlo::convertStringToTwoDInterpolationType( electron_two_d_interp );
  }

  // 9.) The number of moment preserving angles must be >= 0
  if( number_of_moment_preserving_angles < 0 )
  {
    std::cerr << Utility::BoldRed( "Error: " )
              << "the number of moment preserving angles is not valid!"
              << std::endl;

    epr_generator_clp.printHelpMessage( argv[0], *out );

    return 1;
  }

  // 10.) The grid convergence tolerance must be in the valid range
  if( grid_convergence_tol <= 0.0 || grid_convergence_tol >= 1.0 )
  {
    std::cerr << Utility::BoldRed( "Error: " )
              << "the grid convergence tolerance is not valid!"
              << std::endl;

    epr_generator_clp.printHelpMessage( argv[0], *out );

    return 1;
  }

  // 11.) The grid absolute difference tolerance must be in the valid range
  if( grid_absolute_diff_tol <= 0.0 || grid_absolute_diff_tol >= 1.0 )
  {
    std::cerr << Utility::BoldRed( "Error: " )
              << "the grid absolute difference tolerance is not valid!"
              << std::endl;

    epr_generator_clp.printHelpMessage( argv[0], *out );

    return 1;
  }
  
  // 12.) The grid distance tolerance must be in the valid range
  if( grid_distance_tol <= 0.0 || grid_distance_tol >= 1.0 )
  {
    std::cerr << Utility::BoldRed( "Error: " )
              << "the grid distance tolerance is not valid!"
              << std::endl;
    
    epr_generator_clp.printHelpMessage( argv[0], *out );

    return 1;
  }
  
  // Open the cross_sections.xml file
  std::string cross_sections_xml_file = cross_section_directory;
  cross_sections_xml_file += "/cross_sections.xml";

  Teuchos::RCP<Teuchos::ParameterList> cross_sections_table_info =
    Teuchos::getParametersFromXmlFile( cross_sections_xml_file );

  std::string data_file_path, data_file_type, data_table_name;
  int data_file_start_line, atomic_number;
  double atomic_weight;

  try{
    Data::CrossSectionsXMLProperties::extractInfoFromPhotoatomTableInfoParameterList(
                                                    cross_section_directory,
                                                    cross_section_alias,
                                                    *cross_sections_table_info,
                                                    data_file_path,
                                                    data_file_type,
                                                    data_table_name,
                                                    data_file_start_line,
                                                    atomic_weight );
  }
  EXCEPTION_CATCH_AND_EXIT( std::exception,
                            "Error: Unable to load the requested cross "
                            "section table metadata!" );

  if( append_moment_preserving_data )
  {
    if( data_file_type == "Native" )
    {
      Data::ElectronPhotonRelaxationVolatileDataContainer data_container(
            data_file_path,
            Utility::ArchivableObject::XML_ARCHIVE );
      
      try{
        DataGen::StandardElectronPhotonRelaxationDataGenerator::repopulateMomentPreservingData(
          data_container,
          cutoff_angle_cosine,
          tabular_evaluation_tol,
          number_of_moment_preserving_angles,
          electron_interp );
      }
      EXCEPTION_CATCH_AND_EXIT( std::exception,
                                "Error: Unable to repopulate the moment "
                                "preserving data!" );

      data_container.exportData( data_file_path,
                                 Utility::ArchivableObject::XML_ARCHIVE );
    }
    else
    {
      std::cerr << Utility::BoldRed( "Error: " )
             << "Photoatomic file type " << data_file_type
             << " is not supported!";

      return 1;
    }
  }
  else
  {
    // Create the data generator
    if( data_file_type == "ACE" )
    {
      Data::ACEFileHandler ace_file_handler( data_file_path,
                                             data_table_name,
                                             data_file_start_line,
                                             true );

      std::shared_ptr<const Data::XSSEPRDataExtractor> ace_epr_extractor(
                                new const Data::XSSEPRDataExtractor(
                                       ace_file_handler.getTableNXSArray(),
                                       ace_file_handler.getTableJXSArray(),
                                       ace_file_handler.getTableXSSArray() ) );

      atomic_number = ace_epr_extractor->extractAtomicNumber();
      
      std::ostringstream oss;
      oss << "endl_" << atomic_number << "_native.xml";
      
      std::string endl_file_path = cross_section_directory;
      endl_file_path += "/endldata/";
      endl_file_path += oss.str();

      std::shared_ptr<Data::ENDLDataContainer> endl_data_container;
      try{
        endl_data_container.reset( new Data::ENDLDataContainer(
                                    endl_file_path,
                                    Utility::ArchivableObject::XML_ARCHIVE ) );
      }
      EXCEPTION_CATCH_AND_EXIT( std::exception,
                                "Error: Unable to load the desired ENDL data "
                                "file!" );

      try{
        DataGen::StandardElectronPhotonRelaxationDataGenerator*
          raw_generator = new DataGen::StandardElectronPhotonRelaxationDataGenerator(
                                            ace_epr_extractor,
                                            endl_data_container,
                                            min_photon_energy,
                                            max_photon_energy,
                                            min_electron_energy,
                                            max_electron_energy );
        
        raw_generator->setOccupationNumberEvaluationTolerance(
                                            occupation_number_evaluation_tol );
        raw_generator->setSubshellIncoherentEvaluationTolerance(
                                          subshell_incoherent_evaluation_tol );
        raw_generator->setTabularEvaluationTolerance( tabular_evaluation_tol );
        raw_generator->setCutoffAngleCosine( cutoff_angle_cosine );
        raw_generator->setNumberOfMomentPreservingAngles(
                                          number_of_moment_preserving_angles );
        raw_generator->setDefaultPhotonGridConvergenceTolerance(
                                                        grid_convergence_tol );
        raw_generator->setDefaultPhotonGridAbsoluteDifferenceTolerance(
                                                      grid_absolute_diff_tol );
        raw_generator->setDefaultPhotonGridDistanceTolerance( grid_distance_tol );
        raw_generator->setDefaultElectronGridConvergenceTolerance(
                                                        grid_convergence_tol );
        raw_generator->setDefaultElectronGridAbsoluteDifferenceTolerance(
                                                      grid_absolute_diff_tol );
        raw_generator->setDefaultElectronGridDistanceTolerance( grid_distance_tol );
        raw_generator->setElectronTwoDInterpPolicy( electron_interp );

        epr_generator.reset( raw_generator );
      }
      EXCEPTION_CATCH_AND_EXIT( std::exception,
                                "Error: Unable to constructor the epr "
                                "generator!" );
    }
    else
    {
      std::cerr << Utility::BoldRed( "Error: " )
                << "Photoatomic file type " << data_file_type
                << " is not supported!";

      return 1;
    }

    // Create the new data container
    Data::ElectronPhotonRelaxationVolatileDataContainer data_container;

    try{
      epr_generator->populateEPRDataContainer( data_container );
    }
    EXCEPTION_CATCH_AND_EXIT( std::exception,
                              "Error: The EPR data could not be generated! " );

    std::ostringstream oss;
    oss << "epr_" << atomic_number << "_native.xml";

    std::string new_file_name;

    // Export the generated data to an XML file
    if( modify_cs_xml_file )
    {
      std::string local_file_name;

      if( subdirectory_name.size() > 0 )
      {
        local_file_name = subdirectory_name;
        local_file_name += "/";
      }

      local_file_name += oss.str();

      new_file_name = cross_section_directory;
      new_file_name += "/";
      new_file_name += local_file_name;

      std::string new_cross_section_alias( cross_section_alias );
      new_cross_section_alias += "-"+output_alias;

      Teuchos::ParameterList& old_table_info =
        cross_sections_table_info->sublist( cross_section_alias );

      Teuchos::ParameterList& new_table_info =
        cross_sections_table_info->sublist( new_cross_section_alias );
      
      new_table_info.setParameters( old_table_info );
      
      new_table_info.set(
            Data::CrossSectionsXMLProperties::photoatomic_file_path_prop,
            local_file_name );
      new_table_info.set(
            Data::CrossSectionsXMLProperties::photoatomic_file_type_prop,
            Data::CrossSectionsXMLProperties::native_file );
      new_table_info.set(
        Data::CrossSectionsXMLProperties::photoatomic_file_start_line_prop,
        -1 );
      new_table_info.set(
           Data::CrossSectionsXMLProperties::photoatomic_table_name_prop,
           "" );

      new_table_info.set(
            Data::CrossSectionsXMLProperties::electroatomic_file_path_prop,
            local_file_name );
      new_table_info.set(
            Data::CrossSectionsXMLProperties::electroatomic_file_type_prop,
            Data::CrossSectionsXMLProperties::native_file );
      new_table_info.set(
        Data::CrossSectionsXMLProperties::electroatomic_file_start_line_prop,
        -1 );
      new_table_info.set(
           Data::CrossSectionsXMLProperties::electroatomic_table_name_prop,
           "" );

      Teuchos::writeParameterListToXmlFile( *cross_sections_table_info,
                                            cross_sections_xml_file );
    }
    else
      new_file_name = oss.str();

    // Add the notes to the data container before exporting it
    if( table_notes.size() > 0 )
      data_container.setNotes( table_notes );
    
    data_container.exportData( new_file_name,
                               Utility::ArchivableObject::XML_ARCHIVE );
  }

  return 0;
}

//---------------------------------------------------------------------------//
// end epr_generator.cpp
//---------------------------------------------------------------------------//
