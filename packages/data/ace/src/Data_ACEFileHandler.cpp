//---------------------------------------------------------------------------//
//!
//! \file   Data_ACEFileHandler.cpp
//! \author Alex Robinson
//! \brief  A Compact ENDF file handler class definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <stdexcept>

// FRENIE Includes
#include "Data_ACEFileHandler.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"

//! The fortran ace file helper functions
extern "C" {
  int fileExistsUsingFortran( const char* file_name, const int file_name_size );
  int fileIsReadableUsingFortran( const char* file_name, const int file_name_size );
  int fileIsOpenUsingFortran( const int file_id );
  void openFileUsingFortran( const char* file_name, 
		       const int file_name_size,
		       const int file_id );
  void closeFileUsingFortran( const int file_id );
  void moveToLineUsingFortran( const int file_id, const int table_start_line );
  void readAceTableHeaderLine1( const int file_id,
				char* table_name, 
				double* atomic_weight_ratio,
				double* temperature,
				char* table_date );
  void readAceTableHeaderLine2( const int file_id, 
				char* comment, 
				char* material_id );
  void readAceTableZaidsAndAwrs( const int file_id, int* zaids, double* awrs );
  void readAceTableNXSArray( const int file_id, int* nxs );
  void readAceTableJXSArray( const int file_id, int* jxs );
  void readAceTableXSSArray( const int file_id, 
			     double* xss, 
			     const int xss_size );
}

namespace Data{

// Constructor
ACEFileHandler::ACEFileHandler( const std::string& file_name,
				const std::string& table_name,
				const unsigned table_start_line,
				const bool is_ascii )
  : d_ace_file_id( 1 ),
    d_ace_library_name( file_name ),
    d_ace_table_name( 10, ' ' ),
    d_ace_table_processing_date( 10, ' ' ),
    d_ace_table_comment( 70, ' ' ),
    d_ace_table_material_id( 10, ' ' ),
    d_atomic_weight_ratio( 0.0 ),
    d_temperature( 0.0 ),
    d_zaids(),
    d_atomic_weight_ratios(),
    d_nxs(),
    d_jxs(),
    d_xss()
{ 
  openACEFile( file_name, is_ascii );
  readACETable( table_name, table_start_line );
}

// Destructor
ACEFileHandler::~ACEFileHandler()
{
    closeFileUsingFortran( d_ace_file_id );
}

// Open an ACE library file
void ACEFileHandler::openACEFile( const std::string& file_name, 
				  const bool is_ascii )
{
  // Make sure no other ace library is open and assigned the desired id
  testPrecondition( !fileIsOpenUsingFortran( d_ace_file_id ) );
  
  // Binary files cannot currently be handled
  TEST_FOR_EXCEPTION( !is_ascii, 
		      std::runtime_error, 
		      "Fatal Error: Binary ACE files cannot currently be read ("+ file_name + ")." );
  
  // Check that the file exists
  bool ace_file_exists = (bool)fileExistsUsingFortran( file_name.c_str(), 
						       file_name.size() );
  TEST_FOR_EXCEPTION( !ace_file_exists, 
		      std::runtime_error, 
		      "Fatal Error: ACE file " + file_name + 
		      " does not exists." );
  
  // Check that the file can be opened
  bool ace_file_is_readable = (bool)fileIsReadableUsingFortran( file_name.c_str(),
							        file_name.size() );
  TEST_FOR_EXCEPTION( !ace_file_is_readable,
		      std::runtime_error,
		      "Fatal Error: ACE file " + file_name +
		      " exists but is not readable." );
  
  // Open the file
  openFileUsingFortran( file_name.c_str(), file_name.size(), d_ace_file_id );

  // Make sure the ace library is open and assigned the desired id
  testPostcondition( fileIsOpenUsingFortran( d_ace_file_id ) );
}

// Read a table in the ACE file
void ACEFileHandler::readACETable( const std::string& table_name,
				   const unsigned table_start_line )
{
  // Move to the start of the ACE table in the ACE file
  moveToLineUsingFortran( d_ace_file_id, static_cast<int>( table_start_line ) );

  // Read the first line of the ACE table header
  readAceTableHeaderLine1( d_ace_file_id,
			   &d_ace_table_name[0],
			   &d_atomic_weight_ratio,
			   &d_temperature,
			   &d_ace_table_processing_date[0] );

  // Clear white space from the ace table name and processing date
  removeWhiteSpaceFromString( d_ace_table_name );
  removeWhiteSpaceFromString( d_ace_table_processing_date );

  // Test that the table name is the same as the desired table name
  {
    bool expected_table_name = 
      (table_name.compare( d_ace_table_name ) == 0 ? true : false);
    
    if( !expected_table_name )
    {
      std::stringstream ss;
      
      ss << "Fatal Error: Expected table " << table_name << " at line " 
	 << table_start_line << " of ACE library " << d_ace_library_name
	 << " but found table " << d_ace_table_name 
	 << ". The cross_sections.xml file is likely corrupted."
	 << std::endl;
      
      TEST_FOR_EXCEPTION( !expected_table_name,
			  std::runtime_error,
			  ss.str() );
    }
  }

  // Read the second line of the ACE table header
  readAceTableHeaderLine2( d_ace_file_id,
			   &d_ace_table_comment[0],
			   &d_ace_table_material_id[0] );

  // Read the zaids and awrs
  readAceTableZaidsAndAwrs( d_ace_file_id,
			    d_zaids.getRawPtr(),
			    d_atomic_weight_ratios.getRawPtr() );

  // Read the nxs array
  readAceTableNXSArray( d_ace_file_id, d_nxs.getRawPtr() );

  // Read the jxs array
  readAceTableJXSArray( d_ace_file_id, d_jxs.getRawPtr() );
  
  // Resize the xss array
  d_xss.resize( d_nxs[0] );

  // Read the xss array
  readAceTableXSSArray( d_ace_file_id, d_xss.getRawPtr(), d_xss.size() );
}

// Remove white space from table name
void ACEFileHandler::removeWhiteSpaceFromString( std::string& string ) const
{
  unsigned white_space_loc = string.find( " " );
  
  while( white_space_loc < string.size() )
  {
    string.erase( white_space_loc, 1 );

    white_space_loc = string.find( " ", white_space_loc );
  }
}

// Get the library name
const std::string& ACEFileHandler::getLibraryName() const
{
  return d_ace_library_name;
}

// Get the table name
const std::string& ACEFileHandler::getTableName() const
{
  return d_ace_table_name;
}

// Get the table atomic weight ratio
double ACEFileHandler::getTableAtomicWeightRatio() const
{
  return d_atomic_weight_ratio;
}

// Get the table temperature
double ACEFileHandler::getTableTemperature() const
{
  return d_temperature;
}

// Get the table processing date
const std::string& ACEFileHandler::getTableProcessingDate() const
{
  return d_ace_table_processing_date;
}

// Get the table comment
const std::string& ACEFileHandler::getTableComment() const
{
  return d_ace_table_comment;
}

// Get the table mat id
const std::string& ACEFileHandler::getTableMatId() const
{
  return d_ace_table_material_id;
}

// Get the table zaids
Teuchos::ArrayView<const int> ACEFileHandler::getTableZAIDs() const
{
  return d_zaids();
}

// Get the table atomic weight ratios
Teuchos::ArrayView<const double> 
ACEFileHandler::getTableAtomicWeightRatios() const
{
  return d_atomic_weight_ratios();
}

// Get the table NXS array
Teuchos::ArrayView<const int> ACEFileHandler::getTableNXSArray() const
{
  return d_nxs();
}

// Get the table JXS array
Teuchos::ArrayView<const int> ACEFileHandler::getTableJXSArray() const
{
  return d_jxs();
}

// Get the table XSS array
Teuchos::ArrayRCP<const double> ACEFileHandler::getTableXSSArray() const
{
  return d_xss.getConst();
}

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_ACEFileHandler.cpp
//---------------------------------------------------------------------------//
