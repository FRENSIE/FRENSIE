//---------------------------------------------------------------------------//
// \file   ENDLIB97FileHandler.cpp
// \author Alex Robinson
// \brief EPDL97 data processor base class non-template member function 
// definitions
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <cmath>
#include <limits>
#include <fstream>
#include <iostream>

// FACEMC Includes
#include "ENDLIB97FileHandler.hpp"
#include "ContractException.hpp"
#include "FACEMC_Assertion.hpp"
#include "Tuple.hpp"

namespace FACEMC{

//! Constructor
ENDLIB97FileHandler::ENDLIB97FileHandler( const std::string &file_name )
{
  d_endlib_file.open( file_name.c_str() );

  // The file name must refer to a valid file
  testPostCondition( d_endlib_file );
}

//! Open an ENDLIB-97 data file
void ENDLIB97FileHandler::openENDLIB97File( const std::string &file_name )
{
  d_endlib_file.open( file_name.c_str() );

  // The file name must refer to a valid file
  testPostCondition( d_endlib_file );
}

//! Close an ENDLIB-97 data file
void ENDLIB97FileHandler::closeENDLIB97File()
{
  d_endlib_file.close();
}

//! Check if the file is valid
inline bool ENDLIB97FileHandler::validFile()
{
  return d_endlib_file;
}

//! Check if the entire file has been read
inline bool ENDLIB97FileHandler::endOfFile()
{
  return d_endlib_file.eof();
}

//! Read the first table header
void ENDLIB97FileHandler::readFirstTableHeader( unsigned int &atomic_number,
						unsigned int &outgoing_particle_designator,
						double &atomic_weight,
						unsigned int &interpolation_flag )
{
  // The datafile must be valid
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

//! Read the second table header
void ENDLIB97FileHandler::readSecondTableHeader( unsigned int &reaction_type,
						 unsigned int &electron_shell )
{
  // The datafile must be valid
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

//! Skip two column table in EPDL file
void ENDLIB97FileHandler::skipTwoColumnTable()
{
  // The datafile must be valid
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

//! Skip three column table in EPDL file
void ENDLIB97FileHandler::skipThreeColumnTable()
{
  // The datafile must be valid
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

//! Skip four column table in EPDL file
void ENDLIB97FileHandler::skipFourColumnTable()
{
  // The datafile must be valid
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

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end ENDLIB97FileHandler.cpp
//---------------------------------------------------------------------------//


