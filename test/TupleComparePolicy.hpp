//---------------------------------------------------------------------------//
// \file   TupleComparePolicy.hpp
// \author Alex Robinson
// \brief  Tuple compare policy specializations
//---------------------------------------------------------------------------//

#ifndef TUPLE_COMPARE_POLICY_HPP
#define TUPLE_COMPARE_POLICY_HPP

// Std Lib Includes
#include <sstream>
#include <string>

// Trilinos Includes
#include <Teuchos_FancyOStream.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "Tuple.hpp"
#include "TupleComparePolicyDecl.hpp"

namespace FACEMC{

//---------------------------------------------------------------------------//
// TupleComparePolicy Helper Functions.
//---------------------------------------------------------------------------//

// Compare the first tuple members
template<typename T>
bool compareFirstTupleMembers( const T &first_value,
			       const std::string &first_name,
			       const T &second_value,
			       const std::string &second_name,
			       Teuchos::FancyOStream &out,
			       const int index,
			       const double tol )
{
  bool success = true;
  
  std::stringstream first_tuple_member_name;
  std::stringstream second_tuple_member_name;
  // Array Element Compare
  if( index >= 0 )
  {
    first_tuple_member_name << first_name << "[" << index << "].first";
    second_tuple_member_name << second_name << "[" << index << "].first";
  }
  // Single Tuple Compare
  else
  {
    first_tuple_member_name << first_name << ".first";
    second_tuple_member_name << second_name << ".first";
  }
  
  success = TupleComparePolicy<T>::compare( first_value,
					    first_tuple_member_name.str(),
					    second_value,
					    second_tuple_member_name.str(),
					    out,
					    0,
					    tol );
  return success;
}

// Compare the second tuple members
template<typename T>
bool compareSecondTupleMembers( const T &first_value,
				const std::string &first_name,
				const T &second_value,
				const std::string &second_name,
				Teuchos::FancyOStream &out,
				const int index,
				const double tol )
{
  bool success = true;
  
  std::stringstream first_tuple_member_name;
  std::stringstream second_tuple_member_name;
  // Array Element Compare
  if( index >= 0 )
  {
    first_tuple_member_name << first_name << "[" << index << "].second";
    second_tuple_member_name << second_name << "[" << index << "].second";
  }
  // Single Tuple Compare
  else
  {
    first_tuple_member_name << first_name << ".second";
    second_tuple_member_name << second_name << ".second";
  }
  
  success = TupleComparePolicy<T>::compare( first_value,
					    first_tuple_member_name.str(),
					    second_value,
					    second_tuple_member_name.str(),
					    out,
					    0,
					    tol );
  return success;
}

// Compare the third tuple members
template<typename T>
bool compareThirdTupleMembers( const T &first_value,
				const std::string &first_name,
				const T &second_value,
				const std::string &second_name,
				Teuchos::FancyOStream &out,
				const int index,
				const double tol )
{
  bool success = true;
  
  std::stringstream first_tuple_member_name;
  std::stringstream second_tuple_member_name;
  // Array Element Compare
  if( index >= 0 )
  {
    first_tuple_member_name << first_name << "[" << index << "].third";
    second_tuple_member_name << second_name << "[" << index << "].third";
  }
  // Single Tuple Compare
  else
  {
    first_tuple_member_name << first_name << ".third";
    second_tuple_member_name << second_name << ".third";
  }
  
  success = TupleComparePolicy<T>::compare( first_value,
					    first_tuple_member_name.str(),
					    second_value,
					    second_tuple_member_name.str(),
					    out,
					    0,
					    tol );
  return success;
}

// Compare the fourth tuple members
template<typename T>
bool compareFourthTupleMembers( const T &first_value,
				const std::string &first_name,
				const T &second_value,
				const std::string &second_name,
				Teuchos::FancyOStream &out,
				const int index,
				const double tol )
{
  bool success = true;
  
  std::stringstream first_tuple_member_name;
  std::stringstream second_tuple_member_name;
  // Array Element Compare
  if( index >= 0 )
  {
    first_tuple_member_name << first_name << "[" << index << "].fourth";
    second_tuple_member_name << second_name << "[" << index << "].fourth";
  }
  // Single Tuple Compare
  else
  {
    first_tuple_member_name << first_name << ".fourth";
    second_tuple_member_name << second_name << ".fourth";
  }
  
  success = TupleComparePolicy<T>::compare( first_value,
					    first_tuple_member_name.str(),
					    second_value,
					    second_tuple_member_name.str(),
					    out,
					    0,
					    tol );
  return success;
}

//---------------------------------------------------------------------------//
// TupleComparePolicy Specializations
//---------------------------------------------------------------------------//
template<>
struct TupleComparePolicy<unsigned int>
{
  static inline bool compare( const unsigned int first_unsigned,
			      const std::string &first_name,
			      const unsigned int second_unsigned,
			      const std::string &second_name,
			      Teuchos::FancyOStream &out,
			      const int index = -1,
			      const double tol = 0.0 )
  {
    bool success = true;
      
    if( first_unsigned != second_unsigned )
    {
      out << "\nError, " << first_name << " = " << first_unsigned
	  << " == " << second_name << " = " << second_unsigned 
	  << ": failed!\n";
      
      success = false;
    }
      
    return success;
  }
};

template<>
struct TupleComparePolicy<double>
{
  static inline bool compare( const double first_double,
			      const std::string &first_name,
			      const double second_double,
			      const std::string &second_name,
			      Teuchos::FancyOStream &out,
			      const int index = -1,
			      const double tol = 0.0 )
  {
    bool success = true;

    if( tol == 0.0 )
    {
      if( first_double != second_double )
      {
	out << "\nError, " << first_name << " = " << first_double
	    << " == " << second_name << " = " << second_double 
	    << ": failed!\n";
	
	success = false;
      }
    }
    else
    {
      typedef Teuchos::ScalarTraits<double> ST;
      ST::magnitudeType err = ST::magnitude( first_double - second_double )/
	std::max( ST::magnitude( first_double ),
		  ST::magnitude( second_double ) );
      
      if( err > tol )
      {
	out << "\nError, relErr(" << first_name << "," << second_name << ")"
	    << " = relErr(" << first_double << "," << second_double << ") = "
	    << err << " <= tol = " << tol << ": failed!\n";
	
	success = false;
      }
      
    }
    
    return success;
  }
};  
  
template<typename T, typename T2>
struct TupleComparePolicy<Pair<T,T2> >
{
  static inline bool compare( const Pair<T,T2> &first_tuple, 
			      const std::string &first_name,
			      const Pair<T,T2> &second_tuple, 
			      const std::string &second_name,
			      Teuchos::FancyOStream &out,
			      const int index = -1,
			      const double tol = 0.0 )
  {
    bool success = true;
    
    // Compare the first tuple members
    {
      bool local_success = true;
      local_success = compareFirstTupleMembers<T>( first_tuple.first,
						   first_name,
						   second_tuple.first,
						   second_name,
						   out,
						   index,
						   tol );
      if( !local_success )
	success = false;
    }

    // Compare the second tuple members
    {
      bool local_success = true;
      local_success = compareSecondTupleMembers<T2>( first_tuple.second,
						     first_name,
						     second_tuple.second,
						     second_name,
						     out,
						     index,
						     tol );
      if( !local_success )
	success = false;
    }

    return success;
  }
};

template<typename T, typename T2, typename T3>
struct TupleComparePolicy<Trip<T,T2,T3> >
{
  static inline bool compare( const Trip<T,T2,T3> &first_tuple, 
			      const std::string &first_name,
			      const Trip<T,T2,T3> &second_tuple, 
			      const std::string &second_name,
			      Teuchos::FancyOStream &out,
			      const int index = -1,
			      const double tol = 0.0 )
  {
    bool success = true;
    
    // Compare the first tuple members
    {
      bool local_success = true;
      local_success = compareFirstTupleMembers<T>( first_tuple.first,
						   first_name,
						   second_tuple.first,
						   second_name,
						   out,
						   index,
						   tol );
      if( !local_success )
	success = false;
    }

    // Compare the second tuple members
    {
      bool local_success = true;
      local_success = compareSecondTupleMembers<T2>( first_tuple.second,
						     first_name,
						     second_tuple.second,
						     second_name,
						     out,
						     index,
						     tol );
      if( !local_success )
	success = false;
    }
    
    // Compare the third tuple members
    {
      bool local_success = true;
      local_success = compareThirdTupleMembers<T3>( first_tuple.third,
						    first_name,
						    second_tuple.third,
						    second_name,
						    out,
						    index,
						    tol );
      if( !local_success )
	success = false;
    }

    return success;
  }
};

template<typename T, typename T2, typename T3, typename T4>
struct TupleComparePolicy<Quad<T,T2,T3,T4> >
{
  static inline bool compare( const Quad<T,T2,T3,T4> &first_tuple, 
			      const std::string &first_name,
			      const Quad<T,T2,T3,T4> &second_tuple, 
			      const std::string &second_name,
			      Teuchos::FancyOStream &out,
			      const int index = -1,
			      const double tol = 0.0 )
  {
    bool success = true;
    
    // Compare the first tuple members
    {
      bool local_success = true;
      local_success = compareFirstTupleMembers<T>( first_tuple.first,
						   first_name,
						   second_tuple.first,
						   second_name,
						   out,
						   index,
						   tol );
      if( !local_success )
	success = false;
    }

    // Compare the second tuple members
    {
      bool local_success = true;
      local_success = compareSecondTupleMembers<T2>( first_tuple.second,
						     first_name,
						     second_tuple.second,
						     second_name,
						     out,
						     index,
						     tol );
      if( !local_success )
	success = false;
    }
    
    // Compare the third tuple members
    {
      bool local_success = true;
      local_success = compareThirdTupleMembers<T3>( first_tuple.third,
						    first_name,
						    second_tuple.third,
						    second_name,
						    out,
						    index,
						    tol );
      if( !local_success )
	success = false;
    }

    // Compare the fourth tuple members
    {
      bool local_success = true;
      local_success = compareFourthTupleMembers<T4>( first_tuple.fourth,
						     first_name,
						     second_tuple.fourth,
						     second_name,
						     out,
						     index,
						     tol );
      if( !local_success )
	success = false;
    }

    return success;
  }
};
						    
} // end FACEMC namespace

#endif // end TUPLE_COMPARE_POLICY_HPP

//---------------------------------------------------------------------------//
// end TupleComparePolicy.hpp
//---------------------------------------------------------------------------//
