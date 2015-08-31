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
  return d_endlib_file;
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
  char extra[42];

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
  d_endlib_file.getline( extra, 42 );

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

// Process two column table in ENDLIB file 
void ENDLIB97FileHandler::processTwoColumnTable( 
    std::vector<double>& indep_variable,
    std::vector<double>& dep_variable )
{
  // The data file must be valid
  testPrecondition( d_endlib_file );
  // The data arrays must be valid
  testPrecondition( indep_variable.size() == 0 );
  testPrecondition( dep_variable.size() == 0 );
  
  // Variables for reading in a two column table
  char data1_l [10];
  char data1_r [3];
  char data2_l [10];
  char data2_r [3];
  char end_of_table [50];
  char test []=  "         ";
  
  // Values extracted from the table
  double indep, dep;

  // Read the table one line at a time
  do
  {
    d_endlib_file.get( data1_l, 10 );
    d_endlib_file.get( data1_r, 3 );
    d_endlib_file.get( data2_l, 10 );
    d_endlib_file.get( data2_r, 3 );
    d_endlib_file.ignore();
    
    if( strcmp( data1_l, test ) != 0 )
    {
      indep = extractValue<double>( data1_l, data1_r );
      dep = extractValue<double>( data2_l, data2_r );
   
      indep_variable.push_back( indep );
      dep_variable.push_back( dep );
    }
  }
  while( strcmp( data1_l, test ) != 0 );    

  // Read rest of end of table line
  d_endlib_file.getline( end_of_table, 50 );

  // The data file must still be valid
  testPostcondition( d_endlib_file );
  testPostcondition( !indep_variable.empty() );
  testPostcondition( !dep_variable.empty() );
}

// Process three column table in ENDLIB file
void ENDLIB97FileHandler::processThreeColumnTable(
    std::vector<double>& energy_bin,
    std::map<double,std::vector<double> >& indep_variable,
    std::map<double,std::vector<double> >& dep_variable )
{
  // The data file must be valid
  testPrecondition( d_endlib_file );

  // Clear the data arrays 
  energy_bin.clear();
  indep_variable.clear();
  dep_variable.clear();
  
  char data1_l [10];
  char data1_r [3];
  char data2_l [10];
  char data2_r [3];
  char data3_l [10];
  char data3_r [3];
  char end_of_table [40];
  char test []=  "         ";

  // Values extracted from the table
  double energy, indep_point, dep_point;
  std::pair<double,std::vector<double> > indep, dep;

  // Read the table one line at a time
  do
  {
    d_endlib_file.get( data1_l, 10 );
    d_endlib_file.get( data1_r, 3 );
    d_endlib_file.get( data2_l, 10 );
    d_endlib_file.get( data2_r, 3 );
    d_endlib_file.get( data3_l, 10 );
    d_endlib_file.get( data3_r, 3 );
    d_endlib_file.ignore();
    
    if( strcmp( data1_l, test ) != 0 )
    {
      energy = extractValue<double>( data1_l, data1_r );
      indep_point = extractValue<double>( data2_l, data2_r );
      dep_point = extractValue<double>( data3_l, data3_r );

      // start the distribution at the first energy bin
      if ( energy_bin.empty() )
      {
        // insert energy bin
        energy_bin.push_back( energy );
        indep.first = energy;
        dep.first = energy;

        // insert first indep and dep data points at that energy
        indep.second.push_back( indep_point );
        dep.second.push_back( dep_point );
      }
      // start a new distribution at next energy bin
      else if ( energy != energy_bin.back() )
      {
        // insert old distribution
        indep_variable.insert( indep );
        dep_variable.insert( dep );

        // clear indep and dep distributions
        indep.second.clear();
        dep.second.clear();

        // start the new distribution
        energy_bin.push_back( energy );
        indep.first = energy;
        dep.first = energy;
        indep.second.push_back( indep_point );
        dep.second.push_back( dep_point );
      }
      // Continue inderting idep and dep variables for this energy bin
      else
      {
        indep.second.push_back( indep_point );
        dep.second.push_back( dep_point );
      }
    }
  }
  while( strcmp( data1_l, test ) != 0 );

  // insert last distribution
  indep_variable.insert( indep );
  dep_variable.insert( dep );

  // Read rest of end of table line
  d_endlib_file.getline( end_of_table, 40 );

  // The data file must still be valid
  testPostcondition( d_endlib_file );
  testPostcondition( !indep_variable.empty() );
  testPostcondition( !dep_variable.empty() );
  testPostcondition( !energy_bin.empty() );
}

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_ENDLIB97FileHandler.cpp
//---------------------------------------------------------------------------//


