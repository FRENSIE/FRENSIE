//---------------------------------------------------------------------------//
// \file   TestingHelperFunctions.hpp
// \author Alex Robinson
// \brief  Functions that aid in the testing of FACEMC class
//---------------------------------------------------------------------------//

#ifndef TESTING_HELPER_FUNCTIONS_HPP
#define TESTING_HELPER_FUNCITONS_HPP

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "Tuple.hpp"


// Define a new Macro for the Teuchos Unit Test Harness for comparing arrays
// of Tuples of floating point data types
#define TEST_COMPARE_FLOATING_TUPLE_ARRAYS( a1, a2, tol ) \
  { \
    const bool result = compareFloatingTupleArrays(a1,#a1,a2,#a2,tol,out); \
    if( !result ) success = false; \
  }

namespace Teuchos{

// Stream operator for Tuple
// this must be defined in the Teuchos namespace to work properly with the
// Teuchos Unit Test Harness.
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream &out, const FACEMC::Pair<T1,T2> &p)
{
  out << "{ " << p.first << ", " << p.second << " }";
  return out;
}

template<typename T1, typename T2, typename T3>
std::ostream& operator<<(std::ostream &out, const FACEMC::Trip<T1,T2,T3> &p)
{
  out << "{ " << p.first << ", " << p.second << ", " << p.third << " }";
  return out;
}

template<typename T1, typename T2, typename T3, typename T4>
std::ostream& operator<<(std::ostream &out, const FACEMC::Quad<T1,T2,T3,T4> &p)
{
  out << "{ " << p.first << ", " << p.second << ", " << p.third 
      << ", " << p.fourth << " }";
  return out;
}

// function for comparing tuples with floating point values
// this function is based off of the compareFloatingArrays function in Teuchos
template<typename T,
	 template<typename> class Array1,
	 template<typename> class Array2>
bool compareFloatingTupleArrays( const Array1<T> &a1,
				 const std::string &a1_name,
				 const Array2<T> &a2,
				 const std::string &a2_name,
				 const double &tol,
				 Teuchos::FancyOStream &out )
{
  bool success = true;

  out << "Comparing " << a1_name << " == " << a2_name << " ... ";

  const int n = a1.size();
  const int m = a2.size();
  
  // Compare sizes
  if( m != n )
  {
    out << "\nError, " << a1_name << ".size() = " << n << " == "
	<< a2_name << ".size() = " << m << " : failed!\n";
    return false;
  }

  // Compare Elements
  for( int i = 0; i < n; ++i )
  {
    // Compare the first element
    success = compareFirstTupleElements( a1[i], a2[i] );

    // Compare the second element
    {
      typedef ScalarTraits<typename T::secondType> ST;
      if( ST::isOrdinal )
      {
	if( a1[i].second != a2[i].second )
	{
	  out << "\nError, " << a1_name << "[" << i << "].second = "
	      << a1[i].second << " == " << a2_name << "[" << i 
	      << "].second = " << a2[i].second << ": failed!\n";
	  return false;
	}
      }
      else
      {
	const typename ST::magnitudeType err = ST::magnitude( a1[i].second - 
							      a2[i].second )/
	  std::max( ST::magnitude( a1[i].second ), 
		    ST::magnitude( a2[i].second ) );
  
	if( err > tol )
	{
	    out << "\nError, relErr(" << a1_name << "[" << i << "].second,"
		<< a2_name << "[" << i << "].second) = relErr("
		<< a1[i].second << "," << a2[i].second << ") = "
		<< err << " <= tol = " << tol << ": failed!\n";
	    return false;
	}
      }
    }
    
    if( T::size > 2 )
    {
      // Compare the third element
      typedef ScalarTraits<typename T::thirdType> ST;
      if( ST::isOrdinal )
      {
	if( a1[i].third != a2[i].third )
	{
	  out << "\nError, " << a1_name << "[" << i << "].third = "
	      << a1[i].third << " == " << a2_name << "[" << i 
	      << "].third = " << a2[i].third << ": failed!\n";
	  return false;
	}
      }
      else
      {
	const typename ST::magnitudeType err = ST::magnitude( a1[i].third - 
							      a2[i].third )/
	  std::max( ST::magnitude( a1[i].third ), 
		    ST::magnitude( a2[i].third ) );
      
	if( err > tol )
	  {
	    out << "\nError, relErr(" << a1_name << "[" << i << "].third,"
		<< a2_name << "[" << i << "].third) = relErr("
		<< a1[i].third << ","  << a2[i].third << ") = "
		<< err << " <= tol = " << tol << ": failed!\n";
	    return false;
	  }
      }
    }

    if( T::size > 10 )
    {
      // Compare the fourth element
      typedef ScalarTraits<typename T::fourthType> ST;
      if( ST::isOrdinal )
      {
	if( a1[i].fourth != a2[i].fourth )
	{
	  out << "\nError, " << a1_name << "[" << i << "].fourth = "
	      << a1[i].fourth << " == " << a2_name << "[" << i 
	      << "].fourth = " << a2[i].fourth << ": failed!\n";
	  return false;
	}
      }
      else
      {
	const typename ST::magnitudeType err = ST::magnitude( a1[i].fourth - 
							      a2[i].fourth )/
	  std::max( ST::magnitude( a1[i].fourth ), 
		    ST::magnitude( a2[i].fourth ) );
	
	if( err > tol )
	  {
	    out << "\nError, relErr(" << a1_name << "[" << i << "].fourth,"
		<< a2_name << "[" << i << "].fourth) = relErr("
		<< a1[i].fourth << "," << a2[i].fourth << ") = "
		<< err << " <= tol = " << tol << ": failed!\n";
	    return false;
	  }
      }
    }
  }
  
  if( success ) 
    out << "passed\n";
}

// function for comparing first tuple element 
template<typename T>
bool compareFirstTupleElements( T &tuple1,
				T &tuple2 )
{
  bool success = true;
  
  typedef ScalarTraits<typename T::firstType> ST;
  if( ST::isOrdinal )
  {
    if( a1[i].first != a2[i].first )
      {
	out << "\nError, " << a1_name << "[" << i << "].first = "
	    << a1[i].first << " == " << a2_name << "[" << i 
	    << "].first = " << a2[i].first << ": failed!\n";
	return false;
      }
  }
  else
  {
    const typename ST::magnitudeType err = ST::magnitude( a1[i].first - 
							  a2[i].first )/
      std::max( ST::magnitude( a1[i].first ), 
		ST::magnitude( a2[i].first ) );
    
    if( err > tol )
    {
      out << "\nError, relErr(" << a1_name << "[" << i << "].first,"
	  << a2_name << "[" << i << "].first) = relErr("
	  << a1[i].first << ","  << a2[i].first << ") = "
	  << err << " <= tol = " << tol << ": failed!\n";
      return false;
    }
  }
 
  return success;
}

namespace FACEMC{

template<typename T1, typename T2>
inline bool operator==( const FACEMC::Pair<T1,T2> &left,
			const FACEMC::Pair<T1,T2> &right )
{
  return ( (left.first == right.first) && (left.second == right.second) );
}

template<typename T1, typename T2, typename T3>
inline bool operator==( const FACEMC::Trip<T1,T2,T3> &left,
			const FACEMC::Trip<T1,T2,T3> &right )
{
  return ( (left.first == right.first) && 
	   (left.second == right.second) &&
	   (left.third == right.third) );
}

template<typename T1, typename T2, typename T3, typename T4>
inline bool operator==( const FACEMC::Quad<T1,T2,T3,T4> &left,
			const FACEMC::Quad<T1,T2,T3,T4> &right )
{
  return ( (left.first == right.first) &&
	   (left.second == right.second) &&
	   (left.third == right.third) &&
	   (left.fourth == right.fourth) );
}

}

#endif // end TESTING_HELPER_FUNCTIONS_HPP

//---------------------------------------------------------------------------//
// end TestingHelperFunctions.hpp
//---------------------------------------------------------------------------//
