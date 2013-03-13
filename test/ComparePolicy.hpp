//---------------------------------------------------------------------------//
// \file   ComparePolicy.hpp
// \author Alex Robinson
// \brief  Compare policy specializations
//---------------------------------------------------------------------------//

#ifndef COMPARE_POLICY_HPP
#define COMPARE_POLICY_HPP

// Std Lib Includes
#include <string>

// Trilinos Includes
#include <Teuchos_FancyOStream.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "ComparePolicyDecl.hpp"
#include "Tuple.hpp"
#include "TupleComparePolicy.hpp"


namespace FACEMC{

template<>
struct ComparePolicy<unsigned int>
{
  static inline bool compare( const unsigned int &first_value,
			      const std::string &first_name,
			      const unsigned int &second_value,
			      const std::string &second_name,
			      Teuchos::FancyOStream &out,
			      const int index = -1,
			      const double tol = 0.0 )
  {
    bool success = true;
      
    if( first_value != second_value )
    {
      // Array Element Compare
      if( index >= 0 )
      {
	out << "\nError, " << first_name << "[" << index << "]" << " = "
	    << first_value << " == " << second_name << "[" << index << "]" 
	    << " = " << second_value << ": failed!\n";
      }
      // Single Compare
      else
      {
	out << first_name << " = " << first_value
	    << " == " << second_name << " = " << second_value 
	    << ": ";
      }
      
      success = false;
    }
      
    return success;
  }
};

template<>
struct ComparePolicy<double>
{
  static inline bool compare( const double &first_value,
			      const std::string &first_name,
			      const double &second_value,
			      const std::string &second_name,
			      Teuchos::FancyOStream &out,
			      const int index = -1,
			      const double tol = 0.0 )
  {
    bool success = true;
      
    if( tol == 0.0 )
    {
      if( first_value != second_value )
      {
	// Array Element Compare
	if( index >= 0 )
	{
	  out << "\nError, " << first_name << "[" << index << "]" << " = "
	      << first_value << " == " << second_name << "[" << index << "]" 
	      << " = " << second_value << ": failed!\n";
	}
	// Single Compare
	else
	{
	  out << first_name << " = " << first_value
	      << " == " << second_name << " = " << second_value 
	      << ": ";
	}
	
	success = false;
      }
    }
    else
    {
      typedef Teuchos::ScalarTraits<double> ST;
      ST::magnitudeType err = ST::magnitude( first_value - second_value )/
	std::max( ST::magnitude( first_value ),
		  ST::magnitude( second_value ) );
      
      if( err > tol )
      {
	// Array Element Compare
	if( index >= 0 )
	{
	  out << "\nError, relErr(" << first_name << "[" << index << "],"
	      << second_name << "[" << index << "])" << " = relErr(" 
	      << first_value << "," << second_value << ") = " << err
	      << " <= tol = " << tol << ": failed!\n";
	}
	// Single Compare
	else
	{
	  out << "\nCheck: relErr(" << first_name << "," << second_name << ")"
	      << "\n= relErr(" << first_value << "," << second_value << ") = "
	      << err << "\n<= tol = " << tol << ": ";
	}

	success = false;
      }	  
    }
    
    return success;
  }
};

template<typename T, typename T2>
struct ComparePolicy<Pair<T,T2> >
{
  static inline bool compare( const Pair<T,T2> &first_value,
			      const std::string &first_name,
			      const Pair<T,T2> &second_value,
			      const std::string &second_name,
			      Teuchos::FancyOStream &out,
			      const int index = -1,
			      const double tol = 0.0 )
  {
    return TupleComparePolicy<Pair<T,T2> >::compare( first_value,
						     first_name,
						     second_value,
						     second_name,
						     out,
						     index,
						     tol );
  }
};

template<typename T, typename T2, typename T3>
struct ComparePolicy<Trip<T,T2,T3> >
{
  static inline bool compare( const Trip<T,T2,T3> &first_value,
			      const std::string &first_name,
			      const Trip<T,T2,T3> &second_value,
			      const std::string &second_name,
			      Teuchos::FancyOStream &out,
			      const int index = -1,
			      const double tol = 0.0 )
  {
    return TupleComparePolicy<Trip<T,T2,T3> >::compare( first_value,
							first_name,
							second_value,
							second_name,
							out,
							index,
							tol );
  }
};

template<typename T, typename T2, typename T3, typename T4>
struct ComparePolicy<Quad<T,T2,T3,T4> >
{
  static inline bool compare( const Quad<T,T2,T3,T4> &first_value,
			      const std::string &first_name,
			      const Quad<T,T2,T3,T4> &second_value,
			      const std::string &second_name,
			      Teuchos::FancyOStream &out,
			      const int index = -1,
			      const double tol = 0.0 )
  {
    return TupleComparePolicy<Quad<T,T2,T3,T4> >::compare( first_value,
							   first_name,
							   second_value,
							   second_name,
							   out,
							   index,
							   tol );
  }
};

} // end FACEMC namespace

#endif // end COMPARE_POLICY_HPP

//---------------------------------------------------------------------------//
// end ComparePolicy.hpp
//---------------------------------------------------------------------------//
