//---------------------------------------------------------------------------//
// \file EPDL97DataProcessor.cpp
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
#include "EPDL97DataProcessor.hpp"
#include "ElectronShell.hpp"
#include "FACEMC_Assertion.hpp"
#include "Tuple.hpp"

namespace FACEMC{

//! Read the first table header
void EPDL97DataProcessor::readFirstTableHeader( std::ifstream& datafile,
						unsigned int &atomic_number,
						unsigned int &outgoing_particle_designator,
						double &atomic_weight,
						unsigned int &interpolation_flag )
{
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

  datafile.get( zaid, 7 );
  datafile.get( space, 2 );
  datafile.get( Yi, 3 );
  datafile.get( space, 2 );
  datafile.get( Yo, 3 );
  datafile.get( space, 2 );
  datafile.get( Al, 10 );
  datafile.get( Ar, 3 );
  datafile.get( space, 2 );
  datafile.get( date, 7 );
  datafile.get( iflag, 2 );
  datafile.getline( extra, 40 );

  atomic_number = atoi(zaid)/1000;
  outgoing_particle_designator = atoi(Yo);
  atomic_weight = extractValue<double>( Al, Ar );
  interpolation_flag = atoi(iflag);
}

//! Read the second table header
void EPDL97DataProcessor::readSecondTableHeader( std::ifstream& datafile, 
						 unsigned int &reaction_type,
						 unsigned int &electron_shell )
{
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

  datafile.get( C, 3 );
  datafile.get( I, 4 );
  datafile.get( S, 4 );
  datafile.get( garbage, 14 );
  datafile.get( X1l, 10 );
  datafile.get( X1r, 3 );
  datafile.getline( extra, 38 );
  
  reaction_type = atoi(C)*1000 + atoi(I);
  electron_shell = extractValue<unsigned int>( X1l, X1r );  
}

//! Skip two column table in EPDL file
void EPDL97DataProcessor::skipTwoColumnTable( std::ifstream &datafile )
{
  char line[24];
  line[0] = 'n';
  char test[] = "                       ";
  char end_of_table[51];

  while( strcmp( line, test ) != 0 )
    datafile.getline( line, 24 );

  // Read rest of end of table line
  datafile.getline( end_of_table, 51 );
}

//! Skip three column table in EPDL file
void EPDL97DataProcessor::skipThreeColumnTable( std::ifstream &datafile )
{
  char line[35];
  line[0] = 'n';
  char test[] = "                                  ";
  char end_of_table[40];
  
  while( strcmp( line, test ) != 0 )
    datafile.getline( line, 35 );

  // Read rest of end of table line
  datafile.getline( end_of_table, 40 );
}

//! Read three column table in EPDL file
void EPDL97DataProcessor::readThreeColumnTable( FILE** datafile,
						Teuchos::Array<Trip<unsigned int,double,double> > &data )
{
  char data1_l [10];
  data1_l[9] = '\0';
  data1_l[0] = 'n';
  char data1_r [3];
  data1_r[2] = '\0';
  char data2_l [10];
  data2_l[9] = '\0';
  char data2_r [3];
  data2_r[2] = '\0';
  char data3_l [10];
  data3_l[9] = '\0';
  char data3_r [3];
  data3_r[2] = '\0';
  char nwln [2];
  nwln[1] = '\0';
  char end_of_table [40];
  end_of_table[39] = '\0';
  char test []=  "         ";
  int rv;

  // Make sure that the data array is empty
  data.clear();

  // Data point from table
  Trip<unsigned int,double,double> data_point;

  // Read the table one line at a time
  while( strcmp( data1_l, test ) != 0 )
  {
    rv = fscanf( *datafile, "%9c%2c%9c%2c%9c%2c%1c", data1_l, data1_r, data2_l,
		 data2_r, data3_l, data3_r, nwln);
    if( strcmp( data1_l, test ) != 0 )
    {
      data_point.first = extractValue<unsigned int>( data1_l, data1_r );
      data_point.second = extractValue<double>( data2_l, data2_r );
      data_point.third = extractValue<double>( data3_l, data3_r );
      
      data.push_back( data_point );
    }
  }

  // Read rest of end of table line
  rv = fscanf( *datafile, "%39c", end_of_table );
}

//! Skip four column table in EPDL file
void EPDL97DataProcessor::skipFourColumnTable( std::ifstream &datafile )
{
  char line[46];
  line[0] = 'n';
  char test[] = "                                             ";
  char end_of_table[29];
  
  while( strcmp( line, test ) != 0 )
    datafile.getline( line, 46 );

  // Read rest of end of table line
  datafile.getline( end_of_table, 29 );
}

//! Read four column table in EPDL file
void EPDL97DataProcessor::readFourColumnTable( FILE** datafile,
					       Teuchos::Array<Quad<unsigned int,unsigned int,double,double> > &data )
{
  char data1_l [10];
  data1_l[9] = '\0';
  data1_l[0] = 'n';
  char data1_r [3];
  data1_r[2] = '\0';
  char data2_l [10];
  data2_l[9] = '\0';
  char data2_r [3];
  data2_r[2] = '\0';
  char data3_l [10];
  data3_l[9] = '\0';
  char data3_r [3];
  data3_r[2] = '\0';
  char data4_l [10];
  data3_l[9] = '\0';
  char data4_r [3];
  data3_r[2] = '\0';
  char nwln [2];
  nwln[1] = '\0';
  char end_of_table [29];
  end_of_table[28] = '\0';
  char test []=  "         ";
  int rv;

  // Make sure that the data array is empty
  data.clear();

  // Data point from table
  Quad<unsigned int,unsigned int,double,double> data_point;

  // Read the table one line at a time
  while( strcmp( data1_l, test ) != 0 )
  {
    rv = fscanf( *datafile, "%9c%2c%9c%2c%9c%2c%9c%2c%1c", data1_l, data1_r, 
		 data2_l, data2_r, data3_l, data3_r, data4_l, data4_r, nwln);
    if( strcmp( data1_l, test ) != 0 )
    {
      data_point.first = extractValue<unsigned int>( data1_l, data1_r );
      data_point.second = extractValue<unsigned int>( data2_l, data2_r );
      data_point.third = extractValue<double>( data3_l, data3_r );
      data_point.fourth = extractValue<double>( data4_l, data4_r );

      data.push_back( data_point );
    }
  }

  // Read rest of end of table line
  rv = fscanf( *datafile, "%28c", end_of_table );
}

//! Convert an EPDL shell integer to a shell name
std::string EPDL97DataProcessor::uintToShellStr( const unsigned int shell )
{
  FACEMC_ASSERT_ALWAYS( shell > 0 );
  return ElectronShellStr[shell];
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end EPDL97DataProcessor.cpp
//---------------------------------------------------------------------------//


