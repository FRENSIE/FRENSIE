//---------------------------------------------------------------------------//
//!
//! \file   Utility_ComparePolicy.hpp
//! \author Alex Robinson
//! \brief  Compare policy specializations
//! 
//---------------------------------------------------------------------------//

#ifndef UTILITY_COMPARE_POLICY_HPP
#define UTILITY_COMPARE_POLICY_HPP

// Std Lib Includes
#include <string>

// Trilinos Includes
#include <Teuchos_FancyOStream.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_ComparePolicyDecl.hpp"
#include "Utility_Tuple.hpp"

namespace Utility{

namespace Policy{

//---------------------------------------------------------------------------//
// ComparePolicy Helper Functions.
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

/*! \brief The specialization of the Utility::ComparePolicy for const int.
 * \ingroup compare_policy
 */
template<>
struct ComparePolicy<const int>
{
  typedef const int scalarType;
  
  static inline bool compare( const int &first_value,
			      const std::string &first_name,
			      const int &second_value,
			      const std::string &second_name,
			      Teuchos::FancyOStream &out,
			      const int index = -1,
			      const scalarType tol = 0 )
  {
    bool success = true;
      
    // Array Element Compare
    if( index >= 0 )
    {
      out << "\nError, " << first_name << "[" << index << "]" << " = "
	  << first_value << " == " << second_name << "[" << index << "]" 
	  << " = " << second_value << ": ";
      if( first_value != second_value )
      { 
	out << "failed!\n";

	success = false;
      }
      else
	out << "passed\n";
    }
    // Single Compare
    else
    {
      out << first_name << " = " << first_value
	  << " == " << second_name << " = " << second_value 
	  << ": ";
      if( first_value != second_value )
      {
	out << "failed!\n";

	success = false;
      }
      else
	out << "passed\n";
    }
    
    return success;
  }
};

/*! \brief The specialization of the Utility::ComparePolicy for int.
 * \ingroup compare_policy
 */
template<>
struct ComparePolicy<int>
{
  typedef int scalarType;
  
  static inline bool compare( const int &first_value,
			      const std::string &first_name,
			      const int &second_value,
			      const std::string &second_name,
			      Teuchos::FancyOStream &out,
			      const int index = -1,
			      const scalarType tol = 0 )
  {
    return ComparePolicy<const int>::compare( first_value,
					      first_name,
					      second_value,
					      second_name,
					      out,
					      index,
					      tol );
  }
};

/*! \brief The specialization of the Utility::ComparePolicy for const
 * unsigned int.
 * \ingroup compare_policy
 */
template<>
struct ComparePolicy<const unsigned int>
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
      
    // Array Element Compare
    if( index >= 0 )
    {
      out << "\nError, " << first_name << "[" << index << "]" << " = "
	  << first_value << " == " << second_name << "[" << index << "]" 
	  << " = " << second_value << ": ";
      if( first_value != second_value )
      {
	out << "failed!\n";

	success = false;
      }
      else
	out << "passed\n";
    }
    // Single Compare
    else
    {
      out << first_name << " = " << first_value
	  << " == " << second_name << " = " << second_value 
	  << ": ";
      if( first_value != second_value )
      {
	out << "failed!\n";

	success = false;
      }
      else
	out << "passed\n";
    }
    
    return success;
  }
};

/*! \brief The specialization of the Utility::ComparePolicy for unsigned int.
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
    return ComparePolicy<const unsigned int>::compare( first_value,
						       first_name,
						       second_value,
						       second_name,
						       out,
						       index,
						       tol );
  }
};

/*! \brief The specialization of the Utility::ComparePolicy for const
 * unsigned long int.
 * \ingroup compare_policy
 */
template<>
struct ComparePolicy<const unsigned long int>
{
  typedef unsigned int scalarType;
  
  static inline bool compare( const unsigned long int &first_value,
			      const std::string &first_name,
			      const unsigned long int &second_value,
			      const std::string &second_name,
			      Teuchos::FancyOStream &out,
			      const int index = -1,
			      const scalarType tol = 0 )
  {
    bool success = true;
      
    // Array Element Compare
    if( index >= 0 )
    {
      out << "\nError, " << first_name << "[" << index << "]" << " = "
	  << first_value << " == " << second_name << "[" << index << "]" 
	  << " = " << second_value << ": ";
      if( first_value != second_value )
      {
	out << "failed!\n";

	success = false;
      }
      else
	out << "passed\n";
    }
    // Single Compare
    else
    {
      out << first_name << " = " << first_value
	  << " == " << second_name << " = " << second_value 
	  << ": ";
      if( first_value != second_value )
      {
	out << "failed!\n";

	success = false;
      }
      else
	out << "passed\n";
    }
      
    return success;
  }
};

/*! \brief The specialization of the Utility::ComparePolicy for unsigned long 
 * int.
 * \ingroup compare_policy
 */
template<>
struct ComparePolicy<unsigned long int>
{
  typedef unsigned int scalarType;
  
  static inline bool compare( const unsigned long int &first_value,
			      const std::string &first_name,
			      const unsigned long int &second_value,
			      const std::string &second_name,
			      Teuchos::FancyOStream &out,
			      const int index = -1,
			      const scalarType tol = 0 )
  {
    return ComparePolicy<const unsigned long int>::compare( first_value,
							    first_name,
							    second_value,
							    second_name,
							    out,
							    index,
							    tol );
  }
};

/*! \brief The specialization of the Utility::ComparePolicy for const
 * unsigned long long int.
 * \ingroup compare_policy
 */
template<>
struct ComparePolicy<const unsigned long long int>
{
  typedef unsigned int scalarType;
  
  static inline bool compare( const unsigned long long int &first_value,
			      const std::string &first_name,
			      const unsigned long long int &second_value,
			      const std::string &second_name,
			      Teuchos::FancyOStream &out,
			      const int index = -1,
			      const scalarType tol = 0 )
  {
    bool success = true;
      
    // Array Element Compare
    if( index >= 0 )
    {
      out << "\nError, " << first_name << "[" << index << "]" << " = "
	  << first_value << " == " << second_name << "[" << index << "]" 
	  << " = " << second_value << ": ";
      if( first_value != second_value )
      {
	out << "failed!\n";

	success = false;
      }
      else
	out << "passed\n";
    }
    // Single Compare
    else
    {
      out << first_name << " = " << first_value
	  << " == " << second_name << " = " << second_value 
	  << ": ";
      if( first_value != second_value )
      {
	out << "failed!\n";

	success = false;
      }
      else
	out << "passed\n";
    }

    return success;
  }
};

/*! \brief The specialization of the Utility::ComparePolicy for unsigned long 
 * long int.
 * \ingroup compare_policy
 */
template<>
struct ComparePolicy<unsigned long long int>
{
  typedef unsigned int scalarType;
  
  static inline bool compare( const unsigned long long int &first_value,
			      const std::string &first_name,
			      const unsigned long long int &second_value,
			      const std::string &second_name,
			      Teuchos::FancyOStream &out,
			      const int index = -1,
			      const scalarType tol = 0 )
  {
    return ComparePolicy<const unsigned long long int>::compare( first_value,
								 first_name,
								 second_value,
								 second_name,
								 out,
								 index,
								 tol );
  }
};

/*! \brief The specialization of the Utility::ComparePolicy for const double.
 * \ingroup compare_policy
 */
template<>
struct ComparePolicy<const double>
{
  typedef const double scalarType;
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
      // Array Element Compare
      if( index >= 0 )
      {
	out << "\nError, " << first_name << "[" << index << "]" << " = "
	    << first_value << " == " << second_name << "[" << index << "]" 
	    << " = " << second_value << ": ";
	if( first_value != second_value )
	{
	  out << "failed!\n";

	  success = false;
	}
	else 
	  out << "passed\n";
      }
      // Single Compare
      else
      {
	out << first_name << " = " << first_value
	    << " == " << second_name << " = " << second_value 
	    << ": ";
	if( first_value != second_value )
	{
	  out << "failed!\n";

	  success = false;
	}
	else 
	  out << "passed\n";
      }
    }
    else
    {
      double err = relError( first_value, second_value );
      
      // Array Element Compare
      if( index >= 0 )
      {
	out << "\nError, relErr(" << first_name << "[" << index << "],"
	    << second_name << "[" << index << "])" << " = relErr(" 
	    << first_value << "," << second_value << ") = " << err
	    << " <= tol = " << tol << ": ";
	if( err > tol )
	{
	  out << "failed!\n";

	  success = false;
	}
	else 
	  out << "passed\n";
      }
      // Single Compare
      else
      {
	out << "\nCheck: relErr(" << first_name << "," << second_name << ")"
	    << "\n= relErr(" << first_value << "," << second_value << ") = "
	    << err << "\n<= tol = " << tol << ": ";
	if( err > tol )
	{
	  out << "failed!\n";

	  success = false;
	}
	else 
	  out << "passed\n";
      }
    }
    
    return success;
  }
};

/*! \brief The specialization of the Utility::ComparePolicy for double.
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
    return ComparePolicy<const double>::compare( first_value,
						 first_name,
						 second_value,
						 second_name,
						 out,
						 index,
						 tol );
  }
};

/*! \brief The specialization of the Utility::ComparePolicy for const float.
 * \ingroup compare_policy
 */
template<>
struct ComparePolicy<const float>
{
  typedef const float scalarType;
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
      // Array Element Compare
      if( index >= 0 )
      {
	out << "\nError, " << first_name << "[" << index << "]" << " = "
	    << first_value << " == " << second_name << "[" << index << "]" 
	    << " = " << second_value << ": ";
	if( first_value != second_value )
	{
	  out << "failed!\n";

	  success = false;
	}
	else 
	  out << "passed\n";
      }
      // Single Compare
      else
      {
	out << first_name << " = " << first_value
	    << " == " << second_name << " = " << second_value 
	    << ": ";
	if( first_value != second_value )
	{
	  out << "failed!\n";

	  success = false;
	}
	else 
	  out << "passed\n";
      }
    }
    else
    {
      float err = relError( first_value, second_value );
      
      // Array Element Compare
      if( index >= 0 )
      {
	out << "\nError, relErr(" << first_name << "[" << index << "],"
	    << second_name << "[" << index << "])" << " = relErr(" 
	    << first_value << "," << second_value << ") = " << err
	    << " <= tol = " << tol << ": ";
	if( err > tol )
	{
	  out << "failed!\n";

	  success = false;
	}
	else
	  out << "passed\n";
      }
      // Single Compare
      else
      {
	out << "\nCheck: relErr(" << first_name << "," << second_name << ")"
	    << "\n= relErr(" << first_value << "," << second_value << ") = "
	    << err << "\n<= tol = " << tol << ": ";
	if( err > tol )
	{
	  out << "failed!\n";

	  success = false;
	}
	else
	  out << "passed\n";
      }
    }
    
    return success;
  }
};

/*! \brief The specialization of the Utility::ComparePolicy for float.
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
    return ComparePolicy<const float>::compare( first_value,
						first_name, 
						second_value,
						second_name,
						out,
						index,
						tol );
  }
};

/*! \brief The partial specialization of the Utility::ComparePolicy for 
 * const Utility::Pair. 
 * \ingroup compare_policy
 */
template<typename T, typename T2>
struct ComparePolicy<const Pair<T,T2> >
{
  typedef const double scalarType;
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

/*! \brief The partial specialization of the Utility::ComparePolicy for 
 * Utility::Pair. 
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
    return ComparePolicy<const Pair<T,T2> >::compare( first_value,
						      first_name,
						      second_value,
						      second_name,
						      out,
						      index,
						      tol );
  }
};

/*! \brief The partial specialization of the Utility::ComparePolicy for
 * const std::pair.
 * \ingroup compare_policy
 */
template<typename T, typename T2>
struct ComparePolicy<const std::pair<T,T2> >
{
  typedef const double scalarType;
  static inline bool compare( const std::pair<T,T2> &first_value,
			      const std::string &first_name,
			      const std::pair<T,T2> &second_value,
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

/*! \brief The partial specialization of the Utility::ComparePolicy for
 * std::pair.
 * \ingroup compare_policy
 */
template<typename T, typename T2>
struct ComparePolicy<std::pair<T,T2> >
{
  typedef const double scalarType;
  static inline bool compare( const std::pair<T,T2> &first_value,
			      const std::string &first_name,
			      const std::pair<T,T2> &second_value,
			      const std::string &second_name,
			      Teuchos::FancyOStream &out,
			      const int index = -1,
			      const scalarType tol = 0.0 )
  {
    return ComparePolicy<const std::pair<T,T2> >::compare( first_value,
							   first_name,
							   second_value,
							   second_name,
							   out,
							   index,
							   tol );
  }
};

/*! \brief The partial specialization of the Utility::ComparePolicy for 
 * const Utility::Trip. 
 * \ingroup compare_policy
 */
template<typename T, typename T2, typename T3>
struct ComparePolicy<const Trip<T,T2,T3> >
{
  typedef const double scalarType;
  
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

/*! \brief The partial specialization of the Utility::ComparePolicy for 
 * Utility::Trip. 
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
    return ComparePolicy<const Trip<T,T2,T3> >::compare( first_value,
							 first_name,
							 second_value,
							 second_name,
							 out,
							 index,
							 tol );
  }
};

/*! \brief The partial specialization of the Utility::ComparePolicy for 
 * const Utility::Quad. 
 * \ingroup compare_policy
 */
template<typename T, typename T2, typename T3, typename T4>
struct ComparePolicy<const Quad<T,T2,T3,T4> >
{
  typedef const double scalarType;
  
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

/*! \brief The partial specialization of the Utility::ComparePolicy for 
 * Utility::Quad. 
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
    return ComparePolicy<const Quad<T,T2,T3,T4> >::compare( first_value,
							    first_name,
							    second_value,
							    second_name,
							    out,
							    index,
							    tol );
  }
};

} // end Policy namespace

} // end Utility namespace

#endif // end UTILITY_COMPARE_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_ComparePolicy.hpp
//---------------------------------------------------------------------------//
