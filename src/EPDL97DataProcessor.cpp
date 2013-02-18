//---------------------------------------------------------------------------//
// \file EPDL97DataProcessor.cpp
// \author Alex Robinson
// \brief EPDL97 data processor base class non-template member function 
// definitions
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <cmath>

// FACEMC Includes
#include "EPDL97DataProcessor.hpp"
#include "ElectronShell.hpp"
#include "FACEMC_assertion.hpp"
#include "DataPoint.hpp"

namespace FACEMC{

//! Read the first table header
void EPDL97DataProcessor::readFirstTableHeader( FILE* datafile,
						int &atomic_number,
						int &outgoing_particle_designator,
						int &atomic_weight,
						int &interpolation_flag )
{
  // Variables for reading in EPDL data file header 1
  //  the variable names are consistent with the names in the EPDL docs
  char zaid[7];
  zaid[6] = '\0';
  char space[2];
  space[1] = '\0';
  char Yi[2];
  yi[1] = '\0';
  char Yo[3];
  yo[2] = '\0';
  char Al[10];
  AWl[9] = '\0';
  char Ar[3];
  AWr[2] = '\0';
  char date[7];
  data[6] = '\0';
  char iflag[2];
  iflag[1] = '\0';
  char extra[40];
  extra[39] = '\0';

  // File read return value dummy
  int rv;

  // Read first header
  rv = fscanf( epdl, "%6c%1c%2c%1c%2c%1c%9c%2c%1c%6c%1c%39c", zaid, space, Yi, 
	       space, Yo, space, Al, Ar, space, date, iflag, extra ); 

  atomic_number = atoi(zaid)/1000;
  outgoing_particle_designator = atoi(Yo);
  atomic_weight = extractValue<double>( Al, Ar );
  interpolation_flag = atoi(iflag);
}

//! Read the second table header
void EPDL97DataProcessor::readSecondTableHeader( FILE* datafile, 
						 int &reaction_type,
						 int &electron_shell )
{
  // Variables for reading in the EPDL data file header 2
  //  the variable names are consistent with the names in the EPDL docs
  char C [3];
  C[2] = '\0';
  char I [4];
  Ic[3] = '\0';
  char S [4];
  Sc[3] = '\0';
  char garbage [14];
  garbage[13] = '\0';
  char X1l [10];
  X1l[9] = '\0';
  char X1r [3];
  X1r[2] = '\0';
  char extra [38];
  extra[37] = '\0';

  // File read return value dummy
  int rv;
  
  // Read second header
  rv = fscanf( epdl, "%2c%3c%3c%13c%9c%2c%37c", C, I, S, garbage, X1l, X1r, 
	       extra );
  
  reaction_type = atoi(C)*1000 + atoi(I);
  electron_shell = extractValue<int>( X1l, X1r );  
}

//! Skip two column table in EPDL file
void EPDL97DataProcessor::skipTwoColumnTable( FILE* datafile )
{
  char line[24];
  line[0] = 'n';
  line[23] = '\0';
  char test[] = "                       ";
  char end_of_table[51];
  end_of_table[50] = '\0';
  int rv; // dummy return value for file reading

  while( strcmp( line, test ) != 0 )
    rv = fscanf( datafile, "%23c", line );

  // Read rest of end of table line
  rv = fscanf( datafile, "%50c", end_of_table );
}

//! Skip three column table in EPDL file
void EPDL97DataProcessor::skipThreeColumnTable( FILE* datafile )
{
  char line[35];
  line[0] = 'n';
  line[34] = '\0';
  char test[] = "                                  ";
  char end_of_table[40];
  end_of_table[39] = '\0';
  int rv; // dummy return value for file reading
  
  while( strcmp( line, test ) != 0 )
    rv = fscanf( datafile, "%34c", line );

  // Read rest of end of table line
  rv = fscanf( datafile, "%39c", end_of_table );
}

//! Read three column table in EPDL file
void EPDL97DataProcessor::readThreeColumnTable( FILE* datafile,
						Teuchos::Array<DataPoint<int,double,double> > data )
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
  DataPoint<int,double,double> data_point;

  // Read the table one line at a time
  while( strcmp( data1_l, test ) != 0 )
  {
    rv = fscanf( datafile, "%9c%2c%9c%2c%9c%2c%1c", data1_l, data1_r, data2_l,
		 data2_r, data3_l, data3_r, nwln);
    if( strcmp( data1_l, test ) != 0 )
    {
      data_point.value1 = extractValue<int>( data1_l, data1_r );
      data_point.value2 = extractValue<double>( data2_l, data2_r );
      data_point.value3 = extractValue<double>( data3_l, data3_r );
      
      data.push_back( data_point );
    }
  }

  // Read rest of end of table line
  rv = fscanf( datafile, "%39c", end_of_table );
}

//! Skip four column table in EPDL file
void EPDL97DataProcessor::skipFourColumnTable( FILE* datafile )
{
  char line[46];
  line[0] = 'n';
  line[45] = '\0';
  char test[] = "                                             ";
  char end_of_table[29];
  end_of_table[28] = '\0';
  int rv; // dummy return value for file reading
  
  while( strcmp( line, test ) != 0 )
    rv = fscanf( datafile, "%45c", line );

  // Read rest of end of table line
  rv = fscanf( datafile, "%28c", end_of_table );
}

//! Read four column table in EPDL file
void EPDL97DataProcessor::readFourColumnTable( FILE* datafile,
					       Teuchos::Array<DataPoint<int,int,double,double> &data )
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
  DataPoint<int,int,double,double> data_point;

  // Read the table one line at a time
  while( strcmp( data1_l, test ) != 0 )
  {
    rv = fscanf( datafile, "%9c%2c%9c%2c%9c%2c%9c%2c%1c", data1_l, data1_r, 
		 data2_l, data2_r, data3_l, data3_r, data4_l, data4_r, nwln);
    if( strcmp( data1_l, test ) != 0 )
    {
      data_point.value1 = extractValue<int>( data1_l, data1_r );
      data_point.value2 = extractValue<int>( data2_l, data2_r );
      data_point.value3 = extractValue<double>( data3_l, data3_r );
      data_point.value4 = extractValue<double>( data4_l, data4_r );

      data.push_back( data_point );
    }
  }

  // Read rest of end of table line
  rv = fscanf( datafile, "%28c", end_of_table );
}

//! Convert an EPDL shell integer to a shell name
std::string EPDL97DataProcessor::intToShellStr( const int shell )
{
  assertAlways( shell > 0 );
  return ElectronShellStr[shell];
}

//---------------------------------------------------------------------------//
// LogLogDataProcessingPolicy definitions
//---------------------------------------------------------------------------//

//! Process Independent Variable
static inline double EPDL97DataProcessor::LogLogDataProcessingPolicy::processIndependentVar( const double indep_var )
{
  if( indep_var > 0.0 )
    return log( indep_var );
  else
    return log( std::numeric_limits<double>::min() );
}

//! Process Dependent Variable
static inline double EPDL97DataProcessor::LogLogDataProcessingPolicy::processDependentVar( const double dep_var )
{
  if( dep_var > 0.0 )
    return log( dep_var );
  else
    return log( std::numeric_limits<double>::min() );
}

//---------------------------------------------------------------------------//
// LinearLogDataProcessingPolicy definitions
//---------------------------------------------------------------------------//

//! Process Independent Variable
static inline double EPDL97DataProcessor::LinearLogDataProcessingPolicy::processIndependentVar( const double indep_var )
{
  return indep_var;
}

//! Process Dependent Variable
static inline double EPDL97DataProcessor::LinearLogDataProcessingPolicy::processDependentVar( const double dep_var )
{
  if( dep_var > 0.0 )
    return log( dep_var );
  else
    return log( std::numeric_limits<double>::min() );
}

//---------------------------------------------------------------------------//
// LogLinearDataProcessingPolicy definitions
//---------------------------------------------------------------------------//

//! Process Independent Variable
static inline double EPDL97DataProcessor::LogLinearDataProcessingPolicy::processIndependentVar( const double indep_var )
{
  if( indep_var > 0.0 )
    return log( dep_var );
  else
    return log( std::numberic_limits<double>::min() );
}

//! Process Dependent Variable
static inline double EPDL97DataProcessor::LogLinearDataProcessingPolicy::processDependentVar( const double dep_var )
{
  return dep_var;
}

//---------------------------------------------------------------------------//
// LinearLinearDataProcessingPolicy definitions
//---------------------------------------------------------------------------//

//! Process Independent Variable
static inline double EPDL97DataProcessor::LinearLinearDataProcessingPolicy::processIndependentVar( const double indep_var )
{
  return indep_var;
}

//! Process Dependent Variable
static inline double EPDL97DataProcessor::LinearLinearDataProcessingPolicy::processDependentVar( const double dep_var )
{
  return dep_var;
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end EPDL97DataProcessor.cpp
//---------------------------------------------------------------------------//


