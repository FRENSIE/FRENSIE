//---------------------------------------------------------------------------//
// \file   DataProcessor_def.hpp
// \author Alex Robinson
// \brief  Data Processor base class template definitions
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <cmath>
#include <limits>
#include <iterator>

// FACEMC Includes
#include "Tuple.hpp"
#include "TupleMemberSwapPolicy.hpp"

namespace FACEMC{

//! Calculate the slope between each pair of data points and store at the
// desired tuple member.
template<TupleMember member, 
	 typename T, 
	 template<typename> class Array>
void DataProcessor::calculateSlopesAtTupleMember( Array<T> &data  )
{
  // Make sure that the array has more than one element
  testPrecondition( (data.size() > 1) );
  
  typename Array<T>::iterator data_point_1, data_point_2;
  typename Array<T>::iterator end = data.end();

  data_point_1 = data.begin();
  data_point_2 = data_point_1 + 1;

  while( data_point_2 != end )
  {
    data_point_1->fourth = (data_point_2->second - data_point_1->second)/
      (data_point_2->first - data_point_1->first);
    data_point_2->third = 0.0;

    ++data_point_1;
    ++data_point_2;
  }
}

//! Create a cdf from an array of data using a taylor series expansion to O(2)
template<TupleMember member, 
	 typename T, 
	 template<typename> class Array>
void DataProcessor::createContinuousCDFAtTupleMember( Array<T> &data )
{
  // Make sure that the array has more than one element
  testPrecondition( (data.size() > 1) );
  
  typename Array<T>::iterator data_point_1, data_point_2;
  typename Array<T>::iterator end = data.end();

  data_point_1 = data.begin();
  data_point_2 = data.begin() + 1;

  // Initialize the CDF
  data_point_1->third = 0.0;
  
  // Calculate the CDF
  // CDF(x) = CDF(x1)+PDF(x1)*(x-x1)+0.5*(PDF(x)-PDF(x1))/(x2-x1)*(x-x1)^2
  while( data_point_2 != end )
  {
    data_point_2->third = data_point_1->third;
    data_point_2->third += data_point_1->second*
      (data_point_2->first - data_point_1->first) +
      0.5*(data_point_2->second - data_point_1->second)*
      (data_point_2->first - data_point_1->first);

    ++data_point_1;
    ++data_point_2;
  }

  // Normalize the CDF and PDF
  data_point_1 = data.begin();
  while( data_point_1 != end )
  {
    data_point_1->third /= data.back().third;
    data_point_1->second /= data.back().third;
    ++data_point_1;
  }
}

//! Create a discrete CDF in place from an array of data.
template<typename T,template<typename> class Array>
void DataProcessor::createDiscreteCDFInPlaceAtTupleMember( Array<T> &data )
{
  // Make sure that the array has more than one element
  testPrecondition( (data.size() > 1) );
  
  typename Array<T>::iterator data_point_1, data_point_2;
  typename Array<T>::iterator end = data.end();

  data_point_1 = data.begin();
  data_point_2 = data.begin() + 1;

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
  {
    data_point_1->second /= data.back().second;
    ++data_point_1;
  }
}

//! Swap the data in the desired tuple members.
template<TupleMember member1, 
	 TupleMember member2,
	 typename T,
	 template<typename> class Array>
void swapDataAtTupleMembers( Array<T> & data )
{
  // Make sure that the array is valid
  testPrecondition( (data.size() > 0) );
  
  typename Array<T>::iterator data_point, end;
  data_point = data.begin();
  end = data.end();

  while( data_point != end )
  {
    TupleMemberSwapPolicy<std::iterator_traits<typename Array<T>::iterator>::value_type,member1,member2>::swap( *data_point );
    
    ++data_point;
  }
}

//---------------------------------------------------------------------------//
// LogLogDataProcessingPolicy definitions
//---------------------------------------------------------------------------//

//! Process Independent Variable
inline double DataProcessor::LogLogDataProcessingPolicy::processIndependentVar( const double indep_var )
{
  if( indep_var > 0.0 )
    return log( indep_var );
  else
    return log( std::numeric_limits<double>::min() );
}

//! Process Dependent Variable
inline double DataProcessor::LogLogDataProcessingPolicy::processDependentVar( const double dep_var )
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
inline double DataProcessor::LinearLogDataProcessingPolicy::processIndependentVar( const double indep_var )
{
  return indep_var;
}

//! Process Dependent Variable
inline double DataProcessor::LinearLogDataProcessingPolicy::processDependentVar( const double dep_var )
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
inline double DataProcessor::LogLinearDataProcessingPolicy::processIndependentVar( const double indep_var )
{
  if( indep_var > 0.0 )
    return log( indep_var );
  else
    return log( std::numeric_limits<double>::min() );
}

//! Process Dependent Variable
inline double DataProcessor::LogLinearDataProcessingPolicy::processDependentVar( const double dep_var )
{
  return dep_var;
}

//---------------------------------------------------------------------------//
// LinearLinearDataProcessingPolicy definitions
//---------------------------------------------------------------------------//

//! Process Independent Variable
 inline double DataProcessor::LinearLinearDataProcessingPolicy::processIndependentVar( const double indep_var )
{
  return indep_var;
}

//! Process Dependent Variable
inline double DataProcessor::LinearLinearDataProcessingPolicy::processDependentVar( const double dep_var )
{
  return dep_var;
}
