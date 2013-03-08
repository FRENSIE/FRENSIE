//---------------------------------------------------------------------------//
// \file   DataProcessor_def.hpp
// \author Alex Robinson
// \brief  Data Processor base class template definitions
//---------------------------------------------------------------------------//

#ifndef DATA_PROCESSOR_DEF_HPP
#define DATA_PROCESSOR_DEF_HPP

// Std Lib Includes
#include <cmath>
#include <limits>
#include <iterator>

// FACEMC Includes
#include "Tuple.hpp"
#include "TupleMemberSwapPolicy.hpp"
#include "TupleGetSetMemberPolicy.hpp"
#include "ContractException.hpp"

namespace FACEMC{

//! Process the data points
template<typename DataProcessingPolicy,
	   TupleMember indepMember,
	   TupleMember depMember,
	   typename Tuple,
	   template<typename> class Array>
void DataProcessor::processData( Array<Tuple> &data )
{
  // Make sure that the array is valid
  testPrecondition( data.size() > 0 );

  typename Array<Tuple>::iterator data_point = data.begin();
  typename Array<Tuple>::iterator end = data.end();

  typedef TupleGetSetMemberPolicy<Tuple,indepMember> indepTGSMP;
  typedef TupleGetSetMemberPolicy<Tuple,depMember> depTGSMP;

  typename indepTGSMP::tupleMemberType indep_value;
  typename depTGSMP::tupleMemberType dep_value;

  while( data_point != end )
  {
    indep_value = DataProcessingPolicy::processIndependentVar( indepTGSMP::get( *data_point ) );
    dep_value = DataProcessingPolicy::processDependentVar( depTGSMP::get( *data_point ) );

    indepTGSMP::set( *data_point, indep_value );
    depTGSMP::set( *data_point, dep_value );

    ++data_point;
  }
}

//! Calculate the slope between each pair of data points and store at the
// desired tuple member.
template<TupleMember indepMember, 
	 TupleMember depMember,
	 TupleMember slopeMember,
	 typename Tuple, 
	 template<typename> class Array>
void DataProcessor::calculateSlopes( Array<Tuple> &data  )
{
  // Make sure that the array has more than one element
  testPrecondition( (data.size() > 1) );
  
  typename Array<Tuple>::iterator data_point_1, data_point_2;
  typename Array<Tuple>::iterator end = data.end();

  data_point_1 = data.begin();
  data_point_2 = data_point_1 + 1;

  typedef TupleGetSetMemberPolicy<Tuple,indepMember> indepTGSMP;
  typedef TupleGetSetMemberPolicy<Tuple,depMember> depTGSMP;
  typedef TupleGetSetMemberPolicy<Tuple,slopeMember> slopeTGSMP;
  
  typename slopeTGSMP::tupleMemberType slope;
  
  while( data_point_2 != end )
  {
    slope = (depTGSMP::get( *data_point_2 ) - depTGSMP::get( *data_point_1 ))/
      (indepTGSMP::get( *data_point_2 ) - indepTGSMP::get( *data_point_1 ));
    
    slopeTGSMP::set( *data_point_1, slope );
    slopeTGSMP::set( *data_point_2, 0 );

    ++data_point_1;
    ++data_point_2;
  }
}

//! Create a cdf from an array of data using a taylor series expansion to O(2)
template<TupleMember indepMember,
	 TupleMember pdfMember,
	 TupleMember cdfMember,
	 typename Tuple, 
	 template<typename> class Array>
void DataProcessor::calculateContinuousCDF( Array<Tuple> &data )
{
  // Make sure that the array has more than one element
  testPrecondition( (data.size() > 1) );
  
  typename Array<Tuple>::iterator data_point_1, data_point_2;
  typename Array<Tuple>::iterator end = data.end();

  data_point_1 = data.begin();
  data_point_2 = data.begin() + 1;

  typedef TupleGetSetMemberPolicy<Tuple,indepMember> indepTGSMP;
  typedef TupleGetSetMemberPolicy<Tuple,pdfMember> pdfTGSMP;
  typedef TupleGetSetMemberPolicy<Tuple,cdfMember> cdfTGSMP;

  typename cdfTGSMP::tupleMemberType cdf_value;

  // Initialize the CDF
  cdfTGSMP::set( *data_point_1, 0 );
  
  // Calculate the CDF
  // CDF(x) = CDF(x1)+PDF(x1)*(x-x1)+0.5*(PDF(x)-PDF(x1))/(x2-x1)*(x-x1)^2
  while( data_point_2 != end )
  {
    cdf_value = cdfTGSMP::get( *data_point_1 ) +
      pdfTGSMP::get( *data_point_1 )*
      (indepTGSMP::get( *data_point_2 ) - indepTGSMP::get( *data_point_1 )) +
      0.5*(pdfTGSMP::get( *data_point_2 ) - pdfTGSMP::get( *data_point_1 ))*
      (indepTGSMP::get( *data_point_2) - indepTGSMP::get( *data_point_1 ));
    
    cdfTGSMP::set( *data_point_2, cdf_value );
    
    ++data_point_1;
    ++data_point_2;
  }

  // Normalize the CDF and PDF
  typename cdfTGSMP::tupleMemberType cdf_max, cdf_norm_value;
  cdf_max = cdfTGSMP::get( data.back() );
  typename pdfTGSMP::tupleMemberType pdf_norm_value;
  data_point_1 = data.begin();
  
  while( data_point_1 != end )
  {
    cdf_norm_value = cdfTGSMP::get( *data_point_1 )/cdf_max;
    cdfTGSMP::set( *data_point_1, cdf_norm_value );

    pdf_norm_value = pdfTGSMP::get( *data_point_1 )/cdf_max;
    pdfTGSMP::set( *data_point_1, pdf_norm_value );
    
    ++data_point_1;
  }
}

//! Create a discrete CDF from an array of data.
template<TupleMember pdfMember,
	 TupleMember cdfMember,
	 typename Tuple,
	 template<typename> class Array>
void DataProcessor::calculateDiscreteCDF( Array<Tuple> &data )
{
  // Make sure that the array has more than one element
  testPrecondition( (data.size() > 1) );
  
  typename Array<Tuple>::iterator data_point;
  typename Array<Tuple>::iterator end = data.end();

  data_point = data.begin();

  typedef TupleGetSetMemberPolicy<Tuple,pdfMember> pdfTGSMP;
  typedef TupleGetSetMemberPolicy<Tuple,cdfMember> cdfTGSMP;

  typename cdfTGSMP::tupleMemberType cdf_value = 0;

  // Create the discrete CDF
  while( data_point != end )
  {
    cdf_value += pdfTGSMP::get( *data_point );
    cdfTGSMP::set( *data_point, cdf_value );
    
    ++data_point;
  }

  // Normalize the CDF
  data_point = data.begin();
  while( data_point != end )
  {
    cdf_value = cdfTGSMP::get( *data_point )/cdfTGSMP::get( data.back() );
    cdfTGSMP::set( *data_point, cdf_value );
    
    ++data_point;
  }
}

//! Swap the data in the desired tuple members.
template<TupleMember member1, 
	 TupleMember member2,
	 typename Tuple,
	 template<typename> class Array>
void DataProcessor::swapTupleMemberData( Array<Tuple> & data )
{
  // Make sure that the array is valid
  testPrecondition( (data.size() > 0) );
  
  typename Array<Tuple>::iterator data_point, end;
  data_point = data.begin();
  end = data.end();

  while( data_point != end )
  {
    TupleMemberSwapPolicy<Tuple,member1,member2>::swap( *data_point );
    
    ++data_point;
  }
}

//---------------------------------------------------------------------------//
// LogLogDataProcessingPolicy definitions
//---------------------------------------------------------------------------//

//! Process Independent Variable
template<typename T>
inline T DataProcessor::LogLogDataProcessingPolicy::processIndependentVar( const T indep_var )
{
  if( indep_var > 0 )
    return static_cast<T>( log( static_cast<double>(indep_var) ) );
  else
    return 0;
}

//! Process Dependent Variable
template<typename T>
inline T DataProcessor::LogLogDataProcessingPolicy::processDependentVar( const T dep_var )
{
  if( dep_var > 0 )
    return static_cast<T>( log( static_cast<double>(dep_var) ) );
  else
    return 0;
}

//---------------------------------------------------------------------------//
// SquareSquareDataProcessingPolicy definitions
//---------------------------------------------------------------------------//

//! Process Independent Variable
template<typename T>
inline T DataProcessor::SquareSquareDataProcessingPolicy::processIndependentVar( const T indep_var )
{
  return indep_var*indep_var;
}

//! Process Dependent Variable
template<typename T>
inline T DataProcessor::SquareSquareDataProcessingPolicy::processDependentVar( const T dep_var )
{
  return dep_var*dep_var;
}

} // end FACEMC namespace

#endif // end DATA_PROCESSOR_DEF_HPP

//---------------------------------------------------------------------------//
// end DataProcessor_def.hpp
//---------------------------------------------------------------------------//

