//---------------------------------------------------------------------------//
//!
//! \file   endl_generator.cpp
//! \author Alex Robinson
//! \brief  The endl generator exec
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/filesystem.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

// FRENSIE Includes
#include "DataGen_StandardENDLDataGenerator.hpp"
#include "Utility_LoggingMacros.hpp"

int main( int argc, char** argv )
{
  FRENSIE_SETUP_STANDARD_SYNCHRONOUS_LOGS( std::cout );
  
  boost::program_options::variables_map command_line_arguments;

  // Create the command line options
  {
    boost::program_options::options_description command_line_options;
    command_line_options.add_options()
      ("help,h", "produce help message")
      ("eadl_file,a",
       boost::program_options::value<std::string>(),
       "specify the relative location of the eadl file")
      ("epdl_file,p",
       boost::program_options::value<std::string>(),
       "specify the relative location of the epdl file")
      ("eedl_file,e",
       boost::program_options::value<std::string>(),
       "specify the relative location of the eedl file")
      ("output_file,o",
       boost::program_options::value<std::string>(),
       "specify the output file name");

    // Parse the command line arguments
    boost::program_options::store(
         boost::program_options::command_line_parser(argc, argv).options(command_line_options).run(),
         command_line_arguments );

    boost::program_options::notify( command_line_arguments );
  }

  // Set the output file name
  TEST_FOR_EXCEPTION( !command_line_arguments.count( "output_file" ),
                      std::runtime_error,
                      "The output file must be specified!" );

  boost::filesystem::path output_file_name =
    command_line_arguments["output_file"].as<std::string>();

  // Set the eadl file name
  TEST_FOR_EXCEPTION( !command_line_arguments.count( "eadl_file" ),
                      std::runtime_error,
                      "The eadl file must be specified!" );
  
  boost::filesystem::path eadl_file_name =
    command_line_arguments["eadl_file"].as<std::string>();

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( eadl_file_name ),
                      std::runtime_error,
                      "The eadl file path is not valid!" );

  // Set the epdl file name
  TEST_FOR_EXCEPTION( !command_line_arguments.count( "epdl_file" ),
                      std::runtime_error,
                      "The epdl file must be specified!" );
  
  boost::filesystem::path epdl_file_name =
    command_line_arguments["epdl_file"].as<std::string>();

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( epdl_file_name ),
                      std::runtime_error,
                      "The epdl file path is not valid!" );

  // Set the eedl file name
  TEST_FOR_EXCEPTION( !command_line_arguments.count( "eedl_file" ),
                      std::runtime_error,
                      "The eedl file must be specified!" );
  
  boost::filesystem::path eedl_file_name =
    command_line_arguments["eedl_file"].as<std::string>();

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( eedl_file_name ),
                      std::runtime_error,
                      "The eedl file path is not valid!" );

  // Create the endl data generator
  DataGen::StandardENDLDataGenerator
    data_generator( eadl_file_name, epdl_file_name, eedl_file_name );

  data_generator.populateENDLDataContainer();

  data_generator.getDataContainer().saveToFile( output_file_name, true );

  return 0;
}

//---------------------------------------------------------------------------//
// end endl_generator.cpp
//---------------------------------------------------------------------------//
