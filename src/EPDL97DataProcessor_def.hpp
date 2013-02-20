//---------------------------------------------------------------------------//
// \file EPDL97DataProcessor_def.hpp
// \author Alex Robinson
// \brief EPDL97 data processor base class template member function definitions
//---------------------------------------------------------------------------//

#ifndef EPDL97_DATA_PROCESSOR_DEF_HPP
#define EPDL97_DATA_PROCESSOR_DEF_HPP

// Std Lib Includes
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fstream>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FACEMC includes
#include "Tuple.hpp"

namespace FACEMC{

//! Read two column table in EPDL file within specified range
template<typename DataProcessingPolicy>
void EPDL97DataProcessor::readTwoColumnTableInRange( FILE** datafile,
						     Teuchos::Array<Pair<double,double> >  &data,
						     const double indep_var_min,
						     const double indep_var_max )
{
  // Variables for reading in a two column table
  char data1_l [10];
  data1_l[9] = '\0';
  data1_l[0] = 'n';
  char data1_r [3];
  data1_r[2] = '\0';
  char data2_l [10];
  data2_l[9] = '\0';
  char data2_r [3];
  data2_r[2] = '\0';
  char nwln [2];
  nwln[1] = '\0';
  char end_of_table [51];
  end_of_table[50] = '\0';
  char test []=  "         ";
  int rv;
  
  // Values extracted from the table
  double indep_prev = 0.0, indep = 0.0;
  double dep_prev = 0.0, dep = 0.0;
  
  // Data point extracted from the table
  Pair<double, double> data_point;

  // Make sure that the data array is empty
  data.clear();

  // Read the table one line at a time
  while( strcmp( data1_l, test ) != 0 )
  {
    rv = fscanf( *datafile, "%9c%2c%9c%2c%1c", data1_l, data1_r, data2_l,
		 data2_r, nwln);
    if( strcmp( data1_l, test ) != 0 )
    {
      indep = extractValue<double>( data1_l, 
				    data1_r );
      dep = extractValue<double>( data2_l,
				  data2_r );
      
      // Remove values outside of independent variable range
      if( (indep > indep_var_min && indep_prev > indep_var_min) &&
	  (indep_prev < indep_var_max && indep < indep_var_max) )
      {
	data_point.first = DataProcessingPolicy::processIndependentVar(indep);
	data_point.second = DataProcessingPolicy::processDependentVar(dep);
	data.push_back( data_point );
	
	indep_prev = indep;
	dep_prev = dep;
      }
      else if( (indep > indep_var_min && indep_prev < indep_var_min) ||
	       (indep_prev < indep_var_max && indep > indep_var_max) )
      {
	if( indep_prev > 0.0 )
	{
	  data_point.first = DataProcessingPolicy::processIndependentVar(indep_prev);
	  data_point.second = DataProcessingPolicy::processDependentVar(dep_prev);
	  data.push_back( data_point );
	}
	data_point.first = DataProcessingPolicy::processIndependentVar(indep);
	data_point.second = DataProcessingPolicy::processDependentVar(dep);
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

  // Read rest of end of table line
  rv = fscanf( *datafile, "%50c", end_of_table );
}

//! Read two column table in EPDL file
template<typename DataProcessingPolicy>
void EPDL97DataProcessor::readTwoColumnTable( std::ifstream &datafile,
					      Teuchos::Array<Pair<double,double> > &data )
{
  // Variables for reading in a two column table
  char data1_l [10];
  data1_l[0] = 'n';
  char data1_r [3];
  char data2_l [10];
  char data2_r [4];
  char end_of_table [51];
  char test []=  "         ";
  
  // Values extracted from the table
  double indep = 0.0;
  double dep = 0.0;

  // Data point extracted from the table
  Pair<double, double> data_point;

  // Make sure that the data array is empty
  data.clear();

  // Read the table one line at a time
  while( strcmp( data1_l, test ) != 0 )
  {
    datafile.get( data1_l, 10 );
    datafile.get( data1_r, 3 );
    datafile.get( data2_l, 10 );
    datafile.getline( data2_r, 4 );
    if( strcmp( data1_l, test ) != 0 )
    {
      indep = extractValue<double>( data1_l, 
				    data1_r );
      dep = extractValue<double>( data2_l,
				  data2_r );
      
      data_point.first = DataProcessingPolicy::processIndependentVar(indep);
      data_point.second = DataProcessingPolicy::processDependentVar(dep);
      data.push_back( data_point );
    }
  }

  // Read rest of end of table line
  datafile.getline( end_of_table, 51 );
}

template<typename T>
inline T EPDL97DataProcessor::extractValue( std::string mantissa,
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

//---------------------------------------------------------------------------//
// LogLogDataProcessingPolicy definitions
//---------------------------------------------------------------------------//

//! Process Independent Variable
inline double EPDL97DataProcessor::LogLogDataProcessingPolicy::processIndependentVar( const double indep_var )
{
  if( indep_var > 0.0 )
    return log( indep_var );
  else
    return log( std::numeric_limits<double>::min() );
}

//! Process Dependent Variable
inline double EPDL97DataProcessor::LogLogDataProcessingPolicy::processDependentVar( const double dep_var )
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
inline double EPDL97DataProcessor::LinearLogDataProcessingPolicy::processIndependentVar( const double indep_var )
{
  return indep_var;
}

//! Process Dependent Variable
inline double EPDL97DataProcessor::LinearLogDataProcessingPolicy::processDependentVar( const double dep_var )
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
inline double EPDL97DataProcessor::LogLinearDataProcessingPolicy::processIndependentVar( const double indep_var )
{
  if( indep_var > 0.0 )
    return log( indep_var );
  else
    return log( std::numeric_limits<double>::min() );
}

//! Process Dependent Variable
inline double EPDL97DataProcessor::LogLinearDataProcessingPolicy::processDependentVar( const double dep_var )
{
  return dep_var;
}

//---------------------------------------------------------------------------//
// LinearLinearDataProcessingPolicy definitions
//---------------------------------------------------------------------------//

//! Process Independent Variable
 inline double EPDL97DataProcessor::LinearLinearDataProcessingPolicy::processIndependentVar( const double indep_var )
{
  return indep_var;
}

//! Process Dependent Variable
inline double EPDL97DataProcessor::LinearLinearDataProcessingPolicy::processDependentVar( const double dep_var )
{
  return dep_var;
}

} // end FACEMC namespace

#endif // end EPDL97_DATA_PROCESSOR_DEF_HPP

//---------------------------------------------------------------------------//
// end EPDL97DataProcessor_def.hpp
//---------------------------------------------------------------------------//
