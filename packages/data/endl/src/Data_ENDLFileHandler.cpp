//---------------------------------------------------------------------------//
//!
//! \file   Data_ENDLFileHandler.cpp
//! \author Luke Kersting
//! \brief  ENDL electron data extractor class definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <stdexcept>

// FRENSIE Includes
#include "Data_ENDLFileHandler.hpp"
#include "Data_ENDLHelperWrappers.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Data{

// Default Constructor
ENDLFileHandler::ENDLFileHandler()
  : d_endl_file_id( 1 ),
    d_current_line( 0 ),
    d_valid_file( false ),
    d_end_of_file( false )
{ /* ... */ }

// Constructor for reading all data in file
ENDLFileHandler::ENDLFileHandler(
    const std::string& file_name,
    const bool epics_file_type )
  : d_epics_file_type( epics_file_type ),
    d_endl_file_id( 1 ),
    d_current_line( 0 ),
    d_valid_file( false ),
    d_end_of_file( false )
{
  openENDLFile( file_name );
}

// Constructor for reading data specific to a given atomic number
ENDLFileHandler::ENDLFileHandler(
    const std::string& file_name,
    const unsigned atomic_number,
    const bool epics_file_type )
  : d_atomic_number( atomic_number ),
    d_epics_file_type( epics_file_type ),
    d_endl_file_id( 1 ),
    d_current_line( 0 ),
    d_valid_file( false ),
    d_end_of_file( false )
{
  openENDLFile( file_name );
}

// Destructor
ENDLFileHandler::~ENDLFileHandler()
{
  if( fileIsOpenUsingFortran( d_endl_file_id ) )
       closeFileUsingFortran( d_endl_file_id );
}

// Open an ENDL library file
void ENDLFileHandler::openENDLFile( const std::string& file_name )
{
  // Make sure no other endl library is open and assigned the desired id
  testPrecondition( !fileIsOpenUsingFortran( d_endl_file_id ) );

  // Check that the file exists
  bool endl_file_exists = (bool)fileExistsUsingFortran( file_name.c_str(),
						       file_name.size() );
  TEST_FOR_EXCEPTION( !endl_file_exists,
		      std::runtime_error,
		      "ENDL file " + file_name +
		      " does not exists." );

  // Check that the file can be opened
  bool endl_file_is_readable = (bool)fileIsReadableUsingFortran( file_name.c_str(),
							        file_name.size() );
  TEST_FOR_EXCEPTION( !endl_file_is_readable,
		      std::runtime_error,
		      "ENDL file " + file_name +
		      " exists but is not readable." );

  // Open the file
  openFileUsingFortran( file_name.c_str(), file_name.size(), d_endl_file_id );

  // Set file flags and line number
  d_valid_file = true;
  d_end_of_file = false;
  d_current_line = 1;

  // Make sure the endl library is open and assigned the desired id
  testPostcondition( fileIsOpenUsingFortran( d_endl_file_id ) );
}

// Close an ENDL data file
void ENDLFileHandler::closeENDLFile()
{
  // Close the ENDL File
  closeFileUsingFortran( d_endl_file_id );

  // Make sure no endl library is open and assigned the desired id
  testPostcondition( !fileIsOpenUsingFortran( d_endl_file_id ) );
}

// Check if the file is valid
bool ENDLFileHandler::validFile() const
{
  return d_valid_file;
}

// Check if the entire file has been read
bool ENDLFileHandler::endOfFile() const
{
  return d_end_of_file;
}

// Read the first table header
void ENDLFileHandler::readFirstTableHeader(
        int& atomic_number,
        int& outgoing_particle_type,
        double& atomic_mass,
        int& interpolation_flag )
{
  int zaids, incident_particle_type, table_date;
  int io_flag;

  readENDLTableHeaderLine1(
        d_endl_file_id,
        &zaids,
        &incident_particle_type,
        &outgoing_particle_type,
        &atomic_mass,
        &table_date,
        &interpolation_flag,
        &io_flag );

  // Update file flags and line number
  ++d_current_line;

  if( io_flag > 0 )
  {
    d_valid_file = false;
  }
  else if ( io_flag < 0 )
  {
    d_end_of_file = true;
  }

  // Calculate atomic number from zaids
  atomic_number = zaids/1000;

  testPostcondition( validFile() );
}

// Read the second table header
void ENDLFileHandler::readSecondTableHeader(
        int& reaction_type,
        int& electron_shell )
{
  int reaction_descriptor, reaction_property, reaction_modifier;
  int io_flag;
  double subshell_designator;

  readENDLTableHeaderLine2(
        d_endl_file_id,
        &reaction_descriptor,
        &reaction_property,
        &reaction_modifier,
        &subshell_designator,
        &io_flag );

  // Update file flags and line number
  ++d_current_line;

  if( io_flag > 0 )
  {
    d_valid_file = false;
  }
  else if ( io_flag < 0 )
  {
    d_end_of_file = true;
  }

  // Calculate reaction type from the reaction designator and property
  reaction_type = reaction_descriptor*1000 + reaction_property;

  // Calculate the electron shell from the subshell designator
  electron_shell = subshell_designator;

  testPostcondition( validFile() );
}

// Skip table in ENDL file
void ENDLFileHandler::skipTable()
{
  int io_flag, table_size;

  skipENDLTable( d_endl_file_id, &table_size, &io_flag );

  // Update file flags and line number
  d_current_line += table_size+1;

  if( io_flag > 0 )
  {
    d_valid_file = false;
  }
  else if ( io_flag < 0 )
  {
    d_end_of_file = true;
  }

  testPostcondition( validFile() );
}

// Process two column table in ENDL file
void ENDLFileHandler::processTwoColumnTable(
    std::vector<double>& indep_variable,
    std::vector<double>& dep_variable )
{
  int io_flag, table_size;

  // Read table size
  readENDLTableSize(
        d_endl_file_id,
        d_current_line,
        &table_size,
        &io_flag );

  // Resize arrays to table size
  indep_variable.resize( table_size );
  dep_variable.resize( table_size );

  if ( d_epics_file_type )
  {
		// Read table data
		readEPICSTableTwoColumn(
		      d_endl_file_id,
		      table_size,
		      &indep_variable[0],
		      &dep_variable[0],
		      &io_flag );
  }
  else
  {
		// Read table data
		readENDLTableTwoColumn(
		      d_endl_file_id,
		      table_size,
		      &indep_variable[0],
		      &dep_variable[0],
		      &io_flag );
  }

  // Update file flags and line number
  d_current_line += table_size+1;

  if( io_flag > 0 )
  {
    d_valid_file = false;
  }
  else if ( io_flag < 0 )
  {
    d_end_of_file = true;
  }

  testPostcondition( validFile() );
}

// Process three column table in ENDL file
void ENDLFileHandler::processThreeColumnTable(
    std::vector<double>& column_one,
    std::vector<double>& column_two,
    std::vector<double>& column_three  )
{
  int io_flag, table_size;

  // Read table size
  readENDLTableSize(
        d_endl_file_id,
        d_current_line,
        &table_size,
        &io_flag );

  // Resize arrays to table size
  column_one.resize( table_size );
  column_two.resize( table_size );
  column_three.resize( table_size );

  if ( d_epics_file_type )
  {
	// Read EPICS2014 table data
    readEPICSTableThreeColumn(
        d_endl_file_id,
        table_size,
        &column_one[0],
        &column_two[0],
        &column_three[0],
        &io_flag );
  }
  else
  {
	// Read regular table data
    readENDLTableThreeColumn(
        d_endl_file_id,
        table_size,
        &column_one[0],
        &column_two[0],
        &column_three[0],
        &io_flag );
  }

  // Update file flags and line number
  d_current_line += table_size+1;

  if( io_flag > 0 )
  {
    d_valid_file = false;
  }
  else if ( io_flag < 0 )
  {
    d_end_of_file = true;
  }

  testPostcondition( validFile() );
  testPostcondition( !column_one.empty() );
  testPostcondition( !column_two.empty() );
  testPostcondition( !column_three.empty() );
}

// Process four column table in ENDL file
void ENDLFileHandler::processFourColumnTable(
    std::vector<double>& column_one,
    std::vector<double>& column_two,
    std::vector<double>& column_three,
    std::vector<double>& column_four )
{
  int io_flag, table_size;

  // Read table size
  readENDLTableSize(
        d_endl_file_id,
        d_current_line,
        &table_size,
        &io_flag );

  // Resize arrays to table size
  column_one.resize( table_size );
  column_two.resize( table_size );
  column_three.resize( table_size );
  column_four.resize( table_size );

  if ( d_epics_file_type )
  {
	// Read EPICS2014 table data
    readEPICSTableFourColumn(
        d_endl_file_id,
        table_size,
        &column_one[0],
        &column_two[0],
        &column_three[0],
        &column_four[0],
        &io_flag );
  }
  else
  {
	// Read regular table data
    readENDLTableFourColumn(
        d_endl_file_id,
        table_size,
        &column_one[0],
        &column_two[0],
        &column_three[0],
        &column_four[0],
        &io_flag );
  }

  // Update file flags and line number
  d_current_line += table_size+1;

  if( io_flag > 0 )
  {
    d_valid_file = false;
  }
  else if ( io_flag < 0 )
  {
    d_end_of_file = true;
  }

  testPostcondition( !column_one.empty() );
  testPostcondition( !column_two.empty() );
  testPostcondition( !column_three.empty() );
  testPostcondition( !column_four.empty() );
}

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_ENDLFileHandler.cpp
//---------------------------------------------------------------------------//
