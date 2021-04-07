//---------------------------------------------------------------------------//
//!
//! \file   database_generator.cpp
//! \author Alex Robinson
//! \brief  The database generator exec
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/filesystem.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

// FRENSIE Includes
#include "Data_ScatteringCenterPropertiesDatabase.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"

using Utility::Units::MeV;
using Utility::Units::amu;

namespace Details{

//! Add the 79000.14p properties
void addTestAuEPR14ACEFile(
                          const bool library_available,
                          const std::string& library_filepath,
                          const int library_filestartline,
                          Data::ScatteringCenterPropertiesDatabase& database );

//! Add the 5000.03e properties
void addBElectronACEFile( const bool library_available,
                          const std::string& library_filepath,
                          const int library_filestartline,
                          Data::ScatteringCenterPropertiesDatabase& database );

//! Add the 5000.12p properties
void addBEPRACEFile( const bool library_available,
                     const std::string& library_filepath,
                     const int library_filestartline,
                     Data::ScatteringCenterPropertiesDatabase& database );

//! Add the 6012.24u properties
void addC12PhotonuclearACEFile(
                          const bool library_available,
                          const std::string& library_filepath,
                          const int library_filestartline,
                          Data::ScatteringCenterPropertiesDatabase& database );

//! Add the 6000.12p properties
void addCEPRACEFile( const bool library_available,
                     const std::string& library_filepath,
                     const int library_filestartline,
                     Data::ScatteringCenterPropertiesDatabase& database );

//! Add the grph.10t properties
void addGrphSabACEFile( const bool library_available,
                        const std::string& library_filepath,
                        const int library_filestartline,
                        Data::ScatteringCenterPropertiesDatabase& database );

//! Add the 1001.70c properties
void addH1ACEFile( const bool library_available,
                   const std::string& library_filepath,
                   const int library_filestartline,
                   Data::ScatteringCenterPropertiesDatabase& database );

//! Add the lwtr.10t properties
void addH2OSabACEFile( const bool library_available,
                       const std::string& library_filepath,
                       const int library_filestartline,
                       Data::ScatteringCenterPropertiesDatabase& database );

//! Add the 1002.24u properties
void addH2PhotonuclearACEFile(
                          const bool library_available,
                          const std::string& library_filepath,
                          const int library_filestartline,
                          Data::ScatteringCenterPropertiesDatabase& database );

//! Add the 1000.14p properties
void addHEPR14ACEFile( const bool library_available,
                       const std::string& library_filepath,
                       const int library_filestartline,
                       Data::ScatteringCenterPropertiesDatabase& database );
  
//! Add the 1000.12p properties
void addHEPRACEFile( const bool library_available,
                     const std::string& library_filepath,
                     const int library_filestartline,
                     Data::ScatteringCenterPropertiesDatabase& database );

//! Add the poly.10t properties
void addPolySabACEFile( const bool library_available,
                        const std::string& library_filepath,
                        const int library_filestartline,
                        Data::ScatteringCenterPropertiesDatabase& database );

//! Add the 8016.70c properties
void addO16ACEFile( const bool library_available,
                    const std::string& library_filepath,
                    const int library_filestartline,
                    Data::ScatteringCenterPropertiesDatabase& database );

//! Add the 8000.12p properties
void addOEPRACEFile( const bool library_available,
                     const std::string& library_filepath,
                     const int library_filestartline,
                     Data::ScatteringCenterPropertiesDatabase& database );

//! Add the 82208.70c properties
void addPb208ACEFile( const bool library_available,
                      const std::string& library_filepath,
                      const int library_filestartline,
                      Data::ScatteringCenterPropertiesDatabase& database );

//! Add the 82000.03e properties
void addPbElectronACEFile(
                          const bool library_available,
                          const std::string& library_filepath,
                          const int library_filestartline,
                          Data::ScatteringCenterPropertiesDatabase& database );

//! Add the 82000.14p properties
void addPbEPR14ACEFile( const bool library_available,
                        const std::string& library_filepath,
                        const int library_filestartline,
                        Data::ScatteringCenterPropertiesDatabase& database );

//! Add the 82000.12p properties
void addPbEPRACEFile( const bool library_available,
                      const std::string& library_filepath,
                      const int library_filestartline,
                      Data::ScatteringCenterPropertiesDatabase& database );

//! Add the 82000.04p properties
void addPbPhotoatomicACEFile(
                          const bool library_available,
                          const std::string& library_filepath,
                          const int library_filestartline,
                          Data::ScatteringCenterPropertiesDatabase& database );

//! Add the 92238.70c properties
void addU238ACEFile( const bool library_available,
                     const std::string& library_filepath,
                     const int library_filestartline,
                     Data::ScatteringCenterPropertiesDatabase& database );

//! Add the 92000.12p properties
void addUEPRACEFile( const bool library_available,
                     const std::string& library_filepath,
                     const int library_filestartline,
                     Data::ScatteringCenterPropertiesDatabase& database );

//! Add the "test_epr_1_native.xml" properties
void addHNativeEPRFile( const boost::filesystem::path& native_test_data_dir,
                        Data::ScatteringCenterPropertiesDatabase& database );

//! Add the "test_aepr_1_native.xml" properties
void addHNativeAEPRFile( const boost::filesystem::path& native_test_data_dir,
                         Data::ScatteringCenterPropertiesDatabase& database );

//! Add the "test_epr_6_native.xml" properties
void addCNativeEPRFile( const boost::filesystem::path& native_test_data_dir,
                        Data::ScatteringCenterPropertiesDatabase& database );

//! Add the "test_aepr_6_native.xml" properties
void addCNativeAEPRFile( const boost::filesystem::path& native_test_data_dir,
                         Data::ScatteringCenterPropertiesDatabase& database );

//! Add the "test_epr_13_native.xml" properties
void addAlNativeEPRFile( const boost::filesystem::path& native_test_data_dir,
                         Data::ScatteringCenterPropertiesDatabase& database );

//! Add the "test_aepr_13_native.xml" properties
void addAlNativeAEPRFile( const boost::filesystem::path& native_test_data_dir,
                          Data::ScatteringCenterPropertiesDatabase& database );

//! Add the "test_epr_14_native.xml" properties
void addSiNativeEPRFile( const boost::filesystem::path& native_test_data_dir,
                         Data::ScatteringCenterPropertiesDatabase& database );

//! Add the "test_aepr_14_native.xml" properties
void addSiNativeAEPRFile( const boost::filesystem::path& native_test_data_dir,
                          Data::ScatteringCenterPropertiesDatabase& database );

//! Add the "test_epr_82_native.xml" properties
void addPbNativeEPRFile( const boost::filesystem::path& native_test_data_dir,
                         Data::ScatteringCenterPropertiesDatabase& database );

} // end Details namespace

//! Add the Native test files for H
void addHNativeTestFiles( const boost::filesystem::path& native_test_data_dir,
                          Data::ScatteringCenterPropertiesDatabase& database )
{
  Details::addHNativeEPRFile( native_test_data_dir, database );
  Details::addHNativeAEPRFile( native_test_data_dir, database );
}

//! Add the Native test files for C
void addCNativeTestFiles( const boost::filesystem::path& native_test_data_dir,
                          Data::ScatteringCenterPropertiesDatabase& database )
{
  Details::addCNativeEPRFile( native_test_data_dir, database );
  Details::addCNativeAEPRFile( native_test_data_dir, database );
}

//! Add the Native test files for Al
void addAlNativeTestFiles( const boost::filesystem::path& native_test_data_dir,
                           Data::ScatteringCenterPropertiesDatabase& database )
{
  Details::addAlNativeEPRFile( native_test_data_dir, database );
  Details::addAlNativeAEPRFile( native_test_data_dir, database );
}

//! Add the Native test files for Si
void addSiNativeTestFiles( const boost::filesystem::path& native_test_data_dir,
                           Data::ScatteringCenterPropertiesDatabase& database )
{
  Details::addSiNativeEPRFile( native_test_data_dir, database );
  Details::addSiNativeAEPRFile( native_test_data_dir, database );
}

//! Add the Native test files for Pb
void addPbNativeTestFiles( const boost::filesystem::path& native_test_data_dir,
                           Data::ScatteringCenterPropertiesDatabase& database )
{
  Details::addPbNativeEPRFile( native_test_data_dir, database );
}

int main( int argc, char** argv )
{
  boost::program_options::variables_map command_line_arguments;

  {
    // Create the command line options
    boost::program_options::options_description command_line_options;
    command_line_options.add_options()
      ("help,h", "produce help message")
      ("1000_12p_available",
       boost::program_options::value<bool>()->default_value(false),
       "specify if the 1000.12p ACE library is available")
      ("1000_12p_filepath",
       boost::program_options::value<std::string>(),
       "specify the location of the 1000.12p ACE library")
      ("1000_12p_filestartline",
       boost::program_options::value<int>(),
       "specify the file start line of the 1000.12p ACE library")
      ("1000_14p_available",
       boost::program_options::value<bool>()->default_value(false),
       "specify if the 1000.14p ACE library is available")
      ("1000_14p_filepath",
       boost::program_options::value<std::string>(),
       "specify the location of the 1000.14p ACE library")
      ("1000_14p_filestartline",
       boost::program_options::value<int>(),
       "specify the file start line of the 1000.14p ACE library")
      ("5000_12p_available",
       boost::program_options::value<bool>()->default_value(false),
       "specify if the 5000.12p ACE library is available")
      ("5000_12p_filepath",
       boost::program_options::value<std::string>(),
       "specify the location of the 5000.12p ACE library")
      ("5000_12p_filestartline",
       boost::program_options::value<int>(),
       "specify the file start line of the 5000.12p ACE library")
      ("6000_12p_available",
       boost::program_options::value<bool>()->default_value(false),
       "specify if the 6000.12p ACE library is available")
      ("6000_12p_filepath",
       boost::program_options::value<std::string>(),
       "specify the location of the 6000.12p ACE library")
      ("6000_12p_filestartline",
       boost::program_options::value<int>(),
       "specify the file start line of the 6000.12p ACE library")
      ("8000_12p_available",
       boost::program_options::value<bool>()->default_value(false),
       "specify if the 8000.12p ACE library is available")
      ("8000_12p_filepath",
       boost::program_options::value<std::string>(),
       "specify the location of the 8000.12p ACE library")
      ("8000_12p_filestartline",
       boost::program_options::value<int>(),
       "specify the file start line of the 8000.12p ACE library")
      ("79000_14p_available",
       boost::program_options::value<bool>()->default_value(false),
       "specify if the 79000.14p ACE library is available")
      ("79000_14p_filepath",
       boost::program_options::value<std::string>(),
       "specify the location of the 79000.14p ACE library")
      ("79000_14p_filestartline",
       boost::program_options::value<int>(),
       "specify the file start line of the 79000.14p ACE library")
      ("82000_12p_available",
       boost::program_options::value<bool>()->default_value(false),
       "specify if the 82000.12p ACE library is available")
      ("82000_12p_filepath",
       boost::program_options::value<std::string>(),
       "specify the location of the 82000.12p ACE library")
      ("82000_12p_filestartline",
       boost::program_options::value<int>(),
       "specify the file start line of the 82000.12p ACE library")
      ("82000_14p_available",
       boost::program_options::value<bool>()->default_value(false),
       "specify if the 82000.14p ACE library is available")
      ("82000_14p_filepath",
       boost::program_options::value<std::string>(),
       "specify the location of the 82000.14p ACE library")
      ("82000_14p_filestartline",
       boost::program_options::value<int>(),
       "specify the file start line of the 82000.14p ACE library")
      ("92000_12p_available",
       boost::program_options::value<bool>()->default_value(false),
       "specify if the 92000.12p ACE library is available")
      ("92000_12p_filepath",
       boost::program_options::value<std::string>(),
       "specify the location of the 92000.12p ACE library")
      ("92000_12p_filestartline",
       boost::program_options::value<int>(),
       "specify the file start line of the 92000.12p ACE library")
      ("82000_04p_available",
       boost::program_options::value<bool>()->default_value(false),
       "specify if the 82000.04p ACE library is available")
      ("82000_04p_filepath",
       boost::program_options::value<std::string>(),
       "specify the location of the 82000.04p ACE library")
      ("82000_04p_filestartline",
       boost::program_options::value<int>(),
       "specify the file start line of the 82000.04p ACE library")
      ("5000_03e_available",
       boost::program_options::value<bool>()->default_value(false),
       "specify if the 5000.03e ACE library is available")
      ("5000_03e_filepath",
       boost::program_options::value<std::string>(),
       "specify the location of the 5000.03e ACE library")
      ("5000_03e_filestartline",
       boost::program_options::value<int>(),
       "specify the file start line of the 5000.03e ACE library")
      ("82000_03e_available",
       boost::program_options::value<bool>()->default_value(false),
       "specify if the 82000.03e ACE library is available")
      ("82000_03e_filepath",
       boost::program_options::value<std::string>(),
       "specify the location of the 82000.03e ACE library")
      ("82000_03e_filestartline",
       boost::program_options::value<int>(),
       "specify the file start line of the 82000.03e ACE library")
      ("1002_24u_available",
       boost::program_options::value<bool>()->default_value(false),
       "specify if the 1002.24u ACE library is available")
      ("1002_24u_filepath",
       boost::program_options::value<std::string>(),
       "specify the location of the 1002.24u ACE library")
      ("1002_24u_filestartline",
       boost::program_options::value<int>(),
       "specify the file start line of the 1002.24u ACE library")
      ("6012_24u_available",
       boost::program_options::value<bool>()->default_value(false),
       "specify if the 6012.24u ACE library is available")
      ("6012_24u_filepath",
       boost::program_options::value<std::string>(),
       "specify the location of the 6012.24u ACE library")
      ("6012_24u_filestartline",
       boost::program_options::value<int>(),
       "specify the file start line of the 6012.24u ACE library")
      ("1001_70c_available",
       boost::program_options::value<bool>()->default_value(false),
       "specify if the 1001.70c ACE library is available")
      ("1001_70c_filepath",
       boost::program_options::value<std::string>(),
       "specify the location of the 1001.70c ACE library")
      ("1001_70c_filestartline",
       boost::program_options::value<int>(),
       "specify the file start line of the 1001.70c ACE library")
      ("8016_70c_available",
       boost::program_options::value<bool>()->default_value(false),
       "specify if the 8016.70c ACE library is available")
      ("8016_70c_filepath",
       boost::program_options::value<std::string>(),
       "specify the location of the 8016.70c ACE library")
      ("8016_70c_filestartline",
       boost::program_options::value<int>(),
       "specify the file start line of the 8016.70c ACE library")
      ("82208_70c_available",
       boost::program_options::value<bool>()->default_value(false),
       "specify if the 82208.70c ACE library is available")
      ("82208_70c_filepath",
       boost::program_options::value<std::string>(),
       "specify the location of the 82208.70c ACE library")
      ("82208_70c_filestartline",
       boost::program_options::value<int>(),
       "specify the file start line of the 82208.70c ACE library")
      ("92238_70c_available",
       boost::program_options::value<bool>()->default_value(false),
       "specify if the 92238.70c ACE library is available")
      ("92238_70c_filepath",
       boost::program_options::value<std::string>(),
       "specify the location of the 92238.70c ACE library")
      ("92238_70c_filestartline",
       boost::program_options::value<int>(),
       "specify the file start line of the 92238.70c ACE library")
      ("grph_10t_available",
       boost::program_options::value<bool>()->default_value(false),
       "specify if the grph.10t ACE library is available")
      ("grph_10t_filepath",
       boost::program_options::value<std::string>(),
       "specify the location of the grph.10t ACE library")
      ("grph_10t_filestartline",
       boost::program_options::value<int>(),
       "specify the file start line of the grph.10t ACE library")
      ("lwtr_10t_available",
       boost::program_options::value<bool>()->default_value(false),
       "specify if the lwtr.10t ACE library is available")
      ("lwtr_10t_filepath",
       boost::program_options::value<std::string>(),
       "specify the location of the lwtr.10t ACE library")
      ("lwtr_10t_filestartline",
       boost::program_options::value<int>(),
       "specify the file start line of the lwtr.10t ACE library")
      ("poly_10t_available",
       boost::program_options::value<bool>()->default_value(false),
       "specify if the poly.10t ACE library is available")
      ("poly_10t_filepath",
       boost::program_options::value<std::string>(),
       "specify the location of the poly.10t ACE library")
      ("poly_10t_filestartline",
       boost::program_options::value<int>(),
       "specify the file start line of the poly.10t ACE library")
      ("native_dir,n",
       boost::program_options::value<std::string>(),
       "specify the relative location of the native test data directory")
      ("database_name,o",
       boost::program_options::value<std::string>()->default_value("database.xml"),
       "Set the database output file name");

    // Parse the command line arguments
    boost::program_options::store(
         boost::program_options::command_line_parser(argc, argv).options(command_line_options).run(),
         command_line_arguments );

    boost::program_options::notify( command_line_arguments );
  }

  // Set the database output file name
  std::string database_output_file_name =
    command_line_arguments["database_name"].as<std::string>();

  TEST_FOR_EXCEPTION( database_output_file_name.find( " " ) <
                      database_output_file_name.size(),
                      std::runtime_error,
                      "The database output file name cannot contain any "
                      "white space!" );

  // Set the native test data directory path
  TEST_FOR_EXCEPTION( !command_line_arguments.count( "native_dir" ),
                      std::runtime_error,
                      "The native test data directory must be specified!" );

  boost::filesystem::path native_test_data_dir =
    command_line_arguments["native_dir"].as<std::string>();

  TEST_FOR_EXCEPTION( !boost::filesystem::is_directory( native_test_data_dir ),
                      std::runtime_error,
                      "The native test data directory is not valid!" );

  native_test_data_dir = boost::filesystem::relative( native_test_data_dir );

  // Initialize the database
  Data::ScatteringCenterPropertiesDatabase database;

  // Add the ace data properties
  Details::addH1ACEFile( command_line_arguments["1001_70c_available"].as<bool>(),
                         command_line_arguments["1001_70c_filepath"].as<std::string>(),
                         command_line_arguments["1001_70c_filestartline"].as<int>(),
                         database );
  Details::addH2OSabACEFile( command_line_arguments["lwtr_10t_available"].as<bool>(),
                             command_line_arguments["lwtr_10t_filepath"].as<std::string>(),
                             command_line_arguments["lwtr_10t_filestartline"].as<int>(),
                             database );
  Details::addH2PhotonuclearACEFile( command_line_arguments["1002_24u_available"].as<bool>(),
                                     command_line_arguments["1002_24u_filepath"].as<std::string>(),
                                     command_line_arguments["1002_24u_filestartline"].as<int>(),
                                     database );
  Details::addHEPR14ACEFile( command_line_arguments["1000_14p_available"].as<bool>(),
                             command_line_arguments["1000_14p_filepath"].as<std::string>(),
                             command_line_arguments["1000_14p_filestartline"].as<int>(),
                             database );
  Details::addHEPRACEFile( command_line_arguments["1000_12p_available"].as<bool>(),
                           command_line_arguments["1000_12p_filepath"].as<std::string>(),
                           command_line_arguments["1000_12p_filestartline"].as<int>(),
                           database );
  Details::addPolySabACEFile( command_line_arguments["poly_10t_available"].as<bool>(),
                              command_line_arguments["poly_10t_filepath"].as<std::string>(),
                              command_line_arguments["poly_10t_filestartline"].as<int>(),
                              database );

  Details::addBElectronACEFile( command_line_arguments["5000_03e_available"].as<bool>(),
                                command_line_arguments["5000_03e_filepath"].as<std::string>(),
                                command_line_arguments["5000_03e_filestartline"].as<int>(),
                                database );
  Details::addBEPRACEFile( command_line_arguments["5000_12p_available"].as<bool>(),
                           command_line_arguments["5000_12p_filepath"].as<std::string>(),
                           command_line_arguments["5000_12p_filestartline"].as<int>(),
                           database );

  Details::addC12PhotonuclearACEFile( command_line_arguments["6012_24u_available"].as<bool>(),
                                      command_line_arguments["6012_24u_filepath"].as<std::string>(),
                                      command_line_arguments["6012_24u_filestartline"].as<int>(),
                                      database );
  Details::addCEPRACEFile( command_line_arguments["6000_12p_available"].as<bool>(),
                           command_line_arguments["6000_12p_filepath"].as<std::string>(),
                           command_line_arguments["6000_12p_filestartline"].as<int>(),
                           database );
  Details::addGrphSabACEFile( command_line_arguments["grph_10t_available"].as<bool>(),
                              command_line_arguments["grph_10t_filepath"].as<std::string>(),
                              command_line_arguments["grph_10t_filestartline"].as<int>(),
                              database );

  Details::addO16ACEFile( command_line_arguments["8016_70c_available"].as<bool>(),
                          command_line_arguments["8016_70c_filepath"].as<std::string>(),
                          command_line_arguments["8016_70c_filestartline"].as<int>(),
                          database );
  Details::addOEPRACEFile( command_line_arguments["8000_12p_available"].as<bool>(),
                           command_line_arguments["8000_12p_filepath"].as<std::string>(),
                           command_line_arguments["8000_12p_filestartline"].as<int>(),
                           database );

  Details::addTestAuEPR14ACEFile( command_line_arguments["79000_14p_available"].as<bool>(),
                                  command_line_arguments["79000_14p_filepath"].as<std::string>(),
                                  command_line_arguments["79000_14p_filestartline"].as<int>(),
                                  database );

  Details::addPb208ACEFile( command_line_arguments["82208_70c_available"].as<bool>(),
                            command_line_arguments["82208_70c_filepath"].as<std::string>(),
                            command_line_arguments["82208_70c_filestartline"].as<int>(),
                            database );
  Details::addPbElectronACEFile( command_line_arguments["82000_03e_available"].as<bool>(),
                                 command_line_arguments["82000_03e_filepath"].as<std::string>(),
                                 command_line_arguments["82000_03e_filestartline"].as<int>(),
                                 database );
  Details::addPbEPR14ACEFile( command_line_arguments["82000_14p_available"].as<bool>(),
                              command_line_arguments["82000_14p_filepath"].as<std::string>(),
                              command_line_arguments["82000_14p_filestartline"].as<int>(),
                              database );
  Details::addPbEPRACEFile( command_line_arguments["82000_12p_available"].as<bool>(),
                            command_line_arguments["82000_12p_filepath"].as<std::string>(),
                            command_line_arguments["82000_12p_filestartline"].as<int>(),
                            database );
  Details::addPbPhotoatomicACEFile( command_line_arguments["82000_04p_available"].as<bool>(),
                                    command_line_arguments["82000_04p_filepath"].as<std::string>(),
                                    command_line_arguments["82000_04p_filestartline"].as<int>(),
                                    database );

  Details::addU238ACEFile( command_line_arguments["92238_70c_available"].as<bool>(),
                           command_line_arguments["92238_70c_filepath"].as<std::string>(),
                           command_line_arguments["92238_70c_filestartline"].as<int>(),
                           database );
  Details::addUEPRACEFile( command_line_arguments["92000_12p_available"].as<bool>(),
                           command_line_arguments["92000_12p_filepath"].as<std::string>(),
                           command_line_arguments["92000_12p_filestartline"].as<int>(),
                           database );

  // Add the native data properties
  addHNativeTestFiles( native_test_data_dir, database );
  addCNativeTestFiles( native_test_data_dir, database );
  addAlNativeTestFiles( native_test_data_dir, database );
  addSiNativeTestFiles( native_test_data_dir, database );
  addPbNativeTestFiles( native_test_data_dir, database );

  // Export the database to the current directory
  database.saveToFile( database_output_file_name, true );
}

namespace Details{

// Add the 79000.14p properties
void addTestAuEPR14ACEFile( const bool library_available,
                            const std::string& library_filepath,
                            const int library_filestartline,
                            Data::ScatteringCenterPropertiesDatabase& database )
{
  if( library_available )
  {
    boost::filesystem::path ace_test_data_file = library_filepath;
    ace_test_data_file = boost::filesystem::relative( ace_test_data_file );

    TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                        std::runtime_error,
                        "The 79000.14p data file ("
                        << library_filepath <<
                        ") could not be found!" );

    if( !database.doAtomPropertiesExist( Data::Au_ATOM ) )
      database.initializeAtomProperties( Data::Au_ATOM, 195.275000 );
    
    Data::AtomProperties& atom_properties =
      database.getAtomProperties( Data::Au_ATOM );

    auto atomic_weight =
      195.275000*Utility::PhysicalConstants::neutron_rest_mass_amu_q;
    
    std::shared_ptr<const Data::PhotoatomicDataProperties>
      photoatomic_properties( new Data::ACEPhotoatomicDataProperties(
                                                         atomic_weight,
                                                         ace_test_data_file,
                                                         library_filestartline,
                                                         "79000.14p" ) );
    
    atom_properties.setPhotoatomicDataProperties( photoatomic_properties );

    std::shared_ptr<const Data::ElectroatomicDataProperties>
      electroatomic_properties( new Data::ACEElectroatomicDataProperties(
                                                         atomic_weight,
                                                         ace_test_data_file,
                                                         library_filestartline,
                                                         "79000.14p" ) );

    atom_properties.setElectroatomicDataProperties( electroatomic_properties );
  }
}

// Add the 5000.03e properties
void addBElectronACEFile( const bool library_available,
                          const std::string& library_filepath,
                          const int library_filestartline,
                          Data::ScatteringCenterPropertiesDatabase& database )
{
  if( library_available )
  {
    boost::filesystem::path ace_test_data_file = library_filepath;
    ace_test_data_file = boost::filesystem::relative( ace_test_data_file );

    TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                        std::runtime_error,
                        "The 5000.03e data file ("
                        << library_filepath <<
                        ") could not be found!" );
    
    if( !database.doAtomPropertiesExist( Data::B_ATOM ) )
      database.initializeAtomProperties( Data::B_ATOM, 10.717168 );
    
    Data::AtomProperties& atom_properties =
      database.getAtomProperties( Data::B_ATOM );
    
    auto atomic_weight =
      10.717168*Utility::PhysicalConstants::neutron_rest_mass_amu_q;
    
    std::shared_ptr<const Data::ElectroatomicDataProperties>
      electroatomic_properties( new Data::ACEElectroatomicDataProperties(
                                                         atomic_weight,
                                                         ace_test_data_file,
                                                         library_filestartline,
                                                         "5000.03e" ) );

    atom_properties.setElectroatomicDataProperties( electroatomic_properties );
  }
}

// Add the 5000.12p properties
void addBEPRACEFile( const bool library_available,
                     const std::string& library_filepath,
                     const int library_filestartline,
                     Data::ScatteringCenterPropertiesDatabase& database )
{
  if( library_available )
  {
    boost::filesystem::path ace_test_data_file = library_filepath;
    ace_test_data_file = boost::filesystem::relative( ace_test_data_file );

    TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                        std::runtime_error,
                        "The 5000.12p data file ("
                        << library_filepath <<
                        ") could not be found!" );

    if( !database.doAtomPropertiesExist( Data::B_ATOM ) )
      database.initializeAtomProperties( Data::B_ATOM, 10.717100 );

    Data::AtomProperties& atom_properties =
      database.getAtomProperties( Data::B_ATOM );

    auto atomic_weight =
      10.717100*Utility::PhysicalConstants::neutron_rest_mass_amu_q;
    
    std::shared_ptr<const Data::PhotoatomicDataProperties>
      photoatomic_properties( new Data::ACEPhotoatomicDataProperties(
                                                         atomic_weight,
                                                         ace_test_data_file,
                                                         library_filestartline,
                                                         "5000.12p" ) );

    atom_properties.setPhotoatomicDataProperties( photoatomic_properties );

    std::shared_ptr<const Data::ElectroatomicDataProperties>
      electroatomic_properties( new Data::ACEElectroatomicDataProperties(
                                                         atomic_weight,
                                                         ace_test_data_file,
                                                         library_filestartline,
                                                         "5000.12p" ) );

    atom_properties.setElectroatomicDataProperties( electroatomic_properties );
  }
}

// Add the 6012.24u properties
void addC12PhotonuclearACEFile(
                           const bool library_available,
                           const std::string& library_filepath,
                           const int library_filestartline,
                           Data::ScatteringCenterPropertiesDatabase& database )
{
  if( library_available )
  {
    boost::filesystem::path ace_test_data_file = library_filepath;
    ace_test_data_file = boost::filesystem::relative( ace_test_data_file );

    TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                        std::runtime_error,
                        "The 6012.24u data file ("
                        << library_filepath <<
                        ") could not be found!" );

    if( !database.doNuclidePropertiesExist( 6012 ) )
      database.initializeNuclideProperties( 6012, 11.896910 );

    Data::NuclideProperties& nuclide_properties =
      database.getNuclideProperties( 6012 );

    auto atomic_weight =
      11.896910*Utility::PhysicalConstants::neutron_rest_mass_amu_q;

    std::shared_ptr<const Data::PhotonuclearDataProperties>
      photonuclear_properties( new Data::ACEPhotonuclearDataProperties(
                                                         atomic_weight,
                                                         ace_test_data_file,
                                                         library_filestartline,
                                                         "6012.24u" ) );

    nuclide_properties.setPhotonuclearDataProperties( photonuclear_properties );
  }
}

// Add the 6000.12p properties
void addCEPRACEFile( const bool library_available,
                     const std::string& library_filepath,
                     const int library_filestartline,
                     Data::ScatteringCenterPropertiesDatabase& database )
{
  if( library_available )
  {
    boost::filesystem::path ace_test_data_file = library_filepath;
    ace_test_data_file = boost::filesystem::relative( ace_test_data_file );

    TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                        std::runtime_error,
                        "The 6000.12p data file ("
                        << library_filepath <<
                        ") could not be found!" );

    if( !database.doAtomPropertiesExist( Data::C_ATOM ) )
      database.initializeAtomProperties( Data::C_ATOM, 11.907800 );

    Data::AtomProperties& atom_properties =
      database.getAtomProperties( Data::C_ATOM );
    
    auto atomic_weight =
      11.907800*Utility::PhysicalConstants::neutron_rest_mass_amu_q;
    
    std::shared_ptr<const Data::PhotoatomicDataProperties>
      photoatomic_properties( new Data::ACEPhotoatomicDataProperties(
                                                          atomic_weight,
                                                          ace_test_data_file,
                                                          library_filestartline,
                                                          "6000.12p" ) );

    atom_properties.setPhotoatomicDataProperties( photoatomic_properties );
    
    std::shared_ptr<const Data::ElectroatomicDataProperties>
      electroatomic_properties( new Data::ACEElectroatomicDataProperties(
                                                         atomic_weight,
                                                         ace_test_data_file,
                                                         library_filestartline,
                                                         "6000.12p" ) );

    atom_properties.setElectroatomicDataProperties( electroatomic_properties );
  }
}

// Add the grph.10t properties
void addGrphSabACEFile( const bool library_available,
                        const std::string& library_filepath,
                        const int library_filestartline,
                        Data::ScatteringCenterPropertiesDatabase& database )
{
  if( library_available )
  {
    boost::filesystem::path ace_test_data_file = library_filepath;
    ace_test_data_file = boost::filesystem::relative( ace_test_data_file );

    TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                        std::runtime_error,
                        "The grph.10t data file ("
                        << library_filepath <<
                        ") could not be found!" );

    std::shared_ptr<const Data::ThermalNuclearDataProperties>
      thermal_nuclear_properties( new Data::ACEThermalNuclearDataProperties(
                                                         {6000, 6012, 6013},
                                                         2.53010E-08*MeV,
                                                         ace_test_data_file,
                                                         library_filestartline,
                                                         "grph.10t" ) );

    if( !database.doNuclidePropertiesExist( Data::C_ATOM ) )
      database.initializeNuclideProperties( Data::C_ATOM, 11.907800 );

    database.getNuclideProperties( Data::C_ATOM ).setThermalNuclearDataProperties( thermal_nuclear_properties );

    if( !database.doNuclidePropertiesExist( 6012 ) )
      database.initializeNuclideProperties( 6012, 11.89691424 );

    database.getNuclideProperties( 6012 ).setThermalNuclearDataProperties( thermal_nuclear_properties );

    if( !database.doNuclidePropertiesExist( 6013 ) )
      database.initializeNuclideProperties( 6013, 12.89164978 );

    database.getNuclideProperties( 6013 ).setThermalNuclearDataProperties( thermal_nuclear_properties );
  }
}

// Add the 1001.70c properties
void addH1ACEFile( const bool library_available,
                   const std::string& library_filepath,
                   const int library_filestartline,
                   Data::ScatteringCenterPropertiesDatabase& database )
{
  if( library_available )
  {
    boost::filesystem::path ace_test_data_file = library_filepath;
    ace_test_data_file = boost::filesystem::relative( ace_test_data_file );

    TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                        std::runtime_error,
                        "The 1001.70c data file ("
                        << ace_test_data_file <<
                        ") could not be found!" );

    if( !database.doNuclidePropertiesExist( 1001 ) )
      database.initializeNuclideProperties( 1001, 0.999167 );

    Data::NuclideProperties& nuclide_properties =
      database.getNuclideProperties( 1001 );

    std::shared_ptr<const Data::NuclearDataProperties>
      nuclear_properties( new Data::ACENuclearDataProperties(
                                                         0.999167,
                                                         2.53010E-08*MeV,
                                                         ace_test_data_file,
                                                         library_filestartline,
                                                         "1001.70c" ) );
  
    nuclide_properties.setNuclearDataProperties( nuclear_properties );
  }
}

// Add the lwtr.10t properties
void addH2OSabACEFile( const bool library_available,
                       const std::string& library_filepath,
                       const int library_filestartline,
                       Data::ScatteringCenterPropertiesDatabase& database )
{
  if( library_available )
  {
    boost::filesystem::path ace_test_data_file = library_filepath;
    ace_test_data_file = boost::filesystem::relative( ace_test_data_file );

    TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                        std::runtime_error,
                        "The lwtr.10t data file ("
                        << library_filepath <<
                        ") could not be found!" );

    std::shared_ptr<const Data::ThermalNuclearDataProperties>
      thermal_nuclear_properties( new Data::ACEThermalNuclearDataProperties(
                                                         {1001},
                                                         2.53010E-08*MeV,
                                                         ace_test_data_file,
                                                         library_filestartline,
                                                         "lwtr.10t" ) );

    if( !database.doNuclidePropertiesExist( 1001 ) )
      database.initializeNuclideProperties( 1001, 0.999167 );

    database.getNuclideProperties( 1001 ).setThermalNuclearDataProperties( thermal_nuclear_properties );
  }
}

// Add the 1002.24u properties
void addH2PhotonuclearACEFile(
                           const bool library_available,
                           const std::string& library_filepath,
                           const int library_filestartline,
                           Data::ScatteringCenterPropertiesDatabase& database )
{
  if( library_available )
  {
    boost::filesystem::path ace_test_data_file = library_filepath;
    ace_test_data_file = boost::filesystem::relative( ace_test_data_file );

    TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                        std::runtime_error,
                        "The 1002.24u data file ("
                        << library_filepath <<
                        ") could not be found!" );

    if( !database.doNuclidePropertiesExist( 1002 ) )
      database.initializeNuclideProperties( 1002, 1.996300 );

    Data::NuclideProperties& nuclide_properties =
      database.getNuclideProperties( 1002 );

    auto atomic_weight =
      1.996300*Utility::PhysicalConstants::neutron_rest_mass_amu_q;
    
    std::shared_ptr<const Data::PhotonuclearDataProperties>
      photonuclear_properties( new Data::ACEPhotonuclearDataProperties(
                                                         atomic_weight,
                                                         ace_test_data_file,
                                                         library_filestartline,
                                                         "1002.24u" ) );
  
    nuclide_properties.setPhotonuclearDataProperties( photonuclear_properties );
  }
}

// Add the 1000.14p properties
void addHEPR14ACEFile( const bool library_available,
                       const std::string& library_filepath,
                       const int library_filestartline,
                       Data::ScatteringCenterPropertiesDatabase& database )
{
  if( library_available )
  {
    boost::filesystem::path ace_test_data_file = library_filepath;
    ace_test_data_file = boost::filesystem::relative( ace_test_data_file );
  
    TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                        std::runtime_error,
                        "The 1000.14p data file ("
                        << library_filepath <<
                        ") could not be found!" );
  
    if( !database.doAtomPropertiesExist( Data::H_ATOM ) )
      database.initializeAtomProperties( Data::H_ATOM, 0.999242 );
    
    Data::AtomProperties& atom_properties =
      database.getAtomProperties( Data::H_ATOM );
    
    auto atomic_weight =
      0.999242*Utility::PhysicalConstants::neutron_rest_mass_amu_q;

    std::shared_ptr<const Data::PhotoatomicDataProperties>
      photoatomic_properties( new Data::ACEPhotoatomicDataProperties(
                                                         atomic_weight,
                                                         ace_test_data_file,
                                                         library_filestartline,
                                                         "1000.14p" ) );
    
    atom_properties.setPhotoatomicDataProperties( photoatomic_properties );

    std::shared_ptr<const Data::ElectroatomicDataProperties>
      electroatomic_properties( new Data::ACEElectroatomicDataProperties(
                                                         atomic_weight,
                                                         ace_test_data_file,
                                                         library_filestartline,
                                                         "1000.14p" ) );

    atom_properties.setElectroatomicDataProperties( electroatomic_properties );
  }
}
  
// Add the 1000.12p properties
void addHEPRACEFile( const bool library_available,
                     const std::string& library_filepath,
                     const int library_filestartline,
                     Data::ScatteringCenterPropertiesDatabase& database )
{
  if( library_available )
  {
    boost::filesystem::path ace_test_data_file = library_filepath;
    ace_test_data_file = boost::filesystem::relative( ace_test_data_file );
    
    TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                        std::runtime_error,
                        "The 1000.12p data file ("
                        << library_filepath <<
                        ") could not be found!" );
    
    if( !database.doAtomPropertiesExist( Data::H_ATOM ) )
      database.initializeAtomProperties( Data::H_ATOM, 0.999242 );
    
    Data::AtomProperties& atom_properties =
      database.getAtomProperties( Data::H_ATOM );
    
    auto atomic_weight =
      0.999242*Utility::PhysicalConstants::neutron_rest_mass_amu_q;
    
    std::shared_ptr<const Data::PhotoatomicDataProperties>
      photoatomic_properties( new Data::ACEPhotoatomicDataProperties(
                                                         atomic_weight,
                                                         ace_test_data_file,
                                                         library_filestartline,
                                                         "1000.12p" ) );
    
    atom_properties.setPhotoatomicDataProperties( photoatomic_properties );
    
    std::shared_ptr<const Data::ElectroatomicDataProperties>
      electroatomic_properties( new Data::ACEElectroatomicDataProperties(
                                                         atomic_weight,
                                                         ace_test_data_file,
                                                         library_filestartline,
                                                         "1000.12p" ) );
    
    atom_properties.setElectroatomicDataProperties( electroatomic_properties );
  }
}

// Add the poly.10t properties
void addPolySabACEFile( const bool library_available,
                        const std::string& library_filepath,
                        const int library_filestartline,
                        Data::ScatteringCenterPropertiesDatabase& database )
{
  if( library_available )
  {
    boost::filesystem::path ace_test_data_file = library_filepath;
    ace_test_data_file = boost::filesystem::relative( ace_test_data_file );

    TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                        std::runtime_error,
                        "The poly.10t data file ("
                        << library_filepath <<
                        ") could not be found!" );

    std::shared_ptr<const Data::ThermalNuclearDataProperties>
      thermal_nuclear_properties( new Data::ACEThermalNuclearDataProperties(
                                                         {1001},
                                                         2.53010E-08*MeV,
                                                         ace_test_data_file,
                                                         library_filestartline,
                                                         "poly.10t" ) );
    if( !database.doNuclidePropertiesExist( 1001 ) )
      database.initializeNuclideProperties( 1001, 0.999167 );

    database.getNuclideProperties( 1001 ).setThermalNuclearDataProperties( thermal_nuclear_properties );
  }
}

// Add the 8016.70c properties
void addO16ACEFile( const bool library_available,
                    const std::string& library_filepath,
                    const int library_filestartline,
                    Data::ScatteringCenterPropertiesDatabase& database )
{
  if( library_available )
  {
    boost::filesystem::path ace_test_data_file = library_filepath;
    ace_test_data_file = boost::filesystem::relative( ace_test_data_file );

    TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                        std::runtime_error,
                        "The 8016.70c data file ("
                        << library_filepath <<
                        ") could not be found!" );

    if( !database.doNuclidePropertiesExist( 8016 ) )
      database.initializeNuclideProperties( 8016, 15.857510 );

    Data::NuclideProperties& nuclide_properties =
      database.getNuclideProperties( 8016 );

    std::shared_ptr<const Data::NuclearDataProperties>
      nuclear_properties( new Data::ACENuclearDataProperties(
                                                         15.857510,
                                                         2.53010E-08*MeV,
                                                         ace_test_data_file,
                                                         library_filestartline,
                                                         "8016.70c" ) );
  
    nuclide_properties.setNuclearDataProperties( nuclear_properties );
  }
}

// Add the 8000.12p properties
void addOEPRACEFile( const bool library_available,
                     const std::string& library_filepath,
                     const int library_filestartline,
                     Data::ScatteringCenterPropertiesDatabase& database )
{
  if( library_available )
  {
    boost::filesystem::path ace_test_data_file = library_filepath;
    ace_test_data_file = boost::filesystem::relative( ace_test_data_file );

    TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                        std::runtime_error,
                        "The 8000.12p data file ("
                        << library_filepath <<
                        ") could not be found!" );

    if( !database.doAtomPropertiesExist( Data::O_ATOM ) )
      database.initializeAtomProperties( Data::O_ATOM, 15.862000 );

    Data::AtomProperties& atom_properties =
      database.getAtomProperties( Data::O_ATOM );

    auto atomic_weight =
      15.862000*Utility::PhysicalConstants::neutron_rest_mass_amu_q;

    std::shared_ptr<const Data::PhotoatomicDataProperties>
      photoatomic_properties( new Data::ACEPhotoatomicDataProperties(
                                                         atomic_weight,
                                                         ace_test_data_file,
                                                         library_filestartline,
                                                         "8000.12p" ) );

    atom_properties.setPhotoatomicDataProperties( photoatomic_properties );

    std::shared_ptr<const Data::ElectroatomicDataProperties>
      electroatomic_properties( new Data::ACEElectroatomicDataProperties(
                                                         atomic_weight,
                                                         ace_test_data_file,
                                                         library_filestartline,
                                                         "8000.12p" ) );

    atom_properties.setElectroatomicDataProperties( electroatomic_properties );
  }
}

// Add the 82208.70c properties
void addPb208ACEFile( const bool library_available,
                      const std::string& library_filepath,
                      const int library_filestartline,
                      Data::ScatteringCenterPropertiesDatabase& database )
{
  if( library_available )
  {
    boost::filesystem::path ace_test_data_file = library_filepath;
    ace_test_data_file = boost::filesystem::relative( ace_test_data_file );

    TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                        std::runtime_error,
                        "The 82208.70c data file ("
                        << library_filepath <<
                        ") could not be found!" );

    if( !database.doNuclidePropertiesExist( 82208 ) )
      database.initializeNuclideProperties( 82208, 206.190000 );

    Data::NuclideProperties& nuclide_properties =
      database.getNuclideProperties( 82208 );

    std::shared_ptr<const Data::NuclearDataProperties>
      nuclear_properties( new Data::ACENuclearDataProperties(
                                                         206.190000,
                                                         2.53010E-08*MeV,
                                                         ace_test_data_file,
                                                         library_filestartline,
                                                         "82208.70c" ) );
  
    nuclide_properties.setNuclearDataProperties( nuclear_properties );
  }
}

// Add the 82000.03e properties
void addPbElectronACEFile( const bool library_available,
                           const std::string& library_filepath,
                           const int library_filestartline,
                           Data::ScatteringCenterPropertiesDatabase& database )
{
  if( library_available )
  {
    boost::filesystem::path ace_test_data_file = library_filepath;
    ace_test_data_file = boost::filesystem::relative( ace_test_data_file );

    TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                        std::runtime_error,
                        "The 82000.03e data file ("
                        << library_filepath <<
                        ") could not be found!" );

    if( !database.doAtomPropertiesExist( Data::Pb_ATOM ) )
      database.initializeAtomProperties( Data::Pb_ATOM, 205.436151 );

    Data::AtomProperties& atom_properties =
      database.getAtomProperties( Data::Pb_ATOM );

    auto atomic_weight =
      205.436151*Utility::PhysicalConstants::neutron_rest_mass_amu_q;

    std::shared_ptr<const Data::ElectroatomicDataProperties>
      electroatomic_properties( new Data::ACEElectroatomicDataProperties(
                                                         atomic_weight,
                                                         ace_test_data_file,
                                                         library_filestartline,
                                                         "82000.03e" ) );

    atom_properties.setElectroatomicDataProperties( electroatomic_properties );
  }
}

// Add the 82000.14p properties
void addPbEPR14ACEFile( const bool library_available,
                        const std::string& library_filepath,
                        const int library_filestartline,
                        Data::ScatteringCenterPropertiesDatabase& database )
{
  if( library_available )
  {
    boost::filesystem::path ace_test_data_file = library_filepath;
    ace_test_data_file = boost::filesystem::relative( ace_test_data_file );

    TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                        std::runtime_error,
                        "The 82000.14p data file ("
                        << library_filepath <<
                        ") could not be found!" );

    if( !database.doAtomPropertiesExist( Data::Pb_ATOM ) )
      database.initializeAtomProperties( Data::Pb_ATOM, 205.420000 );

    Data::AtomProperties& atom_properties =
      database.getAtomProperties( Data::Pb_ATOM );

    auto atomic_weight =
      205.420000*Utility::PhysicalConstants::neutron_rest_mass_amu_q;

    std::shared_ptr<const Data::PhotoatomicDataProperties>
      photoatomic_properties( new Data::ACEPhotoatomicDataProperties(
                                                         atomic_weight,
                                                         ace_test_data_file,
                                                         library_filestartline,
                                                         "82000.14p" ) );

    atom_properties.setPhotoatomicDataProperties( photoatomic_properties );

    std::shared_ptr<const Data::ElectroatomicDataProperties>
      electroatomic_properties( new Data::ACEElectroatomicDataProperties(
                                                         atomic_weight,
                                                         ace_test_data_file,
                                                         library_filestartline,
                                                         "82000.14p" ) );

    atom_properties.setElectroatomicDataProperties( electroatomic_properties );
  }
}

// Add the 82000.12p properties
void addPbEPRACEFile( const bool library_available,
                      const std::string& library_filepath,
                      const int library_filestartline,
                      Data::ScatteringCenterPropertiesDatabase& database )
{
  if( library_available )
  {
    boost::filesystem::path ace_test_data_file = library_filepath;
    ace_test_data_file = boost::filesystem::relative( ace_test_data_file );

    TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                        std::runtime_error,
                        "The 82000.12p data file ("
                        << library_filepath <<
                        ") could not be found!" );

    if( !database.doAtomPropertiesExist( Data::Pb_ATOM ) )
      database.initializeAtomProperties( Data::Pb_ATOM, 205.420000 );

    Data::AtomProperties& atom_properties =
      database.getAtomProperties( Data::Pb_ATOM );

    auto atomic_weight =
      205.420000*Utility::PhysicalConstants::neutron_rest_mass_amu_q;

    std::shared_ptr<const Data::PhotoatomicDataProperties>
      photoatomic_properties( new Data::ACEPhotoatomicDataProperties(
                                                         atomic_weight,
                                                         ace_test_data_file,
                                                         library_filestartline,
                                                         "82000.12p" ) );

    atom_properties.setPhotoatomicDataProperties( photoatomic_properties );

    std::shared_ptr<const Data::ElectroatomicDataProperties>
      electroatomic_properties( new Data::ACEElectroatomicDataProperties(
                                                         atomic_weight,
                                                         ace_test_data_file,
                                                         library_filestartline,
                                                         "82000.12p" ) );

    atom_properties.setElectroatomicDataProperties( electroatomic_properties );
  }
}

// Add the 82000.04p properties
void addPbPhotoatomicACEFile(
                          const bool library_available,
                          const std::string& library_filepath,
                          const int library_filestartline,
                          Data::ScatteringCenterPropertiesDatabase& database )
{
  if( library_available )
  {
    boost::filesystem::path ace_test_data_file = library_filepath;
    ace_test_data_file = boost::filesystem::relative( ace_test_data_file );

    TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                        std::runtime_error,
                        "The 82000.04p data file ("
                        << library_filepath <<
                        ") could not be found!" );

    if( !database.doAtomPropertiesExist( Data::Pb_ATOM ) )
      database.initializeAtomProperties( Data::Pb_ATOM, 205.420000 );

    Data::AtomProperties& atom_properties =
      database.getAtomProperties( Data::Pb_ATOM );

    auto atomic_weight =
      205.420000*Utility::PhysicalConstants::neutron_rest_mass_amu_q;

    std::shared_ptr<const Data::PhotoatomicDataProperties>
      photoatomic_properties( new Data::ACEPhotoatomicDataProperties(
                                                         atomic_weight,
                                                         ace_test_data_file,
                                                         library_filestartline,
                                                         "82000.04p" ) );

    atom_properties.setPhotoatomicDataProperties( photoatomic_properties );
  }
}

// Add the 92238.70c properties
void addU238ACEFile( const bool library_available,
                     const std::string& library_filepath,
                     const int library_filestartline,
                     Data::ScatteringCenterPropertiesDatabase& database )
{
  if( library_available )
  {
    boost::filesystem::path ace_test_data_file = library_filepath;
    ace_test_data_file = boost::filesystem::relative( ace_test_data_file );

    TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                        std::runtime_error,
                        "The 92238.70c data file ("
                        << library_filepath <<
                        ") could not be found!" );

    if( !database.doNuclidePropertiesExist( 92238 ) )
      database.initializeNuclideProperties( 92238, 236.005800 );

    Data::NuclideProperties& nuclide_properties =
      database.getNuclideProperties( 92238 );

    std::shared_ptr<const Data::NuclearDataProperties>
      nuclear_properties( new Data::ACENuclearDataProperties(
                                                         236.005800,
                                                         2.53010E-08*MeV,
                                                         ace_test_data_file,
                                                         library_filestartline,
                                                         "92238.70c" ) );
  
    nuclide_properties.setNuclearDataProperties( nuclear_properties );
  }
}

// Add the 92000.12p properties
void addUEPRACEFile( const bool library_available,
                     const std::string& library_filepath,
                     const int library_filestartline,
                     Data::ScatteringCenterPropertiesDatabase& database )
{
  if( library_available )
  {
    boost::filesystem::path ace_test_data_file = library_filepath;
    ace_test_data_file = boost::filesystem::relative( ace_test_data_file );

    TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                        std::runtime_error,
                        "The 92000.12p data file ("
                        << library_filepath <<
                        ") could not be found!" );

    if( !database.doAtomPropertiesExist( Data::U_ATOM ) )
      database.initializeAtomProperties( Data::U_ATOM, 235.984000 );

    Data::AtomProperties& atom_properties =
      database.getAtomProperties( Data::U_ATOM );

    auto atomic_weight =
      235.984000*Utility::PhysicalConstants::neutron_rest_mass_amu_q;

    std::shared_ptr<const Data::PhotoatomicDataProperties>
      photoatomic_properties( new Data::ACEPhotoatomicDataProperties(
                                                         atomic_weight,
                                                         ace_test_data_file,
                                                         library_filestartline,
                                                         "92000.12p" ) );

    atom_properties.setPhotoatomicDataProperties( photoatomic_properties );

    std::shared_ptr<const Data::ElectroatomicDataProperties>
      electroatomic_properties( new Data::ACEElectroatomicDataProperties(
                                                         atomic_weight,
                                                         ace_test_data_file,
                                                         library_filestartline,
                                                         "92000.12p" ) );

    atom_properties.setElectroatomicDataProperties( electroatomic_properties );
  }
}

// Add the "test_epr_1_native.xml" properties
void addHNativeEPRFile( const boost::filesystem::path& native_test_data_dir,
                        Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path native_test_data_file = native_test_data_dir;
  native_test_data_file /= "test_epr_1_native.xml";

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( native_test_data_file ),
                      std::runtime_error,
                      "The \"test_epr_1_native.xml\" data file could "
                      "not be found (check native test data directory "
                      "path)!" );

  if( !database.doAtomPropertiesExist( Data::H_ATOM ) )
    database.initializeAtomProperties( Data::H_ATOM, 0.999242 );

  Data::AtomProperties& atom_properties =
    database.getAtomProperties( Data::H_ATOM );

  auto atomic_weight =
    0.999242*Utility::PhysicalConstants::neutron_rest_mass_amu_q;

  std::shared_ptr<const Data::PhotoatomicDataProperties>
    photoatomic_properties( new Data::NativeEPRPhotoatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         0,
                                                         Data::H_ATOM ) );

  atom_properties.setPhotoatomicDataProperties( photoatomic_properties );

  std::shared_ptr<const Data::ElectroatomicDataProperties>
    electroatomic_properties( new Data::NativeEPRElectroatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         0,
                                                         Data::H_ATOM ) );

  atom_properties.setElectroatomicDataProperties( electroatomic_properties );
}

// Add the "test_aepr_1_native.xml" properties
void addHNativeAEPRFile( const boost::filesystem::path& native_test_data_dir,
                         Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path native_test_data_file = native_test_data_dir;
  native_test_data_file /= "test_aepr_1_native.xml";

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( native_test_data_file ),
                      std::runtime_error,
                      "The \"test_aepr_1_native.xml\" data file could "
                      "not be found (check native test data directory "
                      "path)!" );

  if( !database.doAtomPropertiesExist( Data::H_ATOM ) )
    database.initializeAtomProperties( Data::H_ATOM, 0.999242 );

  Data::AtomProperties& atom_properties =
    database.getAtomProperties( Data::H_ATOM );

  auto atomic_weight =
    0.999242*Utility::PhysicalConstants::neutron_rest_mass_amu_q;

  std::shared_ptr<const Data::AdjointPhotoatomicDataProperties>
    photoatomic_properties( new Data::NativeEPRAdjointPhotoatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         0,
                                                         Data::H_ATOM ) );

  atom_properties.setAdjointPhotoatomicDataProperties( photoatomic_properties );

  std::shared_ptr<const Data::AdjointElectroatomicDataProperties>
    electroatomic_properties( new Data::NativeEPRAdjointElectroatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         0,
                                                         Data::H_ATOM ) );

  atom_properties.setAdjointElectroatomicDataProperties( electroatomic_properties );
}

// Add the "test_epr_6_native.xml" properties
void addCNativeEPRFile( const boost::filesystem::path& native_test_data_dir,
                        Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path native_test_data_file = native_test_data_dir;
  native_test_data_file /= "test_epr_6_native.xml";

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( native_test_data_file ),
                      std::runtime_error,
                      "The \"test_epr_6_native.xml\" data file could "
                      "not be found (check native test data directory "
                      "path)!" );

  if( !database.doAtomPropertiesExist( Data::C_ATOM ) )
    database.initializeAtomProperties( Data::C_ATOM, 11.907800 );

  Data::AtomProperties& atom_properties =
    database.getAtomProperties( Data::C_ATOM );

  auto atomic_weight =
    11.907800*Utility::PhysicalConstants::neutron_rest_mass_amu_q;

  std::shared_ptr<const Data::PhotoatomicDataProperties>
    photoatomic_properties( new Data::NativeEPRPhotoatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         0,
                                                         Data::C_ATOM ) );

  atom_properties.setPhotoatomicDataProperties( photoatomic_properties );

  std::shared_ptr<const Data::ElectroatomicDataProperties>
    electroatomic_properties( new Data::NativeEPRElectroatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         0,
                                                         Data::C_ATOM ) );

  atom_properties.setElectroatomicDataProperties( electroatomic_properties );
}

// Add the "test_aepr_6_native.xml" properties
void addCNativeAEPRFile( const boost::filesystem::path& native_test_data_dir,
                         Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path native_test_data_file = native_test_data_dir;
  native_test_data_file /= "test_aepr_6_native.xml";

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( native_test_data_file ),
                      std::runtime_error,
                      "The \"test_aepr_6_native.xml\" data file could "
                      "not be found (check native test data directory "
                      "path)!" );

  if( !database.doAtomPropertiesExist( Data::C_ATOM ) )
    database.initializeAtomProperties( Data::C_ATOM, 11.907800 );

  Data::AtomProperties& atom_properties =
    database.getAtomProperties( Data::C_ATOM );

  auto atomic_weight =
    11.907800*Utility::PhysicalConstants::neutron_rest_mass_amu_q;

  std::shared_ptr<const Data::AdjointPhotoatomicDataProperties>
    photoatomic_properties( new Data::NativeEPRAdjointPhotoatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         0,
                                                         Data::C_ATOM ) );

  atom_properties.setAdjointPhotoatomicDataProperties( photoatomic_properties );

  std::shared_ptr<const Data::AdjointElectroatomicDataProperties>
    electroatomic_properties( new Data::NativeEPRAdjointElectroatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         0,
                                                         Data::C_ATOM ) );

  atom_properties.setAdjointElectroatomicDataProperties( electroatomic_properties );
}

// Add the "test_epr_13_native.xml" properties
void addAlNativeEPRFile( const boost::filesystem::path& native_test_data_dir,
                         Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path native_test_data_file = native_test_data_dir;
  native_test_data_file /= "test_epr_13_native.xml";

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( native_test_data_file ),
                      std::runtime_error,
                      "The \"test_epr_13_native.xml\" data file could "
                      "not be found (check native test data directory "
                      "path)!" );

  Data::AtomProperties::AtomicWeight atomic_weight = 2.6982e+01*amu;

  if( !database.doAtomPropertiesExist( Data::Al_ATOM ) )
    database.initializeAtomProperties( Data::Al_ATOM, atomic_weight );

  Data::AtomProperties& atom_properties =
    database.getAtomProperties( Data::Al_ATOM );

  std::shared_ptr<const Data::PhotoatomicDataProperties>
    photoatomic_properties( new Data::NativeEPRPhotoatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         0,
                                                         Data::Al_ATOM ) );

  atom_properties.setPhotoatomicDataProperties( photoatomic_properties );

  std::shared_ptr<const Data::ElectroatomicDataProperties>
    electroatomic_properties( new Data::NativeEPRElectroatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         0,
                                                         Data::Al_ATOM ) );

  atom_properties.setElectroatomicDataProperties( electroatomic_properties );
}

// Add the "test_aepr_13_native.xml" properties
void addAlNativeAEPRFile( const boost::filesystem::path& native_test_data_dir,
                          Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path native_test_data_file = native_test_data_dir;
  native_test_data_file /= "test_aepr_13_native.xml";

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( native_test_data_file ),
                      std::runtime_error,
                      "The \"test_aepr_13_native.xml\" data file could "
                      "not be found (check native test data directory "
                      "path)!" );

  Data::AtomProperties::AtomicWeight atomic_weight = 2.6982e+01*amu;

  if( !database.doAtomPropertiesExist( Data::Al_ATOM ) )
    database.initializeAtomProperties( Data::Al_ATOM, atomic_weight );

  Data::AtomProperties& atom_properties =
    database.getAtomProperties( Data::Al_ATOM );

  std::shared_ptr<const Data::AdjointPhotoatomicDataProperties>
    photoatomic_properties( new Data::NativeEPRAdjointPhotoatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         0,
                                                         Data::Al_ATOM ) );

  atom_properties.setAdjointPhotoatomicDataProperties( photoatomic_properties );

  std::shared_ptr<const Data::AdjointElectroatomicDataProperties>
    electroatomic_properties( new Data::NativeEPRAdjointElectroatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         0,
                                                         Data::Al_ATOM ) );

  atom_properties.setAdjointElectroatomicDataProperties( electroatomic_properties );
}

// Add the "test_epr_14_native.xml" properties
void addSiNativeEPRFile( const boost::filesystem::path& native_test_data_dir,
                         Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path native_test_data_file = native_test_data_dir;
  native_test_data_file /= "test_epr_14_native.xml";

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( native_test_data_file ),
                      std::runtime_error,
                      "The \"test_epr_14_native.xml\" data file could "
                      "not be found (check native test data directory "
                      "path)!" );

  Data::AtomProperties::AtomicWeight atomic_weight = 2.8085e+01*amu;

  if( !database.doAtomPropertiesExist( Data::Si_ATOM ) )
    database.initializeAtomProperties( Data::Si_ATOM, atomic_weight );

  Data::AtomProperties& atom_properties =
    database.getAtomProperties( Data::Si_ATOM );

  std::shared_ptr<const Data::PhotoatomicDataProperties>
    photoatomic_properties( new Data::NativeEPRPhotoatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         0,
                                                         Data::Si_ATOM ) );

  atom_properties.setPhotoatomicDataProperties( photoatomic_properties );

  std::shared_ptr<const Data::ElectroatomicDataProperties>
    electroatomic_properties( new Data::NativeEPRElectroatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         0,
                                                         Data::Si_ATOM ) );

  atom_properties.setElectroatomicDataProperties( electroatomic_properties );
}

// Add the "test_aepr_14_native.xml" properties
void addSiNativeAEPRFile( const boost::filesystem::path& native_test_data_dir,
                          Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path native_test_data_file = native_test_data_dir;
  native_test_data_file /= "test_aepr_14_native.xml";

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( native_test_data_file ),
                      std::runtime_error,
                      "The \"test_aepr_14_native.xml\" data file could "
                      "not be found (check native test data directory "
                      "path)!" );

  Data::AtomProperties::AtomicWeight atomic_weight = 2.8085e+01*amu;

  if( !database.doAtomPropertiesExist( Data::Si_ATOM ) )
    database.initializeAtomProperties( Data::Si_ATOM, atomic_weight );

  Data::AtomProperties& atom_properties =
    database.getAtomProperties( Data::Si_ATOM );

  std::shared_ptr<const Data::AdjointPhotoatomicDataProperties>
    photoatomic_properties( new Data::NativeEPRAdjointPhotoatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         0,
                                                         Data::Si_ATOM ) );

  atom_properties.setAdjointPhotoatomicDataProperties( photoatomic_properties );

  std::shared_ptr<const Data::AdjointElectroatomicDataProperties>
    electroatomic_properties( new Data::NativeEPRAdjointElectroatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         0,
                                                         Data::Si_ATOM ) );

  atom_properties.setAdjointElectroatomicDataProperties( electroatomic_properties );
}

// Add the "test_epr_82_native.xml" properties
void addPbNativeEPRFile( const boost::filesystem::path& native_test_data_dir,
                         Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path native_test_data_file = native_test_data_dir;
  native_test_data_file /= "test_epr_82_native.xml";

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( native_test_data_file ),
                      std::runtime_error,
                      "The \"test_epr_82_native.xml\" data file could "
                      "not be found (check native test data directory "
                      "path)!" );

  Data::AtomProperties::AtomicWeight atomic_weight = 2.072e+02*amu;

  if( !database.doAtomPropertiesExist( Data::Pb_ATOM ) )
    database.initializeAtomProperties( Data::Pb_ATOM, atomic_weight );

  Data::AtomProperties& atom_properties =
    database.getAtomProperties( Data::Pb_ATOM );

  std::shared_ptr<const Data::PhotoatomicDataProperties>
    photoatomic_properties( new Data::NativeEPRPhotoatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         0,
                                                         Data::Pb_ATOM ) );

  atom_properties.setPhotoatomicDataProperties( photoatomic_properties );

  std::shared_ptr<const Data::ElectroatomicDataProperties>
    electroatomic_properties( new Data::NativeEPRElectroatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         0,
                                                         Data::Pb_ATOM ) );

  atom_properties.setElectroatomicDataProperties( electroatomic_properties );
}

} // end Details namespace

//---------------------------------------------------------------------------//
// end database_generator.cpp
//---------------------------------------------------------------------------//
