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
// of Pairs of floating point data types
#define TEST_COMPARE_FLOATING_PAIR_ARRAYS( a1, a2, tol ) \
  {									\
    const bool result =							\
      Teuchos::compareFloatingPairArrays(a1,#a1,a2,#a2,tol,out);	\
    if( !result ) success = false;					\
  }

// Define a new Macro for the Teuchos Unit Test Harness for comparing arrays
// of Triplets of floating point data types
#define TEST_COMPARE_FLOATING_TRIP_ARRAYS( a1, a2, tol ) \
  {									\
    const bool result =							\
      Teuchos::compareFloatingTripArrays(a1,#a1,a2,#a2,tol,out);	\
    if( !result ) success = false;					\
  }

// Define a new Macro for the Teuchos Unit Test Harness for comparing arrays
// of Quadruplets of floating point data types
#define TEST_COMPARE_FLOATING_QUAD_ARRAYS( a1, a2, tol ) \
  {									\
    const bool result =							\
      Teuchos::compareFloatingQuadArrays(a1,#a1,a2,#a2,tol,out);	\
    if( !result ) success = false;					\
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

// Function for comparing arrays of pairs with floating point values
// this function is based off of the compareFloatingArrays function in Teuchos
template<typename T,
	 template<typename> class Array1,
	 template<typename> class Array2>
bool compareFloatingPairArrays( const Array1<T> &a1,
				const std::string &a1_name,
				const Array2<T> &a2,
				const std::string &a2_name,
				const double &tol,
				Teuchos::FancyOStream &out )
{
  bool success = true;
  bool local_success = true;

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
    local_success = compareFirstTupleElements( a1[i], a1_name, 
					       a2[i], a2_name,
					       i,
					       tol,
					       out );
    if( !local_success )
      success = false;

    // Compare the second element
    local_success = compareSecondTupleElements( a1[i], a1_name,
						a2[i], a2_name,
						i,
						tol,
						out );
    if( !local_success )
      success = false;
  }
  
  if( success ) 
    out << "passed\n";

  return success;
}

// Function for comparing arrays of tiplets with floating point values
// this function is based off of the compareFloatingArrays function in Teuchos
template<typename T,
	 template<typename> class Array1,
	 template<typename> class Array2>
bool compareFloatingTripArrays( const Array1<T> &a1,
				const std::string &a1_name,
				const Array2<T> &a2,
				const std::string &a2_name,
				const double &tol,
				Teuchos::FancyOStream &out )
{
  bool success = true;
  bool local_success = true;

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
    local_success = compareFirstTupleElements( a1[i], a1_name, 
					       a2[i], a2_name,
					       i,
					       tol,
					       out );
    if( !local_success )
      success = false;
    
    // Compare the second element
    local_success = compareSecondTupleElements( a1[i], a1_name,
						a2[i], a2_name,
						i,
						tol,
						out );
    if( !local_success )
      success = false;
    
    // Compare the third element
    local_success = compareThirdTupleElements( a1[i], a1_name,
					       a2[i], a2_name,
					       i, 
					       tol,
					       out );
    if( !local_success )
      success = false;
  }
  
  if( success ) 
    out << "passed\n";

  return success;
}

// Function for comparing arrays of quadruplets with floating point values
// this function is based off of the compareFloatingArrays function in Teuchos
template<typename T,
	 template<typename> class Array1,
	 template<typename> class Array2>
bool compareFloatingQuadArrays( const Array1<T> &a1,
				const std::string &a1_name,
				const Array2<T> &a2,
				const std::string &a2_name,
				const double &tol,
				Teuchos::FancyOStream &out )
{
  bool success = true;
  bool local_success = true;

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
    local_success = compareFirstTupleElements( a1[i], a1_name, 
					       a2[i], a2_name,
					       i,
					       tol,
					       out );
    if( !local_success )
      success = false;
    
    // Compare the second element
    local_success = compareSecondTupleElements( a1[i], a1_name,
						a2[i], a2_name,
						i,
						tol,
						out );
    if( !local_success )
      success = false;
    
    // Compare the third element
    local_success = compareThirdTupleElements( a1[i], a1_name,
					       a2[i], a2_name,
					       i, 
					       tol,
					       out );
    if( !local_success )
      success = false;
     
    // Compare the fourth element
    local_success = compareFourthTupleElements( a1[i], a1_name,
						a2[i], a2_name,
						i,
						tol,
						out );
    if( !local_success )
      success = false;
  }
  
  if( success ) 
    out << "passed\n";
  
  return success;
}

// function for comparing first tuple element 
template<typename T>
bool compareFirstTupleElements( const T &tuple1,
				const std::string &a1_name,
				const T &tuple2,
				const std::string &a2_name,
				const int i,
				const double tol,
				Teuchos::FancyOStream &out)
{
  bool success = true;
  
  typedef ScalarTraits<typename T::firstType> ST;
  if( ST::isOrdinal )
  {
    if( tuple1.first != tuple2.first )
      {
	out << "\nError, " << a1_name << "[" << i << "].first = "
	    << tuple1.first << " == " << a2_name << "[" << i 
	    << "].first = " << tuple2.first << ": failed!\n";
	return false;
      }
  }
  else
  {
    const typename ST::magnitudeType err = ST::magnitude( tuple1.first - 
							  tuple2.first )/
      std::max( ST::magnitude( tuple1.first ), 
		ST::magnitude( tuple2.first ) );
    
    if( err > tol )
    {
      out << "\nError, relErr(" << a1_name << "[" << i << "].first,"
	  << a2_name << "[" << i << "].first) = relErr("
	  << tuple1.first << ","  << tuple2.first << ") = "
	  << err << " <= tol = " << tol << ": failed!\n";
      return false;
    }
  }
 
  return success;
}

// function for comparing second tuple element 
template<typename T>
bool compareSecondTupleElements( const T &tuple1,
				 const std::string &a1_name,
				 const T &tuple2,
				 const std::string &a2_name,
				 const int i,
				 const double tol,
				 Teuchos::FancyOStream &out)
{
  bool success = true;

  typedef ScalarTraits<typename T::secondType> ST;
  if( ST::isOrdinal )
  {
    if( tuple1.second != tuple2.second )
    {
      out << "\nError, " << a1_name << "[" << i << "].second = "
	  << tuple1.second << " == " << a2_name << "[" << i 
	  << "].second = " << tuple2.second << ": failed!\n";
      return false;
    }
  }
  else
  {
    const typename ST::magnitudeType err = ST::magnitude( tuple1.second - 
							  tuple2.second )/
      std::max( ST::magnitude( tuple1.second ), 
		ST::magnitude( tuple2.second ) );
    
    if( err > tol )
    {
      out << "\nError, relErr(" << a1_name << "[" << i << "].second,"
	  << a2_name << "[" << i << "].second) = relErr("
	  << tuple1.second << "," << tuple2.second << ") = "
	  << err << " <= tol = " << tol << ": failed!\n";
      return false;
    }
  }
  
  return success;
}

// function for comparing third tuple element 
template<typename T>
bool compareThirdTupleElements( const T &tuple1,
				const std::string &a1_name,
				const T &tuple2,
				const std::string &a2_name,
				const int i,
				const double tol,
				Teuchos::FancyOStream &out)
{
  
  bool success = true;

  typedef ScalarTraits<typename T::thirdType> ST;
  if( ST::isOrdinal )
  {
    if( tuple1.third != tuple2.third )
      {
	out << "\nError, " << a1_name << "[" << i << "].third = "
	    << tuple1.third << " == " << a2_name << "[" << i 
	    << "].third = " << tuple2.third << ": failed!\n";
	return false;
      }
  }
  else
  {
    const typename ST::magnitudeType err = ST::magnitude( tuple1.third - 
							  tuple2.third )/
      std::max( ST::magnitude( tuple1.third ), 
		ST::magnitude( tuple2.third ) );
    
    if( err > tol )
    {
      out << "\nError, relErr(" << a1_name << "[" << i << "].third,"
	  << a2_name << "[" << i << "].third) = relErr("
	  << tuple1.third << ","  << tuple2.third << ") = "
	  << err << " <= tol = " << tol << ": failed!\n";
      return false;
    }
  }

  return success;
}

// function for comparing fourth tuple element 
template<typename T>
bool compareFourthTupleElements( const T &tuple1,
				 const std::string &a1_name,
				 const T &tuple2,
				 const std::string &a2_name,
				 const int i,
				 const double tol,
				 Teuchos::FancyOStream &out)
{
  
  bool success = true;

  typedef ScalarTraits<typename T::fourthType> ST;
  if( ST::isOrdinal )
  {
    if( tuple1.fourth != tuple2.fourth )
    {
      out << "\nError, " << a1_name << "[" << i << "].fourth = "
	  << tuple1.fourth << " == " << a2_name << "[" << i 
	  << "].fourth = " << tuple2.fourth << ": failed!\n";
      return false;
    }
  }
  else
  {
    const typename ST::magnitudeType err = ST::magnitude( tuple1.fourth - 
							  tuple2.fourth )/
      std::max( ST::magnitude( tuple1.fourth ), 
		ST::magnitude( tuple2.fourth ) );
    
    if( err > tol )
    {
      out << "\nError, relErr(" << a1_name << "[" << i << "].fourth,"
	  << a2_name << "[" << i << "].fourth) = relErr("
	  << tuple1.fourth << "," << tuple2.fourth << ") = "
	  << err << " <= tol = " << tol << ": failed!\n";
      return false;
    }
  }
  
  return success;
}

} // end Teuchos namespace

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

} // end FACEMC namespace

#endif // end TESTING_HELPER_FUNCTIONS_HPP

//---------------------------------------------------------------------------//
// end TestingHelperFunctions.hpp
//---------------------------------------------------------------------------//
