//---------------------------------------------------------------------------//
//!
//! \file   ComparePolicy.hpp
//! \author Alex Robinson
//! \brief  Compare policy specializations
//! 
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
//#include "TupleComparePolicy.hpp"


namespace FACEMC{

//---------------------------------------------------------------------------//
// TupleComparePolicy Helper Functions.
//---------------------------------------------------------------------------//

/*! \brief Relative error of two values
 * \ingroup compare_policy
 */
template<typename ScalarType>
ScalarType relError( const ScalarType first_value, 
		     const ScalarType second_value )
{
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  typename ST::magnitudeType err;
  if( first_value != ST::zero() && second_value != ST::zero() )
  {
    err = ST::magnitude( first_value - second_value )/
      std::max( ST::magnitude( first_value ),
		ST::magnitude( second_value ) );
  }
  else
  {
    err = std::max( ST::magnitude( first_value ),
		    ST::magnitude( second_value ) );
  }

  return err;
}

/*! \brief Compare the first tuple members
 * \ingroup compare_policy
 */
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
  
  success = ComparePolicy<T>::compare( first_value,
				       first_tuple_member_name.str(),
				       second_value,
				       second_tuple_member_name.str(),
				       out,
				       -1,
				       tol );
  return success;
}

/*! \brief Compare the second tuple members
 * \ingroup compare_policy
 */
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
  
  success = ComparePolicy<T>::compare( first_value,
				       first_tuple_member_name.str(),
				       second_value,
				       second_tuple_member_name.str(),
				       out,
				       -1,
				       tol );
  return success;
}

/*! \brief Compare the third tuple members
 * \ingroup compare_policy
 */
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
  
  success = ComparePolicy<T>::compare( first_value,
				       first_tuple_member_name.str(),
				       second_value,
				       second_tuple_member_name.str(),
				       out,
				       -1,
				       tol );
  return success;
}

/*! \brief Compare the fourth tuple members
 * \ingroup compare_policy
 */
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
  
  success = ComparePolicy<T>::compare( first_value,
				       first_tuple_member_name.str(),
				       second_value,
				       second_tuple_member_name.str(),
				       out,
				       -1,
				       tol );
  return success;
}

/*! \brief The specialization of the FACEMC::ComparePolicy for unsigned int.
 * \ingroup compare_policy
 */
template<>
struct ComparePolicy<unsigned int>
{
  typedef unsigned int scalarType;
  
  static inline bool compare( const unsigned int &first_value,
			      const std::string &first_name,
			      const unsigned int &second_value,
			      const std::string &second_name,
			      Teuchos::FancyOStream &out,
			      const int index = -1,
			      const scalarType tol = 0 )
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

/*! \brief The specialization of the FACEMC::ComparePolicy for double.
 * \ingroup compare_policy
 */
template<>
struct ComparePolicy<double>
{
  typedef double scalarType;
  static inline bool compare( const double &first_value,
			      const std::string &first_name,
			      const double &second_value,
			      const std::string &second_name,
			      Teuchos::FancyOStream &out,
			      const int index = -1,
			      const scalarType tol = 0.0 )
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
      double err = relError( first_value, second_value );
      
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
	      << err << "\n<= tol = " << tol << ": failed!\n";
	}

	success = false;
      }	  
    }
    
    return success;
  }
};

/*! \brief The specialization of the FACEMC::ComparePolicy for float.
 * \ingroup compare_policy
 */
template<>
struct ComparePolicy<float>
{
  typedef float scalarType;
  static inline bool compare( const float &first_value,
			      const std::string &first_name,
			      const float &second_value,
			      const std::string &second_name,
			      Teuchos::FancyOStream &out,
			      const int index = -1,
			      const scalarType tol = 0.0f )
  {
    bool success = true;
      
    if( tol == 0.0f )
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
	      << ": failed!\n";
	}
	
	success = false;
      }
    }
    else
    {
      float err = relError( first_value, second_value );
      
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
	      << err << "\n<= tol = " << tol << ": failed!\n";
	}

	success = false;
      }	  
    }
    
    return success;
  }
};

/*! \brief The partial specialization of the FACEMC::ComparePolicy for 
 * FACEMC::Pair. 
 * \ingroup compare_policy
 */
template<typename T, typename T2>
struct ComparePolicy<Pair<T,T2> >
{
  typedef double scalarType;
  static inline bool compare( const Pair<T,T2> &first_value,
			      const std::string &first_name,
			      const Pair<T,T2> &second_value,
			      const std::string &second_name,
			      Teuchos::FancyOStream &out,
			      const int index = -1,
			      const scalarType tol = 0.0 )
  {
    bool success = true;
    
    // Compare the first tuple members
    {
      bool local_success = true;
      local_success = compareFirstTupleMembers<T>( first_value.first,
						   first_name,
						   second_value.first,
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
      local_success = compareSecondTupleMembers<T2>( first_value.second,
						     first_name,
						     second_value.second,
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

/*! \brief The partial specialization of the FACEMC::ComparePolicy for 
 * FACEMC::Trip. 
 * \ingroup compare_policy
 */
template<typename T, typename T2, typename T3>
struct ComparePolicy<Trip<T,T2,T3> >
{
  typedef double scalarType;
  
  static inline bool compare( const Trip<T,T2,T3> &first_value,
			      const std::string &first_name,
			      const Trip<T,T2,T3> &second_value,
			      const std::string &second_name,
			      Teuchos::FancyOStream &out,
			      const int index = -1,
			      const scalarType tol = 0.0 )
  {
    bool success = true;
    
    // Compare the first tuple members
    {
      bool local_success = true;
      local_success = compareFirstTupleMembers<T>( first_value.first,
						   first_name,
						   second_value.first,
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
      local_success = compareSecondTupleMembers<T2>( first_value.second,
						     first_name,
						     second_value.second,
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
      local_success = compareThirdTupleMembers<T3>( first_value.third,
						    first_name,
						    second_value.third,
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

/*! \brief The partial specialization of the FACEMC::ComparePolicy for 
 * FACEMC::Quad. 
 * \ingroup compare_policy
 */
template<typename T, typename T2, typename T3, typename T4>
struct ComparePolicy<Quad<T,T2,T3,T4> >
{
  typedef double scalarType;
  
  static inline bool compare( const Quad<T,T2,T3,T4> &first_value,
			      const std::string &first_name,
			      const Quad<T,T2,T3,T4> &second_value,
			      const std::string &second_name,
			      Teuchos::FancyOStream &out,
			      const int index = -1,
			      const scalarType tol = 0.0 )
  {
    bool success = true;
    
    // Compare the first tuple members
    {
      bool local_success = true;
      local_success = compareFirstTupleMembers<T>( first_value.first,
						   first_name,
						   second_value.first,
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
      local_success = compareSecondTupleMembers<T2>( first_value.second,
						     first_name,
						     second_value.second,
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
      local_success = compareThirdTupleMembers<T3>( first_value.third,
						    first_name,
						    second_value.third,
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
      local_success = compareFourthTupleMembers<T4>( first_value.fourth,
						     first_name,
						     second_value.fourth,
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

#endif // end COMPARE_POLICY_HPP

//---------------------------------------------------------------------------//
// end ComparePolicy.hpp
//---------------------------------------------------------------------------//
