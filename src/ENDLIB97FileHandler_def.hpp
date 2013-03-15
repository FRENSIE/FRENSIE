//---------------------------------------------------------------------------//
// \file   ENDLIB97FileHandler_def.hpp
// \author Alex Robinson
// \brief  ENDLIB-97 data file handler class template member function 
// definitions.
//---------------------------------------------------------------------------//

#ifndef ENDLIB97_FILE_HANDLER_DEF_HPP
#define ENDLIB97_FILE_HANDLER_DEF_HPP

// Std Lib Includes
#include <iostream>
#include <string>
#include <fstream>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FACEMC includes
#include "Tuple.hpp"
#include "ContractException.hpp"

namespace FACEMC{

//! Read two column table in ENDLIB file within specified range
template<typename T>
void ENDLIB97FileHandler::readTwoColumnTableInRange( 
				     Teuchos::Array<T>  &data,
				     const typename T::firstType indep_var_min,
				     const typename T::firstType indep_var_max )
{
  // The datafile must be valid
  testPrecondition( d_endlib_file );
  // The data array must be valid
  testPrecondition( data.size() == 0 );
  
  // Variables for reading in a two column table
  char data1_l [10];
  char data1_r [3];
  char data2_l [10];
  char data2_r [3];
  char end_of_table [50];
  char test []=  "         ";
  
  // Values extracted from the table
  typename T::firstType indep_impossible_min = 
    std::numeric_limits<double>::infinity()*-1;
  typename T::firstType indep_prev = indep_impossible_min, indep = 0.0;
  typename T::secondType dep_prev = 0.0, dep = 0.0;
  
  // Data point extracted from the table
  T data_point;

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
      indep = extractValue<typename T::firstType>( data1_l, data1_r );
      dep = extractValue<typename T::secondType>( data2_l, data2_r );
      
      // Remove values outside of independent variable range
      if( (indep > indep_var_min && indep_prev > indep_var_min) &&
	  (indep_prev < indep_var_max && indep <= indep_var_max) )
      {
	data_point.first = indep;
	data_point.second = dep;
	data.push_back( data_point );
	
	indep_prev = indep;
	dep_prev = dep;
      }
      else if( indep > indep_var_min && indep_prev <= indep_var_min &&
	       indep_prev > indep_impossible_min )
      {
	
	data_point.first = indep_prev;
	data_point.second = dep_prev;
	data.push_back( data_point );

	data_point.first = indep;
	data_point.second = dep;
	data.push_back( data_point );
	
	indep_prev = indep;
	dep_prev = dep;
      }
      else if( indep_prev < indep_var_max && indep > indep_var_max)
      {
	data_point.first = indep;
	data_point.second = dep;
	data.push_back( data_point );
	
	indep_prev = indep;
	dep_prev = dep;
      }
      else if( indep > indep_var_min && indep_prev == indep_impossible_min )
      {
	data_point.first = indep;
	data_point.second = dep;
	data.push_back( data_point );
	
	indep_prev = indep;
	dep_prev = dep;
      }
      else
      {
	indep_prev = indep;
	dep_prev = dep;
      }
    }
  }
  while( strcmp( data1_l, test ) != 0 );
    

  // Read rest of end of table line
  d_endlib_file.getline( end_of_table, 50 );

  // The data file must still be valid
  testPostcondition( d_endlib_file );
}

//! Read two column table in ENDLIB file
template<typename T>
void ENDLIB97FileHandler::readTwoColumnTable( Teuchos::Array<T> &data )
{
  // The datafile must be valid
  testPrecondition( d_endlib_file );
  // The data array must be valid
  testPrecondition( data.size() == 0 );
  
  // Variables for reading in a two column table
  char data1_l [10];
  char data1_r [3];
  char data2_l [10];
  char data2_r [3];
  char end_of_table [50];
  char test []=  "         ";
  
  // Values extracted from the table
  typename T::firstType indep = 0.0;
  typename T::secondType dep = 0.0;

  // Data point extracted from the table
  T data_point;

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
      indep = extractValue<typename T::firstType>( data1_l, data1_r );
      dep = extractValue<typename T::secondType>( data2_l, data2_r );
      
      data_point.first = indep;
      data_point.second = dep;
      data.push_back( data_point );
    }
  }
  while( strcmp( data1_l, test ) != 0 );    

  // Read rest of end of table line
  d_endlib_file.getline( end_of_table, 50 );

  // The data file must still be valid
  testPostcondition( d_endlib_file );
}

//! Read three column table in ENDLIB file
template<typename T>
void ENDLIB97FileHandler::readThreeColumnTable(	Teuchos::Array<T> &data )
{
  // The datafile must be valid
  testPrecondition( d_endlib_file );
  // The data array must be valid
  testPrecondition( data.size() == 0 );
  
  char data1_l [10];
  char data1_r [3];
  char data2_l [10];
  char data2_r [3];
  char data3_l [10];
  char data3_r [3];
  char end_of_table [40];
  char test []=  "         ";

  // Make sure that the data array is empty
  data.clear();
  
  // Values extracted from the table
  typename T::firstType first_val;
  typename T::secondType second_val;
  typename T::thirdType third_val;

  // Data point from table
  T data_point;

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
      first_val = extractValue<typename T::firstType>( data1_l, data1_r );
      second_val = extractValue<typename T::secondType>( data2_l, data2_r );
      third_val = extractValue<typename T::thirdType>( data3_l, data3_r );

      data_point.first = first_val;
      data_point.second = second_val;
      data_point.third = third_val;
      
      data.push_back( data_point );
    }
  }
  while( strcmp( data1_l, test ) != 0 );

  // Read rest of end of table line
  d_endlib_file.getline( end_of_table, 40 );

  // The data file must still be valid
  testPostcondition( d_endlib_file );
}

//! Read four column table in EPDL file
template<typename T>
void ENDLIB97FileHandler::readFourColumnTable( Teuchos::Array<T> &data )
{
  // The datafile must be valid
  testPrecondition( d_endlib_file );
  // The data array must be valid
  testPrecondition( data.size() == 0 );
  
  char data1_l [10];
  char data1_r [3];
  char data2_l [10];
  char data2_r [3];
  char data3_l [10];
  char data3_r [3];
  char data4_l [10];
  char data4_r [3];
  char end_of_table [28];
  char test []=  "         ";

  // Values extracted from the table
  typename T::firstType first_val;
  typename T::secondType second_val;
  typename T::thirdType third_val;
  typename T::fourthType fourth_val;

  // Data point from table
  T data_point;

  // Read the table one line at a time
  do
  {
    d_endlib_file.get( data1_l, 10 );
    d_endlib_file.get( data1_r, 3 );
    d_endlib_file.get( data2_l, 10 );
    d_endlib_file.get( data2_r, 3 );
    d_endlib_file.get( data3_l, 10 );
    d_endlib_file.get( data3_r, 3 );
    d_endlib_file.get( data4_l, 10 );
    d_endlib_file.get( data4_r, 3 );
    d_endlib_file.ignore();
    
    if( strcmp( data1_l, test ) != 0 )
    {
      first_val  = extractValue<typename T::firstType>( data1_l, data1_r );
      second_val = extractValue<typename T::secondType>( data2_l, data2_r );
      third_val =  extractValue<typename T::thirdType>( data3_l, data3_r );
      fourth_val = extractValue<typename T::fourthType>( data4_l, data4_r );

      data_point.first = first_val;
      data_point.second = second_val;
      data_point.third = third_val;
      data_point.fourth = fourth_val;

      data.push_back( data_point );
    }
  }
  while( strcmp( data1_l, test ) != 0 );

  // Read rest of end of table line
  d_endlib_file.getline( end_of_table, 28 );

  // The data file must still be valid
  testPostcondition( d_endlib_file );
}

//! Create the desired type from a printed fortran style fixed-width float.
template<typename T>
inline T ENDLIB97FileHandler::extractValue( std::string mantissa,
					    std::string exponent )
{
  std::string string_value;
  
  // test for all possible output cases
  if( strncmp( &mantissa[8], "+", 1 ) == 0 )
  {
    mantissa[8] = '0';
    string_value = mantissa + "e+";
  }
  else if( strncmp( &mantissa[8], "-", 1 ) == 0 )
  {
    mantissa[8] = '0';
    string_value = mantissa + "e-";
  }
  else
    string_value = mantissa;
  
  if( strncmp( &exponent[0], " ", 1 ) == 0 )
    exponent[0] = '0';
  else if( strncmp( &exponent[0], "+", 1 ) == 0 )
  {
    exponent[0] = '0';
    string_value += "e+";
  }
  else if( strncmp( &exponent[0], "-", 1 ) == 0 )
  {
    exponent[0] = '0';
    string_value += "e-";
  }
  
  string_value += exponent;
  
  double double_value = atof( string_value.c_str() );
  
  return static_cast<T>(double_value);
}

} // end FACEMC namespace

#endif // end ENDLIB97_FILE_HANDLER_DEF_HPP

//---------------------------------------------------------------------------//
// end ENDLIB97FileHandler_def.hpp
//---------------------------------------------------------------------------//
