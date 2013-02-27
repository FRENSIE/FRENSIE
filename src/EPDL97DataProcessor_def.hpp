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
template<typename DataProcessingPolicy,
	 typename T,
	 template<typename> class Array>
void EPDL97DataProcessor::readTwoColumnTableInRange( std::ifstream &datafile,
						     Array<T>  &data,
						     const double indep_var_min,
						     const double indep_var_max )
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
  double indep_impossible_min = std::numeric_limits<double>::infinity()*-1;
  double indep_prev = indep_impossible_min, indep = 0.0;
  double dep_prev = 0.0, dep = 0.0;
  
  // Data point extracted from the table
  T data_point;

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
      indep = extractValue<typename T::first_type>( data1_l, 
						    data1_r );
      dep = extractValue<typename T::second_type>( data2_l,
						   data2_r );
      
      // Remove values outside of independent variable range
      if( (indep > indep_var_min && indep_prev > indep_var_min) &&
	  (indep_prev < indep_var_max && indep <= indep_var_max) )
      {
	data_point.first = DataProcessingPolicy::processIndependentVar(indep);
	data_point.second = DataProcessingPolicy::processDependentVar(dep);
	data.push_back( data_point );
	
	indep_prev = indep;
	dep_prev = dep;
      }
      else if( indep > indep_var_min && indep_prev <= indep_var_min &&
	       indep_prev > indep_impossible_min )
      {
	
	data_point.first = DataProcessingPolicy::processIndependentVar(indep_prev);
	data_point.second = DataProcessingPolicy::processDependentVar(dep_prev);
	data.push_back( data_point );

	data_point.first = DataProcessingPolicy::processIndependentVar(indep);
	data_point.second = DataProcessingPolicy::processDependentVar(dep);
	data.push_back( data_point );
	
	indep_prev = indep;
	dep_prev = dep;
      }
      else if( indep_prev < indep_var_max && indep > indep_var_max)
      {
	data_point.first = DataProcessingPolicy::processIndependentVar(indep);
	data_point.second = DataProcessingPolicy::processDependentVar(dep);
	data.push_back( data_point );
	
	indep_prev = indep;
	dep_prev = dep;
      }
      else if( indep > indep_var_min && indep_prev == indep_impossible_min )
      {
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
  datafile.getline( end_of_table, 51 );
}

//! Read two column table in EPDL file
  template<typename DataProcessingPolicy,
	   typename T,
	   template<typename> class Array>
void EPDL97DataProcessor::readTwoColumnTable( std::ifstream &datafile,
					      Array<T> &data )
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
  T data_point;

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
      indep = extractValue<typename T::first_type>( data1_l, 
						    data1_r );
      dep = extractValue<typename T::second_type>( data2_l,
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

//! Create a cdf from an array of data using a taylor series expansion to O(2)
template<typename T,template<typename> class Array>
void EPDLDataProcessor::createContinuousCDFAtFourthTupleLoc( Array<T> &data )
{
  typename Array<T>::iterator data_point_1, data_point_2;
  typename Array<T>::iterator end = data.end();

  data_point_1 = data.begin();
  data_point_2 = data_point_1 + 1;

  // Make sure that the array is not empty
  FACEMC_ASSERT_ALWAYS( (data_point_1 != end) );

  // Make sure that the array has more than one entry
  FACEMC_ASSERT_ALWAYS( (data_point_2 != end) );

  // Initialize the CDF
  data_point_1->fourth = 0.0;
  
  // Calculate the CDF
  // CDF(x) = CDF(x1)+PDF(x1)*(x-x1)+0.5*(PDF(x)-PDF(x1))/(x2-x1)*(x-x1)^2
  while( data_point_2 != end )
  {
    data_point_2->fourth = data_point_1->fourth;
    data_point_2->fourth += data_point_1->second*
      (data_point_2->first - data_point_1->first) +
      0.5*(data_point_2->second - data_point_1->second)*
      (data_point_2->first - data_point_1->first);

    ++data_point_1;
    ++data_point_2;
  }

  // Normalize the CDF
  data_point_1 = data.begin() + 1;
  while( data_point_1 != end )
    data_point_1->fourth /= data.back().fourth;
}

//! Create a discrete CDF in place (second tuple location) from an array of 
// data.
template<typename T,template<typename> class Array>
void EPDLDataProcessor::createDiscreteCDFAtSecondTupleLoc( Array<T> &data )
{
  typename Array<T>::iterator data_point_1, data_point_2;
  typename Array<T>::iterator end = data.end();

  data_point_1 = data.begin();
  data_point_2 = data_point_1 + 1;

  // Make sure that the array is not empty
  FACEMC_ASSERT_ALWAYS( (data_point_1 != end) );

  // Make sure that the array has more than one entry
  FACEMC_ASSERT_ALWAYS( (data_point_2 != end) );

  // Create the discrete CDF
  while( data_point_2 != end )
  {
    data_point_2->second += data_point_1->second;
    
    ++data_point_1;
    ++data_point_2;
  }

  // Normalize the CDF
  data_point_1 = data.begin();
  while( data_point_1 != end )
    data_point_1->second /= data.back().second;
}

//! Create a discrete CDF in place (third tuple location) from an array of 
// data.
template<typename T,template<typename> class Array>
void EPDLDataProcessor::createDiscreteCDFAtThirdTupleLoc( Array<T> &data )
{
  typename Array<T>::iterator data_point_1, data_point_2;
  typename Array<T>::iterator end = data.end();

  data_point_1 = data.begin();
  data_point_2 = data_point_1 + 1;

  // Make sure that the array is not empty
  FACEMC_ASSERT_ALWAYS( (data_point_1 != end) );

  // Make sure that the array has more than one entry
  FACEMC_ASSERT_ALWAYS( (data_point_2 != end) );

  // Create the discrete CDF
  while( data_point_2 != end )
  {
    data_point_2->third += data_point_1->third;
    
    ++data_point_1;
    ++data_point_2;
  }

  // Normalize the CDF
  data_point_1 = data.begin();
  while( data_point_1 != end )
    data_point_1->third /= data.back().third;
}

//! Calculate the slope between each pair of data points.
template<typename T, template<typename> class Array>
void EPDL97DataProcessor::calculateSlopesAndAddToThirdTupleLoc( Array<T> &data  )
{
  typename Array<T>::iterator data_point_1, data_point_2;
  typename Array<T>::iterator end = data.end();

  data_point_1 = data.begin();
  data_point_2 = data_point_1 + 1;

  // Make sure that the array is not empty
  FACEMC_ASSERT_ALWAYS( (data_point_1 != end) );

  // Make sure that the array has more than one entry
  FACEMC_ASSERT_ALWAYS( (data_point_2 != end) );

  while( data_point_2 != end )
  {
    data_point_1->third = (data_point_2->second - data_point_1->second)/
      (data_point_2->first - data_point_1->first);
    data_point_2->third = 0.0;

    ++data_point_1;
    ++data_point_2;
  }
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
