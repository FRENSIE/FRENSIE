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

// FRENSIE Includes
#include "Data_ACEPhotoatomicDataProperties.hpp"
#include "Data_ACEElectroatomicDataProperties.hpp"
#include "Data_ACENuclearDataProperties.hpp"
#include "Data_ACEThermalNuclearDataProperties.hpp"
#include "Data_ACEPhotonuclearDataProperties.hpp"
#include "Data_NativeEPRPhotoatomicDataProperties.hpp"
#include "Data_NativeEPRAdjointPhotoatomicDataProperties.hpp"
#include "Data_NativeEPRElectroatomicDataProperties.hpp"
#include "Data_NativeEPRAdjointElectroatomicDataProperties.hpp"
#include "Data_ENDLPhotoatomicDataProperties.hpp"
#include "Data_ENDLElectroatomicDataProperties.hpp"
#include "Data_ScatteringCenterPropertiesDatabase.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"

using Utility::Units::MeV;
using Utility::Units::amu;

namespace Details{

//! Add the "test_au_epr14_ace_file.txt" properties
void addTestAuEPR14ACEFile(
                          const boost::filesystem::path& ace_test_data_dir,
                          Data::ScatteringCenterPropertiesDatabase& database );

//! Add the "test_b_electron_ace_file.txt" properties
void addBElectronACEFile( const boost::filesystem::path& ace_test_data_dir,
                          Data::ScatteringCenterPropertiesDatabase& database );

//! Add the "test_b_epr_ace_file.txt" properties
void addBEPRACEFile( const boost::filesystem::path& ace_test_data_dir,
                     Data::ScatteringCenterPropertiesDatabase& database );

//! Add the "test_c12_photonuclear_ace_file.txt" properties
void addC12PhotonuclearACEFile(
                          const boost::filesystem::path& ace_test_data_dir,
                          Data::ScatteringCenterPropertiesDatabase& database );
  
//! Add the "test_c_epr_ace_file.txt" properties
void addCEPRACEFile( const boost::filesystem::path& ace_test_data_dir,
                     Data::ScatteringCenterPropertiesDatabase& database );

//! Add the "test_grph_sab_ace_file.txt" properties
void addGrphSabACEFile( const boost::filesystem::path& ace_test_data_dir,
                        Data::ScatteringCenterPropertiesDatabase& database );

//! Add the "test_h1_ace_file.txt" properties
void addH1ACEFile( const boost::filesystem::path& ace_test_data_dir,
                   Data::ScatteringCenterPropertiesDatabase& database );

//! Add the "test_h2o_sab_ace_file.txt" properties
void addH2OSabACEFile( const boost::filesystem::path& ace_test_data_dir,
                       Data::ScatteringCenterPropertiesDatabase& database );

//! Add the "test_h2_photonuclear_ace_file.txt" properties
void addH2PhotonuclearACEFile(
                          const boost::filesystem::path& ace_test_data_dir,
                          Data::ScatteringCenterPropertiesDatabase& database );

//! Add the "test_h_epr14_ace_file.txt" properties
void addHEPR14ACEFile( const boost::filesystem::path& ace_test_data_dir,
                       Data::ScatteringCenterPropertiesDatabase& database );
  
//! Add the "test_h_epr_ace_file.txt" properties
void addHEPRACEFile( const boost::filesystem::path& ace_test_data_dir,
                     Data::ScatteringCenterPropertiesDatabase& database );

//! Add the "test_poly_sab_ace_file.txt" properties
void addPolySabACEFile( const boost::filesystem::path& ace_test_data_dir,
                        Data::ScatteringCenterPropertiesDatabase& database );

//! Add the "test_o16_ace_file.txt" properties
void addO16ACEFile( const boost::filesystem::path& ace_test_data_dir,
                    Data::ScatteringCenterPropertiesDatabase& database );

//! Add the "test_o_epr_ace_file.txt" properties
void addOEPRACEFile( const boost::filesystem::path& ace_test_data_dir,
                     Data::ScatteringCenterPropertiesDatabase& database );

//! Add the "test_pb208_ace_file.txt" properties
void addPb208ACEFile( const boost::filesystem::path& ace_test_data_dir,
                      Data::ScatteringCenterPropertiesDatabase& database );

//! Add the "test_pb_electron_ace_file.txt" properties
void addPbElectronACEFile(
                          const boost::filesystem::path& ace_test_data_dir,
                          Data::ScatteringCenterPropertiesDatabase& database );

//! Add the "test_pb_epr14_ace_file.txt" properties
void addPbEPR14ACEFile( const boost::filesystem::path& ace_test_data_dir,
                        Data::ScatteringCenterPropertiesDatabase& database );

//! Add the "test_pb_epr_ace_file.txt" properties
void addPbEPRACEFile( const boost::filesystem::path& ace_test_data_dir,
                      Data::ScatteringCenterPropertiesDatabase& database );

//! Add the "test_pb_photoatomic_ace_file.txt" properties
void addPbPhotoatomicACEFile(
                          const boost::filesystem::path& ace_test_data_dir,
                          Data::ScatteringCenterPropertiesDatabase& database );

//! Add the "test_u238_ace_file.txt" properties
void addU238ACEFile( const boost::filesystem::path& ace_test_data_dir,
                     Data::ScatteringCenterPropertiesDatabase& database );

//! Add the "test_u_epr_ace_file.txt" properties
void addUEPRACEFile( const boost::filesystem::path& ace_test_data_dir,
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

//! Add the ACE test files for H
void addHACETestFiles( const boost::filesystem::path& ace_test_data_dir,
                       Data::ScatteringCenterPropertiesDatabase& database )
{
  Details::addH1ACEFile( ace_test_data_dir, database );
  Details::addH2OSabACEFile( ace_test_data_dir, database );
  Details::addH2PhotonuclearACEFile( ace_test_data_dir, database );
  Details::addHEPR14ACEFile( ace_test_data_dir, database );
  Details::addHEPRACEFile( ace_test_data_dir, database );
  Details::addPolySabACEFile( ace_test_data_dir, database );
}

//! Add the ACE test files for B
void addBACETestFiles( const boost::filesystem::path& ace_test_data_dir,
                       Data::ScatteringCenterPropertiesDatabase& database )
{
  Details::addBElectronACEFile( ace_test_data_dir, database );
  Details::addBEPRACEFile( ace_test_data_dir, database );
}

//! Add the ACE test files for C
void addCACETestFiles( const boost::filesystem::path& ace_test_data_dir,
                       Data::ScatteringCenterPropertiesDatabase& database )
{
  Details::addC12PhotonuclearACEFile( ace_test_data_dir, database );
  Details::addCEPRACEFile( ace_test_data_dir, database );
  Details::addGrphSabACEFile( ace_test_data_dir, database );
}

//! Add the ACE test files for O
void addOACETestFiles( const boost::filesystem::path& ace_test_data_dir,
                       Data::ScatteringCenterPropertiesDatabase& database )
{
  Details::addO16ACEFile( ace_test_data_dir, database );
  Details::addOEPRACEFile( ace_test_data_dir, database );
}

//! Add the test files for Au
void addAuACETestFiles( const boost::filesystem::path& ace_test_data_dir,
                        Data::ScatteringCenterPropertiesDatabase& database )
{
  Details::addTestAuEPR14ACEFile( ace_test_data_dir, database );
}

//! Add the ACE test files for Pb
void addPbACETestFiles( const boost::filesystem::path& ace_test_data_dir,
                        Data::ScatteringCenterPropertiesDatabase& database )
{
  Details::addPb208ACEFile( ace_test_data_dir, database );
  Details::addPbElectronACEFile( ace_test_data_dir, database );
  Details::addPbEPR14ACEFile( ace_test_data_dir, database );
  Details::addPbEPRACEFile( ace_test_data_dir, database );
  Details::addPbPhotoatomicACEFile( ace_test_data_dir, database );
}

//! Add the ACE test files for U
void addUACETestFiles( const boost::filesystem::path& ace_test_data_dir,
                       Data::ScatteringCenterPropertiesDatabase& database )
{
  Details::addU238ACEFile( ace_test_data_dir, database );
  Details::addUEPRACEFile( ace_test_data_dir, database );
}

//! Add the ENDL test files for H
void addHENDLTestFiles( const boost::filesystem::path& endl_test_data_dir,
                        Data::ScatteringCenterPropertiesDatabase& database );

//! Add the ENDL test files for C
void addCENDLTestFiles( const boost::filesystem::path& endl_test_data_dir,
                        Data::ScatteringCenterPropertiesDatabase& database );

//! Add the ENDL test files for Pb
void addPbENDLTestFiles( const boost::filesystem::path& endl_test_data_dir,
                         Data::ScatteringCenterPropertiesDatabase& database );

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
void addAlNativeTestFiles( const boost::filesystem::path& native_test_data_dir,
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
      ("ace_dir,a",
       boost::program_options::value<std::string>(),
       "specify the relative location of the ace test data directory")
      ("native_dir,n",
       boost::program_options::value<std::string>(),
       "specify the relative location of the native test data directory")
      ("endl_dir,e",
       boost::program_options::value<std::string>(),
       "specify the relative location of the endl test data directory")
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
    comman_line_arguments["database_name"].as<std::string>();

  TEST_FOR_EXCEPTION( database_output_file_name.find( " " ) <
                      database_output_file_name.size(),
                      std::runtime_error,
                      "The database output file name cannot contain any "
                      "white space!" );

  // Set the ace test data directory path
  TEST_FOR_EXCEPTION( !command_line_arguments.count( "ace_dir" ),
                      std::runtime_error,
                      "The ace test data directory must be specified!" );

  boost::filesystem::path ace_test_data_dir =
    command_line_arguments["ace_dir"].as<std::string>();

  TEST_FOR_EXCEPTION( !boost::filesystem::is_directory( ace_test_data_dir ),
                      std::runtime_error,
                      "The ace test data directory is not valid!" );

  ace_test_data_dir = boost::filesystem::relative( ace_test_data_dir );
                                                   

  // Set the endl test data directory path
  TEST_FOR_EXCEPTION( !command_line_arguments.count( "endl_dir" ),
                      std::runtime_error,
                      "The endl test data directory must be specified!" );

  boost::filesystem::path endl_test_data_dir =
    command_line_arguments["endl_dir"].as<std::string>();

  TEST_FOR_EXCEPTION( !boost::filesystem::is_directory( endl_test_data_dir ),
                      std::runtime_error,
                      "The endl test data directory is not valid!" );

  endl_test_data_dir = boost::filesystem::relative( endl_test_data_dir );

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
  addHACETestFiles( ace_test_data_dir, database );
  addBACETestFiles( ace_test_data_dir, database );
  addCACETestFiles( ace_test_data_dir, database );
  addOACETestFiles( ace_test_data_dir, database );
  addAuACETestFiles( ace_test_data_dir, database );
  addPbACETestFiles( ace_test_data_dir, database );
  addUACETestFiles( ace_test_data_dir, database );

  // Add the endl data properties
  addHENDLTestFiles( endl_test_data_dir, database );
  addCENDLTestFiles( endl_test_data_dir, database );
  addPbENDLTestFiles( endl_test_data_dir, database );

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

// Add the "test_au_epr14_ace_file.txt" properties
void addTestAuEPR14ACEFile( const boost::filesystem::path& ace_test_data_dir,
                            Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path ace_test_data_file = ace_test_data_dir;
  ace_test_data_file /= "test_au_epr14_ace_file.txt";
  
  TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                      std::runtime_error,
                      "The \"test_au_epr14_ace_file.txt\" data file could not "
                      "be found (check ace test data directory path)!" );

  if( !database.doPropertiesExist( Data::Au_ATOM ) )
    database.initializeNuclide( Data::Au_ATOM, 195.275000 );
    
  Data::AtomProperties& atom_properties =
    database.getAtomProperties( Data::Au_ATOM );

  auto atomic_weight =
    195.275000*Utility::PhysicalConstants::neutron_rest_mass_amu_q;

  std::shared_ptr<const Data::PhotoatomicDataProperties>
    photoatomic_properties( new Data::ACEPhotoatomicDataProperties(
                                                            atomic_weight,
                                                            ace_test_data_file,
                                                            1,
                                                            "79000.14p" ) );
    
  atom_properties.setPhotoatomicDataProperties( photoatomic_properties );

  std::shared_ptr<const Data::ElectroatomicDataProperties>
    electroatomic_properties( new Data::ACEElectroatomicDataProperties(
                                                            atomic_weight,
                                                            ace_test_data_file,
                                                            1,
                                                            "79000.14p" ) );

  atom_properties.setElectroatomicDataProperties( electroatomic_properties );
}

// Add the "test_b_electron_ace_file.txt" properties
void addBElectronACEFile( const boost::filesystem::path& ace_test_data_dir,
                          Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path ace_test_data_file = ace_test_data_dir;
  ace_test_data_dir /= "test_b_electron_ace_file.txt";

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                      std::runtime_error,
                      "The \"test_b_electron_ace_file.txt\" data file could "
                      "not be found (check ace test data directory path)!" );

  if( !database.doPropertiesExist( Data::B_ATOM ) )
    database.initializeNuclide( Data::B_ATOM, 10.717168 );

  Data::AtomProperties& atom_properties =
    database.getAtomProperties( Data::B_ATOM );

  auto atomic_weight =
    10.717168*Utility::PhysicalConstants::neutron_rest_mass_amu_q;

  std::shared_ptr<const Data::ElectroatomicDataProperties>
    electroatomic_properties( new Data::ACEElectroatomicDataProperties(
                                                            atomic_weight,
                                                            ace_test_data_file,
                                                            1,
                                                            "5000.03e" ) );

  atom_properties.setElectroatomicDataProperties( electroatomic_properties );
}

// Add the "test_b_epr_ace_file.txt" properties
void addBEPRACEFile( const boost::filesystem::path& ace_test_data_dir,
                     Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path ace_test_data_file = ace_test_data_dir;
  ace_test_data_dir /= "test_b_epr_ace_file.txt";

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                      std::runtime_error,
                      "The \"test_b_epr_ace_file.txt\" data file could "
                      "not be found (check ace test data directory path)!" );

  if( !database.doPropertiesExist( Data::B_ATOM ) )
    database.initializeNuclide( Data::B_ATOM, 10.717100 );

  Data::AtomProperties& atom_properties =
    database.getAtomProperties( Data::B_ATOM );

  auto atomic_weight =
    10.717100*Utility::PhysicalConstants::neutron_rest_mass_amu_q;

  std::shared_ptr<const Data::PhotoatomicDataProperties>
    photoatomic_properties( new Data::ACEPhotoatomicDataProperties(
                                                            atomic_weight,
                                                            ace_test_data_file,
                                                            1,
                                                            "5000.12p" ) );

  atom_properties.setPhotoatomicDataProperties( photoatomic_properties );

  std::shared_ptr<const Data::ElectroatomicDataProperties>
    electroatomic_properties( new Data::ACEElectroatomicDataProperties(
                                                            atomic_weight,
                                                            ace_test_data_file,
                                                            1,
                                                            "5000.12p" ) );

  atom_properties.setElectroatomicDataProperties( electroatomic_properties );
}

// Add the "test_c12_photonuclear_ace_file.txt" properties
void addC12PhotonuclearACEFile(
                           const boost::filesystem::path& ace_test_data_dir,
                           Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path ace_test_data_file = ace_test_data_dir;
  ace_test_data_dir /= "test_c12_photonuclear_ace_file.txt";

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                      std::runtime_error,
                      "The \"test_c12_photonuclear_ace_file.txt\" data file "
                      "could not be found (check ace test data directory "
                      "path)!" );

  if( !database.doPropertiesExist( 6012 ) )
    database.initializeNuclide( 6012, 11.896910 );

  Data::NuclideProperties& nuclide_properties =
    database.getNuclideProperties( 6012 );

  auto atomic_weight =
    11.896910*Utility::PhysicalConstants::neutron_rest_mass_amu_q;

  std::shared_ptr<const Data::PhotonuclearDataProperties>
    photonuclear_properties( new Data::ACEPhotonuclearDataProperties(
                                                            atomic_weight,
                                                            ace_test_data_file,
                                                            1,
                                                            "6012.24u" ) );

  nuclide_properties.setPhotonuclearDataProperties( photonuclear_properties );
}

// Add the "test_c_epr_ace_file.txt" properties
void addCEPRACEFile( const boost::filesystem::path& ace_test_data_dir,
                     Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path ace_test_data_file = ace_test_data_dir;
  ace_test_data_dir /= "test_c_epr_ace_file.txt";

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                      std::runtime_error,
                      "The \"test_c_epr_ace_file.txt\" data file could not be "
                      "found (check ace test data directory path)!" );

  if( !database.doPropertiesExist( Data::C_ATOM ) )
    database.initializeNuclide( Data::C_ATOM, 11.907800 );

  Data::AtomProperties& atom_properties =
    database.getAtomProperties( Data::C_ATOM );

  auto atomic_weight =
    11.907800*Utility::PhysicalConstants::neutron_rest_mass_amu_q;

  std::shared_ptr<const Data::PhotoatomicDataProperties>
    photoatomic_properties( new Data::ACEPhotoatomicDataProperties(
                                                            atomic_weight,
                                                            ace_test_data_file,
                                                            1,
                                                            "6000.12p" ) );

  atom_properties.setPhotoatomicDataProperties( photoatomic_properties );

  std::shared_ptr<const Data::ElectroatomicDataProperties>
    electroatomic_properties( new Data::ACEElectroatomicDataProperties(
                                                            atomic_weight,
                                                            ace_test_data_file,
                                                            1,
                                                            "6000.12p" ) );

  atom_propertis.setElectroatomicDataProperties( electroatomic_properties );
}

// Add the "test_grph_sab_ace_file.txt" properties
void addGrphSabACEFile( const boost::filesystem::path& ace_test_data_dir,
                        Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path ace_test_data_file = ace_test_data_dir;
  ace_test_data_dir /= "test_grph_sab_ace_file.txt"

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                      std::runtime_error,
                      "The \"test_grph_sab_ace_file.txt\" data file could not "
                      "be found (check ace test data directory path)!" );

  std::shared_ptr<const Data::ThermalNuclearDataProperties>
    thermal_nuclear_properties( new Data::ACEThermalNuclearDataProperties(
                                                            {6000, 6012, 6013},
                                                            2.53010E-08*MeV,
                                                            ace_test_data_file,
                                                            1,
                                                            "grph.10t" ) );

  if( !database.doPropertiesExist( Data::C_ATOM ) )
    database.initializeNuclide( Data::C_ATOM, 11.907800 );

  database.getNuclide( Data::C_ATOM ).setThermalNuclearDataProperties( thermal_nuclear_data_properties );

  if( !database.doPropertiesExist( 6012 ) )
    database.initializeNuclide( 6012, 11.89691424 );

  database.getNuclide( 6012 ).setThermalNuclearDataProperties( thermal_nuclear_data_properties );

  if( !database.doPropertiesExist( 6013 ) )
    database.initializeNuclide( 6013, 12.89164978 );

  database.getNuclide( 6013 ).setThermalNuclearDataProperties( thermal_nuclear_data_properties );
}

// Add the "test_h1_ace_file.txt" properties
void addH1ACEFile( const boost::filesystem::path& ace_test_data_dir,
                   Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path ace_test_data_file = ace_test_data_dir;
  ace_test_data_dir /= "test_h1_ace_file.txt"

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                      std::runtime_error,
                      "The \"test_h1_ace_file.txt\" data file could not be "
                      "found (check ace test data directory path)!" );

  if( !database.doPropertiesExist( 1001 ) )
    database.initializeNuclide( 1001, 0.999167 );

  Data::NuclideProperties& nuclide_properties =
    database.getNuclideProperties( 1001 );

  std::shared_ptr<const Data::NuclearDataProperties>
    nuclear_properties( new Data::ACENuclearDataProperties( 0.999167,
                                                            2.53010E-08*MeV,
                                                            ace_test_data_file,
                                                            1,
                                                            "1001.70c" ) );
  
  nuclide_properties.setNuclearDataProperties( nuclear_properties );
}

// Add the "test_h2o_sab_ace_file.txt" properties
void addH2OSabACEFile( const boost::filesystem::path& ace_test_data_dir,
                       Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path ace_test_data_file = ace_test_data_dir;
  ace_test_data_dir /= "test_h2o_sab_ace_file.txt"

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                      std::runtime_error,
                      "The \"test_h2o_sab_ace_file.txt\" data file could not "
                      "be found (check ace test data directory path)!" );

  std::shared_ptr<const Data::ThermalNuclearDataProperties>
    thermal_nuclear_properties( new Data::ACEThermalNuclearDataProperties(
                                                            {1001},
                                                            2.53010E-08*MeV,
                                                            ace_test_data_file,
                                                            1,
                                                            "lwtr.10t" ) );

  if( !database.doPropertiesExist( 1001 ) )
    database.initializeNuclide( 1001, 0.999167 );

  database.getNuclideProperties( 1001 ).setThermalNuclearDataProperties( thermal_nuclear_properties );
}

// Add the "test_h2_photonuclear_ace_file.txt" properties
void addH2PhotonuclearACEFile(
                           const boost::filesystem::path& ace_test_data_dir,
                           Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path ace_test_data_file = ace_test_data_dir;
  ace_test_data_dir /= "test_h2_photonuclear_ace_file.txt";

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                      std::runtime_error,
                      "The \"test_h2_photonuclear_ace_file.txt\" data file "
                      "could not be found (check ace test data directory "
                      "path)!" );

  if( !database.doPropertiesExist( 1002 ) )
    database.initializeNuclide( 1002, 1.996300 );

  Data::NuclideProperties& nuclide_properties =
    database.getNuclideProperties( 1002 );

  auto atomic_weight =
    1.996300*Utility::PhysicalConstants::neutron_rest_mass_amu_q;

  std::shared_ptr<const Data::PhotonuclearDataProperties>
    photonuclear_properties( new Data::ACEPhotonuclearDataProperties(
                                                            atomic_weight,
                                                            ace_test_data_file,
                                                            1,
                                                            "1002.24u" ) );
  
  nuclide_properties.setPhotonuclearDataProperties( photonuclear_properties );
}

// Add the "test_h_epr14_ace_file.txt" properties
void addHEPR14ACEFile( const boost::filesystem::path& ace_test_data_dir,
                       Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path ace_test_data_file = ace_test_data_dir;
  ace_test_data_file /= "test_h_epr14_ace_file.txt";
  
  TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                      std::runtime_error,
                      "The \"test_h_epr14_ace_file.txt\" data file could not "
                      "be found (check ace test data directory path)!" );

  if( !database.doPropertiesExist( Data::H_ATOM ) )
    database.initializeNuclide( Data::H_ATOM, 0.999242 );

  Data::AtomProperties& atom_properties =
    database.getAtomProperties( Data::H_ATOM );

  auto atomic_weight =
    0.999242*Utility::PhysicalConstants::neutron_rest_mass_amu_q;

  std::shared_ptr<const Data::PhotoatomicDataProperties>
    photoatomic_properties( new Data::ACEPhotoatomicDataProperties(
                                                            atomic_weight,
                                                            ace_test_data_file,
                                                            1,
                                                            "1000.14p" ) );
    
  atom_properties.setPhotoatomicDataProperties( photoatomic_properties );

  std::shared_ptr<const Data::ElectroatomicDataProperties>
    electroatomic_properties( new Data::ACEElectroatomicDataProperties(
                                                            atomic_weight,
                                                            ace_test_data_file,
                                                            1,
                                                            "1000.14p" ) );

  atom_properties.setElectroatomicDataProperties( electroatomic_properties );
}
  
// Add the "test_h_epr_ace_file.txt" properties
void addHEPRACEFile( const boost::filesystem::path& ace_test_data_dir,
                     Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path ace_test_data_file = ace_test_data_dir;
  ace_test_data_file /= "test_h_epr_ace_file.txt";
  
  TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                      std::runtime_error,
                      "The \"test_h_epr_ace_file.txt\" data file could not "
                      "be found (check ace test data directory path)!" );

  if( !database.doPropertiesExist( Data::H_ATOM ) )
    database.initializeNuclide( Data::H_ATOM, 0.999242 );

  Data::AtomProperties& atom_properties =
    database.getAtomProperties( Data::H_ATOM );

  auto atomic_weight =
    0.999242*Utility::PhysicalConstants::neutron_rest_mass_amu_q;

  std::shared_ptr<const Data::PhotoatomicDataProperties>
    photoatomic_properties( new Data::ACEPhotoatomicDataProperties(
                                                            atomic_weight,
                                                            ace_test_data_file,
                                                            1,
                                                            "1000.12p" ) );
    
  atom_properties.setPhotoatomicDataProperties( photoatomic_properties );

  std::shared_ptr<const Data::ElectroatomicDataProperties>
    electroatomic_properties( new Data::ACEElectroatomicDataProperties(
                                                            atomic_weight,
                                                            ace_test_data_file,
                                                            1,
                                                            "1000.12p" ) );

  atom_properties.setElectroatomicDataProperties( electroatomic_properties );
}

// Add the "test_poly_sab_ace_file.txt" properties
void addPolySabACEFile( const boost::filesystem::path& ace_test_data_dir,
                        Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path ace_test_data_file = ace_test_data_dir;
  ace_test_data_dir /= "test_poly_sab_ace_file.txt"

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                      std::runtime_error,
                      "The \"test_poly_sab_ace_file.txt\" data file could not "
                      "be found (check ace test data directory path)!" );

  std::shared_ptr<const Data::ThermalNuclearDataProperties>
    thermal_nuclear_properties( new Data::ACEThermalNuclearDataProperties(
                                                            {1001},
                                                            2.53010E-08*MeV,
                                                            ace_test_data_file,
                                                            1,
                                                            "poly.10t" ) );
  if( !database.doPropertiesExist( 1001 ) )
    database.initializeNuclide( 1001, 0.999167 );

  database.getNuclideProperties( 1001 ).setThermalNuclearDataProperties( thermal_nuclear_properties );
}

// Add the "test_o16_ace_file.txt" properties
void addO16ACEFile( const boost::filesystem::path& ace_test_data_dir,
                    Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path ace_test_data_file = ace_test_data_dir;
  ace_test_data_dir /= "test_o16_ace_file.txt"

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                      std::runtime_error,
                      "The \"test_o16_ace_file.txt\" data file could not be "
                      "found (check ace test data directory path)!" );

  if( !database.doPropertiesExist( 8016 ) )
    database.initializeNuclide( 8016, 15.857510 );

  Data::NuclideProperties& nuclide_properties =
    database.getNuclideProperties( 8016 );

  std::shared_ptr<const Data::NuclearDataProperties>
    nuclear_properties( new Data::ACENuclearDataProperties( 15.857510,
                                                            2.53010E-08*MeV,
                                                            ace_test_data_file,
                                                            1,
                                                            "8016.70c" ) );
  
  nuclide_properties.setNuclearDataProperties( nuclear_properties );
}

// Add the "test_o_epr_ace_file.txt" properties
void addOEPRACEFile( const boost::filesystem::path& ace_test_data_dir,
                     Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path ace_test_data_file = ace_test_data_dir;
  ace_test_data_dir /= "test_o_epr_ace_file.txt";

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                      std::runtime_error,
                      "The \"test_o_epr_ace_file.txt\" data file could not be "
                      "found (check ace test data directory path)!" );

  if( !database.doPropertiesExist( Data::O_ATOM ) )
    database.initializeNuclide( Data::O_ATOM, 15.862000 );

  Data::AtomProperties& atom_properties =
    database.getAtomProperties( Data::O_ATOM );

  auto atomic_weight =
    15.862000*Utility::PhysicalConstants::neutron_rest_mass_amu_q;

  std::shared_ptr<const Data::PhotoatomicDataProperties>
    photoatomic_properties( new Data::ACEPhotoatomicDataProperties(
                                                            atomic_weight,
                                                            ace_test_data_file,
                                                            1,
                                                            "8000.12p" ) );

  atom_properties.setPhotoatomicDataProperties( photoatomic_properties );

  std::shared_ptr<const Data::ElectroatomicDataProperties>
    electroatomic_properties( new Data::ACEElectroatomicDataProperties(
                                                            atomic_weight,
                                                            ace_test_data_file,
                                                            1,
                                                            "8000.12p" ) );

  atom_properties.setElectroatomicDataProperties( electroatomic_properties );
}

// Add the "test_pb208_ace_file.txt" properties
void addPb208ACEFile( const boost::filesystem::path& ace_test_data_dir,
                      Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path ace_test_data_file = ace_test_data_dir;
  ace_test_data_dir /= "test_pb208_ace_file.txt"

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                      std::runtime_error,
                      "The \"test_pb208_ace_file.txt\" data file could not be "
                      "found (check ace test data directory path)!" );

  if( !database.doPropertiesExist( 82208 ) )
    database.initializeNuclide( 82208, 206.190000 );

  Data::NuclideProperties& nuclide_properties =
    database.getNuclideProperties( 82208 );

  std::shared_ptr<const Data::NuclearDataProperties>
    nuclear_properties( new Data::ACENuclearDataProperties( 206.190000,
                                                            2.53010E-08*MeV,
                                                            ace_test_data_file,
                                                            1,
                                                            "82208.70c" ) );
  
  nuclide_properties.setNuclearDataProperties( nuclear_properties );
}

// Add the "test_pb_electron_ace_file.txt" properties
void addPbElectronACEFile(
                          const boost::filesystem::path& ace_test_data_dir,
                          Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path ace_test_data_file = ace_test_data_dir;
  ace_test_data_dir /= "test_pb_electron_ace_file.txt";

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                      std::runtime_error,
                      "The \"test_pb_electron_ace_file.txt\" data file could "
                      "not be found (check ace test data directory path)!" );

  if( !database.doPropertiesExist( Data::Pb_ATOM ) )
    database.initializeNuclide( Data::Pb_ATOM, 205.436151 );

  Data::AtomProperties& atom_properties =
    database.getAtomProperties( Data::Pb_ATOM );

  auto atomic_weight =
    205.436151*Utility::PhysicalConstants::neutron_rest_mass_amu_q;

  std::shared_ptr<const Data::ElectroatomicDataProperties>
    electroatomic_properties( new Data::ACEElectroatomicDataProperties(
                                                            atomic_weight,
                                                            ace_test_data_file,
                                                            1,
                                                            "82000.03e" ) );

  atom_properties.setElectroatomicDataProperties( electroatomic_properties );
}

// Add the "test_pb_epr14_ace_file.txt" properties
void addPbEPR14ACEFile( const boost::filesystem::path& ace_test_data_dir,
                        Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path ace_test_data_file = ace_test_data_dir;
  ace_test_data_dir /= "test_pb_epr14_ace_file.txt";

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                      std::runtime_error,
                      "The \"test_pb_epr14_ace_file.txt\" data file could "
                      "not be found (check ace test data directory path)!" );

  if( !database.doPropertiesExist( Data::Pb_ATOM ) )
    database.initializeNuclide( Data::Pb_ATOM, 205.420000 );

  Data::AtomProperties& atom_properties =
    database.getAtomProperties( Data::Pb_ATOM );

  auto atomic_weight =
    205.420000*Utility::PhysicalConstants::neutron_rest_mass_amu_q;

  std::shared_ptr<const Data::PhotoatomicDataProperties>
    photoatomic_properties( new Data::ACEPhotoatomicDataProperties(
                                                            atomic_weight,
                                                            ace_test_data_file,
                                                            1,
                                                            "82000.14p" ) );

  atom_properties.setPhotoatomicDataProperties( photoatomic_properties );

  std::shared_ptr<const Data::ElectroatomicDataProperties>
    electroatomic_properties( new Data::ACEElectroatomicDataProperties(
                                                            atomic_weight,
                                                            ace_test_data_file,
                                                            1,
                                                            "82000.14p" ) );

  atom_properties.setElectroatomicDataProperties( electroatomic_properties );
}

// Add the "test_pb_epr_ace_file.txt" properties
void addPbEPRACEFile( const boost::filesystem::path& ace_test_data_dir,
                      Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path ace_test_data_file = ace_test_data_dir;
  ace_test_data_dir /= "test_pb_epr_ace_file.txt";

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                      std::runtime_error,
                      "The \"test_pb_epr_ace_file.txt\" data file could "
                      "not be found (check ace test data directory path)!" );

  if( !database.doPropertiesExist( Data::Pb_ATOM ) )
    database.initializeNuclide( Data::Pb_ATOM, 205.420000 );

  Data::AtomProperties& atom_properties =
    database.getAtomProperties( Data::Pb_ATOM );

  auto atomic_weight =
    205.420000*Utility::PhysicalConstants::neutron_rest_mass_amu_q;

  std::shared_ptr<const Data::PhotoatomicDataProperties>
    photoatomic_properties( new Data::ACEPhotoatomicDataProperties(
                                                            atomic_weight,
                                                            ace_test_data_file,
                                                            1,
                                                            "82000.12p" ) );

  atom_properties.setPhotoatomicDataProperties( photoatomic_properties );

  std::shared_ptr<const Data::ElectroatomicDataProperties>
    electroatomic_properties( new Data::ACEElectroatomicDataProperties(
                                                            atomic_weight,
                                                            ace_test_data_file,
                                                            1,
                                                            "82000.12p" ) );

  atom_properties.setElectroatomicDataProperties( electroatomic_properties );
}

// Add the "test_pb_photoatomic_ace_file.txt" properties
void addPbPhotoatomicACEFile(
                          const boost::filesystem::path& ace_test_data_dir,
                          Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path ace_test_data_file = ace_test_data_dir;
  ace_test_data_dir /= "test_pb_photoatomic_ace_file.txt";

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                      std::runtime_error,
                      "The \"test_pb_photoatomic_ace_file.txt\" data file "
                      "could not be found (check ace test data directory "
                      "path)!" );

  if( !database.doPropertiesExist( Data::Pb_ATOM ) )
    database.initializeNuclide( Data::Pb_ATOM, 205.420000 );

  Data::AtomProperties& atom_properties =
    database.getAtomProperties( Data::Pb_ATOM );

  auto atomic_weight =
    205.420000*Utility::PhysicalConstants::neutron_rest_mass_amu_q;

  std::shared_ptr<const Data::PhotoatomicDataProperties>
    photoatomic_properties( new Data::ACEPhotoatomicDataProperties(
                                                            atomic_weight,
                                                            ace_test_data_file,
                                                            1,
                                                            "82000.04p" ) );

  atom_properties.setPhotoatomicDataProperties( photoatomic_properties );
}

// Add the "test_u238_ace_file.txt" properties
void addU238ACEFile( const boost::filesystem::path& ace_test_data_dir,
                     Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path ace_test_data_file = ace_test_data_dir;
  ace_test_data_dir /= "test_u238_ace_file.txt"

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                      std::runtime_error,
                      "The \"test_u238_ace_file.txt\" data file could not be "
                      "found (check ace test data directory path)!" );

  if( !database.doPropertiesExist( 92238 ) )
    database.initializeNuclide( 92238, 236.005800 );

  Data::NuclideProperties& nuclide_properties =
    database.getNuclideProperties( 92238 );

  std::shared_ptr<const Data::NuclearDataProperties>
    nuclear_properties( new Data::ACENuclearDataProperties( 236.005800,
                                                            2.53010E-08*MeV,
                                                            ace_test_data_file,
                                                            1,
                                                            "92238.70c" ) );
  
  nuclide_properties.setNuclearDataProperties( nuclear_properties );
}

// Add the "test_u_epr_ace_file.txt" properties
void addUEPRACEFile( const boost::filesystem::path& ace_test_data_dir,
                     Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path ace_test_data_file = ace_test_data_dir;
  ace_test_data_dir /= "test_u_epr_ace_file.txt";

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( ace_test_data_file ),
                      std::runtime_error,
                      "The \"test_u_epr_ace_file.txt\" data file could "
                      "not be found (check ace test data directory path)!" );

  if( !database.doPropertiesExist( Data::U_ATOM ) )
    database.initializeNuclide( Data::U_ATOM, 235.984000 );

  Data::AtomProperties& atom_properties =
    database.getAtomProperties( Data::U_ATOM );

  auto atomic_weight =
    235.984000*Utility::PhysicalConstants::neutron_rest_mass_amu_q;

  std::shared_ptr<const Data::PhotoatomicDataProperties>
    photoatomic_properties( new Data::ACEPhotoatomicDataProperties(
                                                            atomic_weight,
                                                            ace_test_data_file,
                                                            1,
                                                            "92000.12p" ) );

  atom_properties.setPhotoatomicDataProperties( photoatomic_properties );

  std::shared_ptr<const Data::ElectroatomicDataProperties>
    electroatomic_properties( new Data::ACEElectroatomicDataProperties(
                                                            atomic_weight,
                                                            ace_test_data_file,
                                                            1,
                                                            "92000.12p" ) );

  atom_properties.setElectroatomicDataProperties( electroatomic_properties );
}

// Add the ENDL test files for H
void addHENDLTestFiles( const boost::filesystem::path& endl_test_data_dir,
                        Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path endl_test_data_file = endl_test_data_dir;
  endl_test_data_dir /= "test_h_endl_native.xml";

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( endl_test_data_file ),
                      std::runtime_error,
                      "The \"test_h_endl_native.xml\" data file could not be "
                      "found (check endl test data directory path)!" );

  if( !database.doPropertiesExist( Data::H_ATOM ) )
    database.initializeNuclide( Data::H_ATOM, 0.999242 );

  Data::AtomProperties& nuclide_properties =
    database.getAtomProperties( Data::H_ATOM );

  auto atomic_weight =
    0.999242*Utility::PhysicalConstants::neutron_rest_mass_amu_q;

  std::shared_ptr<const Data::PhotoatomicDataProperties>
    photoatomic_properties( new Data::ENDLPhotoatomicDataProperties(
                                                           atomic_weight,
                                                           endl_test_data_file,
                                                           1,
                                                           Data::H_ATOM ) );

  database.setPhotoatomicDataProperties( photoatomic_properties );

  std::shared_ptr<const Data::ElectroatomicDataProperties>
    electroatomic_properties( new Data::ENDLElectroatomicDataProperties(
                                                           atomic_weight,
                                                           endl_test_data_file,
                                                           1,
                                                           Data::H_ATOM ) );

  database.setElectroatomicDataProperties( electroatomic_properties );
}

// Add the ENDL test files for C
void addCENDLTestFiles( const boost::filesystem::path& endl_test_data_dir,
                        Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path endl_test_data_file = endl_test_data_dir;
  endl_test_data_dir /= "test_c_endl_native.xml";

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( endl_test_data_file ),
                      std::runtime_error,
                      "The \"test_c_endl_native.xml\" data file could not be "
                      "found (check endl test data directory path)!" );

  if( !database.doPropertiesExist( Data::C_ATOM ) )
    database.initializeNuclide( Data::C_ATOM, 11.907800 );

  Data::AtomProperties& nuclide_properties =
    database.getAtomProperties( Data::C_ATOM );

  auto atomic_weight =
    11.907800*Utility::PhysicalConstants::neutron_rest_mass_amu_q;

  std::shared_ptr<const Data::PhotoatomicDataProperties>
    photoatomic_properties( new Data::ENDLPhotoatomicDataProperties(
                                                           atomic_weight,
                                                           endl_test_data_file,
                                                           1,
                                                           Data::C_ATOM ) );

  database.setPhotoatomicDataProperties( photoatomic_properties );

  std::shared_ptr<const Data::ElectroatomicDataProperties>
    electroatomic_properties( new Data::ENDLElectroatomicDataProperties(
                                                           atomic_weight,
                                                           endl_test_data_file,
                                                           1,
                                                           Data::C_ATOM ) );

  database.setElectroatomicDataProperties( electroatomic_properties );
}

// Add the ENDL test files for Pb
void addPbENDLTestFiles( const boost::filesystem::path& endl_test_data_dir,
                         Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path endl_test_data_file = endl_test_data_dir;
  endl_test_data_dir /= "test_pb_endl_native.xml";

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( endl_test_data_file ),
                      std::runtime_error,
                      "The \"test_pb_endl_native.xml\" data file could not be "
                      "found (check endl test data directory path)!" );

  if( !database.doPropertiesExist( Data::Pb_ATOM ) )
    database.initializeNuclide( Data::Pb_ATOM, 205.420000 );

  Data::AtomProperties& nuclide_properties =
    database.getAtomProperties( Data::Pb_ATOM );

  auto atomic_weight =
    205.420000*Utility::PhysicalConstants::neutron_rest_mass_amu_q;

  std::shared_ptr<const Data::PhotoatomicDataProperties>
    photoatomic_properties( new Data::ENDLPhotoatomicDataProperties(
                                                           atomic_weight,
                                                           endl_test_data_file,
                                                           1,
                                                           Data::Pb_ATOM ) );

  database.setPhotoatomicDataProperties( photoatomic_properties );

  std::shared_ptr<const Data::ElectroatomicDataProperties>
    electroatomic_properties( new Data::ENDLElectroatomicDataProperties(
                                                           atomic_weight,
                                                           endl_test_data_file,
                                                           1,
                                                           Data::Pb_ATOM ) );

  database.setElectroatomicDataProperties( electroatomic_properties );
}

// Add the "test_epr_1_native.xml" properties
void addHNativeEPRFile( const boost::filesystem::path& native_test_data_dir,
                        Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path native_test_data_file = native_test_data_dir;
  native_test_data_dir /= "test_epr_1_native.xml";

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( endl_test_data_file ),
                      std::runtime_error,
                      "The \"test_epr_1_native.xml\" data file could "
                      "not be found (check native test data directory "
                      "path)!" );

  if( !database.doPropertiesExist( Data::H_ATOM ) )
    database.initializeNuclide( Data::H_ATOM, 0.999242 );

  Data::AtomProperties& atom_properties =
    database.getAtomProperties( Data::H_ATOM );

  auto atomic_weight =
    0.999242*Utility::PhysicalConstants::neutron_rest_mass_amu_q;

  std::shared_ptr<const Data::PhotoatomicDataProperties>
    photoatomic_properties( new Data::NativeEPRPhotoatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         1,
                                                         Data::H_ATOM ) );

  atom_properties.setPhotoatomicDataProperties( photoatomic_properties );

  std::shared_ptr<const Data::ElectroatomicDataProperties>
    electroatomic_properties( new Data::NativeEPRElectroatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         1,
                                                         Data::H_ATOM ) );

  atom_properties.setElectroatomicDataProperties( electroatomic_properties );
}

// Add the "test_aepr_1_native.xml" properties
void addHNativeAEPRFile( const boost::filesystem::path& native_test_data_dir,
                         Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path native_test_data_file = native_test_data_dir;
  native_test_data_dir /= "test_aepr_1_native.xml";

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( native_test_data_file ),
                      std::runtime_error,
                      "The \"test_aepr_1_native.xml\" data file could "
                      "not be found (check native test data directory "
                      "path)!" );

  if( !database.doPropertiesExist( Data::H_ATOM ) )
    database.initializeNuclide( Data::H_ATOM, 0.999242 );

  Data::AtomProperties& atom_properties =
    database.getAtomProperties( Data::H_ATOM );

  auto atomic_weight =
    0.999242*Utility::PhysicalConstants::neutron_rest_mass_amu_q;

  std::shared_ptr<const Data::AdjointPhotoatomicDataProperties>
    photoatomic_properties( new Data::NativeEPRAdjointPhotoatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         1,
                                                         Data::H_ATOM ) );

  atom_properties.setAdjointPhotoatomicDataProperties( photoatomic_properties );

  std::shared_ptr<const Data::AdjointElectroatomicDataProperties>
    electroatomic_properties( new Data::NativeEPRAdjointElectroatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         1,
                                                         Data::H_ATOM ) );

  atom_properties.setAdjointElectroatomicDataProperties( electroatomic_properties );
}

// Add the "test_epr_6_native.xml" properties
void addCNativeEPRFile( const boost::filesystem::path& native_test_data_dir,
                        Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path native_test_data_file = native_test_data_dir;
  native_test_data_dir /= "test_epr_6_native.xml";

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( native_test_data_file ),
                      std::runtime_error,
                      "The \"test_epr_6_native.xml\" data file could "
                      "not be found (check native test data directory "
                      "path)!" );

  if( !database.doPropertiesExist( Data::C_ATOM ) )
    database.initializeNuclide( Data::C_ATOM, 11.907800 );

  Data::AtomProperties& atom_properties =
    database.getAtomProperties( Data::C_ATOM );

  auto atomic_weight =
    11.907800*Utility::PhysicalConstants::neutron_rest_mass_amu_q;

  std::shared_ptr<const Data::PhotoatomicDataProperties>
    photoatomic_properties( new Data::NativeEPRPhotoatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         1,
                                                         Data::C_ATOM ) );

  atom_properties.setPhotoatomicDataProperties( photoatomic_properties );

  std::shared_ptr<const Data::ElectroatomicDataProperties>
    electroatomic_properties( new Data::NativeEPRElectroatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         1,
                                                         Data::C_ATOM ) );

  atom_properties.setElectroatomicDataProperties( electroatomic_properties );
}

// Add the "test_aepr_6_native.xml" properties
void addCNativeAEPRFile( const boost::filesystem::path& native_test_data_dir,
                         Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path native_test_data_file = native_test_data_dir;
  native_test_data_dir /= "test_aepr_6_native.xml";

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( native_test_data_file ),
                      std::runtime_error,
                      "The \"test_aepr_6_native.xml\" data file could "
                      "not be found (check native test data directory "
                      "path)!" );

  if( !database.doPropertiesExist( Data::C_ATOM ) )
    database.initializeNuclide( Data::C_ATOM, 11.907800 );

  Data::AtomProperties& atom_properties =
    database.getAtomProperties( Data::C_ATOM );

  auto atomic_weight =
    11.907800*Utility::PhysicalConstants::neutron_rest_mass_amu_q;

  std::shared_ptr<const Data::AdjointPhotoatomicDataProperties>
    photoatomic_properties( new Data::NativeEPRAdjointPhotoatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         1,
                                                         Data::C_ATOM ) );

  atom_properties.setAdjointPhotoatomicDataProperties( photoatomic_properties );

  std::shared_ptr<const Data::AdjointElectroatomicDataProperties>
    electroatomic_properties( new Data::NativeEPRAdjointElectroatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         1,
                                                         Data::C_ATOM ) );

  atom_properties.setAdjointElectroatomicDataProperties( electroatomic_properties );
}

// Add the "test_epr_13_native.xml" properties
void addAlNativeEPRFile( const boost::filesystem::path& native_test_data_dir,
                         Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path native_test_data_file = native_test_data_dir;
  native_test_data_dir /= "test_epr_13_native.xml";

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( native_test_data_file ),
                      std::runtime_error,
                      "The \"test_epr_13_native.xml\" data file could "
                      "not be found (check native test data directory "
                      "path)!" );

  Data::AtomProperties::AtomicWeight atomic_weight = 2.6982e+01*amu;
  
  if( !database.doPropertiesExist( Data::Al_ATOM ) )
    database.initializeNuclide( Data::Al_ATOM, atomic_weight );

  Data::AtomProperties& atom_properties =
    database.getAtomProperties( Data::Al_ATOM );

  std::shared_ptr<const Data::PhotoatomicDataProperties>
    photoatomic_properties( new Data::NativeEPRPhotoatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         1,
                                                         Data::Al_ATOM ) );

  atom_properties.setPhotoatomicDataProperties( photoatomic_properties );

  std::shared_ptr<const Data::ElectroatomicDataProperties>
    electroatomic_properties( new Data::NativeEPRElectroatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         1,
                                                         Data::Al_ATOM ) );

  atom_properties.setElectroatomicDataProperties( electroatomic_properties );
}

// Add the "test_aepr_13_native.xml" properties
void addAlNativeAEPRFile( const boost::filesystem::path& native_test_data_dir,
                          Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path native_test_data_file = native_test_data_dir;
  native_test_data_dir /= "test_aepr_13_native.xml";

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( native_test_data_file ),
                      std::runtime_error,
                      "The \"test_aepr_13_native.xml\" data file could "
                      "not be found (check native test data directory "
                      "path)!" );

  Data::AtomProperties::AtomicWeight atomic_weight = 2.6982e+01*amu;
  
  if( !database.doPropertiesExist( Data::Al_ATOM ) )
    database.initializeNuclide( Data::Al_ATOM, atomic_weight );

  Data::AtomProperties& atom_properties =
    database.getAtomProperties( Data::Al_ATOM );

  std::shared_ptr<const Data::AdjointPhotoatomicDataProperties>
    photoatomic_properties( new Data::NativeEPRAdjointPhotoatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         1,
                                                         Data::Al_ATOM ) );

  atom_properties.setAdjointPhotoatomicDataProperties( photoatomic_properties );

  std::shared_ptr<const Data::AdjointElectroatomicDataProperties>
    electroatomic_properties( new Data::NativeEPRAdjointElectroatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         1,
                                                         Data::Al_ATOM ) );

  atom_properties.setAdjointElectroatomicDataProperties( electroatomic_properties );
}

// Add the "test_epr_14_native.xml" properties
void addSiNativeEPRFile( const boost::filesystem::path& native_test_data_dir,
                         Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path native_test_data_file = native_test_data_dir;
  native_test_data_dir /= "test_epr_14_native.xml";

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( native_test_data_file ),
                      std::runtime_error,
                      "The \"test_epr_14_native.xml\" data file could "
                      "not be found (check native test data directory "
                      "path)!" );

  Data::AtomProperties::AtomicWeight atomic_weight = 2.8085e+01*amu;
  
  if( !database.doPropertiesExist( Data::Si_ATOM ) )
    database.initializeNuclide( Data::Si_ATOM, atomic_weight );

  Data::AtomProperties& atom_properties =
    database.getAtomProperties( Data::Si_ATOM );

  std::shared_ptr<const Data::PhotoatomicDataProperties>
    photoatomic_properties( new Data::NativeEPRPhotoatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         1,
                                                         Data::Si_ATOM ) );

  atom_properties.setPhotoatomicDataProperties( photoatomic_properties );

  std::shared_ptr<const Data::ElectroatomicDataProperties>
    electroatomic_properties( new Data::NativeEPRElectroatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         1,
                                                         Data::Si_ATOM ) );

  atom_properties.setElectroatomicDataProperties( electroatomic_properties );
}

// Add the "test_aepr_14_native.xml" properties
void addSiNativeAEPRFile( const boost::filesystem::path& native_test_data_dir,
                          Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path native_test_data_file = native_test_data_dir;
  native_test_data_dir /= "test_aepr_14_native.xml";

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( native_test_data_file ),
                      std::runtime_error,
                      "The \"test_aepr_14_native.xml\" data file could "
                      "not be found (check native test data directory "
                      "path)!" );

  Data::AtomProperties::AtomicWeight atomic_weight = 2.8085e+01*amu;
  
  if( !database.doPropertiesExist( Data::Si_ATOM ) )
    database.initializeNuclide( Data::Si_ATOM, atomic_weight );

  Data::AtomProperties& atom_properties =
    database.getAtomProperties( Data::Si_ATOM );

  std::shared_ptr<const Data::AdjointPhotoatomicDataProperties>
    photoatomic_properties( new Data::NativeEPRAdjointPhotoatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         1,
                                                         Data::Si_ATOM ) );

  atom_properties.setAdjointPhotoatomicDataProperties( photoatomic_properties );

  std::shared_ptr<const Data::AdjointElectroatomicDataProperties>
    electroatomic_properties( new Data::NativeEPRAdjointElectroatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         1,
                                                         Data::Si_ATOM ) );

  atom_properties.setAdjointElectroatomicDataProperties( electroatomic_properties );
}

// Add the "test_epr_82_native.xml" properties
void addPbNativeEPRFile( const boost::filesystem::path& native_test_data_dir,
                         Data::ScatteringCenterPropertiesDatabase& database )
{
  boost::filesystem::path native_test_data_file = native_test_data_dir;
  native_test_data_dir /= "test_epr_82_native.xml";

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( native_test_data_file ),
                      std::runtime_error,
                      "The \"test_epr_82_native.xml\" data file could "
                      "not be found (check native test data directory "
                      "path)!" );

  Data::AtomProperties::AtomicWeight atomic_weight = 2.072e+02*amu;
  
  if( !database.doPropertiesExist( Data::Pb_ATOM ) )
    database.initializeNuclide( Data::Pb_ATOM, atomic_weight );

  Data::AtomProperties& atom_properties =
    database.getAtomProperties( Data::Pb_ATOM );

  std::shared_ptr<const Data::PhotoatomicDataProperties>
    photoatomic_properties( new Data::NativeEPRPhotoatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         1,
                                                         Data::Pb_ATOM ) );

  atom_properties.setPhotoatomicDataProperties( photoatomic_properties );

  std::shared_ptr<const Data::ElectroatomicDataProperties>
    electroatomic_properties( new Data::NativeEPRElectroatomicDataProperties(
                                                         atomic_weight,
                                                         native_test_data_file,
                                                         1,
                                                         Data::Pb_ATOM ) );

  atom_properties.setElectroatomicDataProperties( electroatomic_properties );
}
  
} // end Details namespace

//---------------------------------------------------------------------------//
// end database_generator.cpp
//---------------------------------------------------------------------------//
