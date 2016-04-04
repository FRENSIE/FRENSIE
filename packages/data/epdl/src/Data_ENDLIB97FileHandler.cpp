//---------------------------------------------------------------------------//
//!
//! \file   Data_ENDLIB97FileHandler.cpp
//! \author Alex Robinson
//! \brief  ENDLIB97 data proc. base class non-template member function defs.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <cmath>
#include <limits>
#include <fstream>
#include <iostream>

// FRENSIE Includes
#include "Data_ENDLIB97FileHandler.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_Assertion.hpp"
#include "Utility_Tuple.hpp"

namespace Data{

// Constructor
/*! \param[in] file_name The name of the ENDLIB-97 file that will be parsed.
 */
ENDLIB97FileHandler::ENDLIB97FileHandler( const std::string &file_name )
{
  d_endlib_file.open( file_name.c_str() );

  // The file name must refer to a valid file
  testPostcondition( d_endlib_file );
}

// Destructor
ENDLIB97FileHandler::~ENDLIB97FileHandler()
{
  if( d_endlib_file.is_open() )
    d_endlib_file.close();
}

// Open an ENDLIB-97 data file
/*! \details If the default constructor is used this function must be called
 * to open the desired ENDLIB-97 data file. 
 * \param[in] file_name The name of the ENDLIB-97 file that will be parsed. 
 */
void ENDLIB97FileHandler::openENDLIB97File( const std::string &file_name )
{
  // Make sure that a previously opened file is closed before opening a new one
  if( d_endlib_file )
    d_endlib_file.close();
  
  d_endlib_file.open( file_name.c_str() );

  // The file name must refer to a valid file
  testPostcondition( d_endlib_file );
}

// Close an ENDLIB-97 data file
void ENDLIB97FileHandler::closeENDLIB97File()
{
  d_endlib_file.close();
}

// Check if the file is valid
bool ENDLIB97FileHandler::validFile() const
{
  return !d_endlib_file.fail();
}

// Check if the entire file has been read
bool ENDLIB97FileHandler::endOfFile() const
{
  return d_endlib_file.eof();
}

// Read the first table header
/*! \details The first ENDLIB-97 table header has important information that 
 * must be extracted before the data table can be read and extracted. This 
 * information includes the atomic number of the element the data in the table
 * corresponds to, the atomic weight of the element, the type of particle that 
 * is emitted from the interaction and the type of interpolation that must be
 * done with the data. This function reads the first table header and extracts
 * the important information. 
 * \param[out] atomic_number The atomic number of the element the data in the 
 * table corresponds to.
 * \param[out] outgoing_particle_designator The outgoing particle from the 
 * interaction.
 * \param[out] atomic_weight The atomic weight of the element represented in the
 * table. 
 * \param[out] interpolation_flag The type of interpolation that must be done 
 * with data in this table.
 * \pre The data file being parsed must be valid.
 * \post The data file must still be valid after reading the first header. When
 * the end of the file is reached, the eof bit won't be set until this function
 * attempts to read another header. Therefore it is possible that the file
 * will not be valid (eof bit set) after calling this function.
 */  
void ENDLIB97FileHandler::readFirstTableHeader( unsigned int &atomic_number,
						unsigned int &outgoing_particle_designator,
						double &atomic_weight,
						unsigned int &interpolation_flag )
{
  // The data file must be valid
  testPrecondition( d_endlib_file );
  
  // Variables for reading in EPDL data file header 1
  //  the variable names are consistent with the names in the EPDL docs,
  //  the variables are one char longer than needed to account for the '\0' char
  char zaid[7];
  char space[2];
  char Yi[3];
  char Yo[3];
  char Al[10];
  char Ar[3];
  char date[7];
  char iflag[2];
  char extra[40];

  d_endlib_file.get( zaid, 7 );
  d_endlib_file.get( space, 2 );
  d_endlib_file.get( Yi, 3 );
  d_endlib_file.get( space, 2 );
  d_endlib_file.get( Yo, 3 );
  d_endlib_file.get( space, 2 );
  d_endlib_file.get( Al, 10 );
  d_endlib_file.get( Ar, 3 );
  d_endlib_file.get( space, 2 );
  d_endlib_file.get( date, 7 );
  d_endlib_file.get( iflag, 2 );
  d_endlib_file.getline( extra, 40 );

  atomic_number = atoi(zaid)/1000;
  outgoing_particle_designator = atoi(Yo);
  atomic_weight = extractValue<double>( Al, Ar );
  interpolation_flag = atoi(iflag);

  // The data file must still be valid (or the eof bit is set)
  testPostcondition( (d_endlib_file || d_endlib_file.eof()) );
}

// Read the second table header
/*! \details The second ENDLIB-97 table header has important information that
 * must be extracted before the data table can be read and extracted. This
 * information includes the type of reaction the data corresponds to and the 
 * electron shell upon which the interaction is assumed to occur. This function
 * reads the second table header and extracts the important information.
 * \param[out] reaction_type The type of reaction the data in the table 
 * corresponds to. See the EPDL-97 documentation for a list of reaction type
 * identifiers. 
 * \param[out] electron_shell The electron shell upon which the interaction is
 * assumed to occur. 
 * \pre The data file being parsed must be valid.
 * \post The data file must still be valid after reading the second header. 
 */
void ENDLIB97FileHandler::readSecondTableHeader( unsigned int &reaction_type,
						 unsigned int &electron_shell )
{
  // The data file must be valid
  testPrecondition( d_endlib_file );
  
  // Variables for reading in the EPDL data file header 2
  //  the variable names are consistent with the names in the EPDL docs,
  //  the variables are one char longer than needed to account for the '\0' char
  char C [3];
  char I [4];
  char S [4];
  char garbage [14];
  char X1l [10];
  char X1r [3];
  char extra [38];

  d_endlib_file.get( C, 3 );
  d_endlib_file.get( I, 4 );
  d_endlib_file.get( S, 4 );
  d_endlib_file.get( garbage, 14 );
  d_endlib_file.get( X1l, 10 );
  d_endlib_file.get( X1r, 3 );
  d_endlib_file.getline( extra, 38 );
  
  reaction_type = atoi(C)*1000 + atoi(I);
  electron_shell = extractValue<unsigned int>( X1l, X1r ); 

  // The data file must still be valid
  testPostcondition( d_endlib_file );
}

// Skip two column table in EPDL file
void ENDLIB97FileHandler::skipTwoColumnTable()
{
  // The data file must be valid
  testPrecondition( d_endlib_file );
  
  char line[23];
  char test[] = "                      ";
  char end_of_table[50];

  do
  {
    d_endlib_file.get( line, 23 );
    d_endlib_file.ignore();
  }
  while( strcmp( line, test ) != 0 );
    

  // Read rest of end of table line
  d_endlib_file.getline( end_of_table, 50 );

  // The data file must still be valid
  testPostcondition( d_endlib_file );
}

// Skip three column table in EPDL file
void ENDLIB97FileHandler::skipThreeColumnTable()
{
  // The data file must be valid
  testPrecondition( d_endlib_file );
  
  char line[34];
  char test[] = "                                 ";
  char end_of_table[40];
  
  do
  {
    d_endlib_file.get( line, 34 );
    d_endlib_file.ignore();
  }
  while( strcmp( line, test ) != 0 );
    
  // Read rest of end of table line
  d_endlib_file.getline( end_of_table, 40 );
}

// Skip four column table in EPDL file
void ENDLIB97FileHandler::skipFourColumnTable()
{
  // The data file must be valid
  testPrecondition( d_endlib_file );
  
  char line[45];
  char test[] = "                                            ";
  char end_of_table[28];
  
  do
  {
    d_endlib_file.get( line, 45 );
    d_endlib_file.ignore();
  }
  while( strcmp( line, test ) != 0 );
    
  // Read rest of end of table line
  d_endlib_file.getline( end_of_table, 28 );

  // The data file must still be valid
  testPostcondition( d_endlib_file );
}

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_ENDLIB97FileHandler.cpp
//---------------------------------------------------------------------------//


