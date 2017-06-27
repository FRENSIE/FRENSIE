//---------------------------------------------------------------------------//
//!
//! \file   Utility_ComparisonTraits.hpp
//! \author Alex Robinson
//! \brief  Comparison traits specializations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_COMPARISON_TRAITS_HPP
#define UTILITY_COMPARISON_TRAITS_HPP

// Std Lib Includes
#include <string>
#include <utility>

// Boost Includes
#include <boost/units/quantity.hpp>
#include <boost/units/io.hpp>

// Trilinos Includes
#include <Teuchos_FancyOStream.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_ComparisonTraitsDecl.hpp"
#include "Utility_Tuple.hpp"

namespace Utility{

/*! The specialization of the Utility::ComparisonTraits for const types.
 * \ingroup comparison_traits
 */
template<typename T>
struct ComparisonTraits<T,typename std::enable_if<std::is_const<T>::value && !std::is_volatile<T>::value>::type> : public ComparisonTraits<typename std::remove_const<T>::type>
{ /* ... */ };

/*! The specialization of the Utility::ComparisonTraits for volatile types.
 * \ingroup comparison_traits
 */
template<typename T>
struct ComparisonTraits<T,typename std::enable_if<!std::is_const<T>::value && std::is_volatile<T>::value>::type> : public ComparisonTraits<typename std::remove_volatile<T>::type>
{ /* ... */ };

/*! \brief The specialization of the Utility::ComparisonTraits for const
 * volatile types.
 * \ingroup comparison_traits
 */
template<typename T>
struct ComparisonTraits<T,typename std::enable_if<std::is_const<T>::value && std::is_volatile<T>::value>::type> : public ComparisonTraits<typename std::remove_cv<T>::type>
{ /* ... */ };

/*! \brief The specialization of the Utility::ComparisonTraits for std::string
 * \ingroup comparison_traits
 */
template<>
struct ComparisonTraits<std::string>
{
  typedef const double scalarType;

  static inline bool compare( const std::string& first_value,
			      const std::string& first_name,
			      const std::string& second_value,
			      const std::string& second_name,
			      Teuchos::FancyOStream& out,
			      const int index = -1,
			      const scalarType tol = 0 )
  {
    bool success = true;

    // Array Element Compare
    if( index >= 0 )
    {
      out << first_name << "[" << index << "]" << " = "
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

/*! \brief The specialization of the Utility::ComparisonTraits for 
 * integral types
 * \ingroup comparison_traits
 */
template<typename T>
struct ComparisonTraits<T,typename std::enable_if<std::is_integral<T>::value>::type>
{
  typedef const T scalarType;

  static inline bool compare( const T& first_value,
			      const std::string& first_name,
			      const T& second_value,
			      const std::string& second_name,
			      Teuchos::FancyOStream& out,
			      const int index = -1,
			      const scalarType tol = 0 )
  {
    bool success = true;

    // Array Element Compare
    if( index >= 0 )
    {
      out << first_name << "[" << index << "]" << " = "
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

/*! \brief The specialization of the Utility::ComparisonTraits for 
 * floating point types
 * \ingroup comparison_traits
 */
template<typename T>
struct ComparisonTraits<T,typename std::enable_if<std::is_floating_point<T>::value>::type>
{
  typedef const T scalarType;
  static inline bool compare( const T& first_value,
			      const std::string& first_name,
			      const T& second_value,
			      const std::string& second_name,
			      Teuchos::FancyOStream& out,
			      const int index = -1,
			      const scalarType tol = 0.0 )
  {
    bool success = true;

    if( tol == 0.0 )
    {
      // Array Element Compare
      if( index >= 0 )
      {
	out << first_name << "[" << index << "]" << " = "
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
      scalarType err = relError( first_value, second_value );

      // Array Element Compare
      if( index >= 0 )
      {
	out << "relErr(" << first_name << "[" << index << "],"
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

namespace Details{

// The helper class that is used to compare tuple members
template<size_t I, typename TupleType, typename Enabled = void>
struct TupleMemberCompareHelper
{
  static inline bool compareTupleMembers(
                     const TupleType& first_tuple,
                     const std::string& first_name,
                     const TupleType& second_tuple,
                     const std::string& second_name,
                     Teuchos::FancyOStream& out,
                     const int index,
                     const double tol )
  {
    std::ostringstream first_tuple_member_name;
    std::ostringstream second_tuple_member_name;

    // Array element compare
    if( index >= 0 )
    {
      first_tuple_member_name << first_name << "[" << index << "]." << I;
      second_tuple_member_name << second_name << "[" << index << "]." << I;
    }
    // Single tuple compare
    else
    {
      first_tuple_member_name << first_name << "." << I;
      second_tuple_member_name << second_name << "." << I;
    }

    bool local_success =
      Utility::ComparisonTraits<typename Utility::TupleElement<I,TupleType>::type>::compare(
                                              Utility::get<I>( first_tuple ),
                                              first_tuple_member_name.str(),
                                              Utility::get<I>( second_tuple ),
                                              second_tuple_member_name.str(),
                                              out,
                                              -1,
                                              tol );

    return local_success &&
      TupleMemberCompareHelper<I+1,TupleType>::compareTupleMembers(
                                                                  first_tuple,
                                                                  first_name,
                                                                  second_tuple,
                                                                  second_name,
                                                                  out,
                                                                  index,
                                                                  tol );
  }
};

// The helper class that is used to compare tuple members
template<size_t I, typename TupleType>
struct TupleMemberCompareHelper<I,TupleType,typename std::enable_if<I==TupleSize<TupleType>::value>::type>
{
  static inline bool compareTupleMembers(
                     const TupleType& first_tuple,
                     const std::string& first_name,
                     const TupleType& second_tuple,
                     const std::string& second_name,
                     Teuchos::FancyOStream& out,
                     const int index,
                     const double tol )
  { return true; }
};

} // end Details namespace

/*! \brief The partial specialization of the Utility::ComparisonTraits for
 * const Utility::Tuple.
 * \ingroup comparison_traits
 */
template<typename... Types>
struct ComparisonTraits<std::tuple<Types...> >
{
  typedef const double scalarType;
  static inline bool compare( const std::tuple<Types...>& first_value,
			      const std::string& first_name,
			      const std::tuple<Types...>& second_value,
			      const std::string& second_name,
			      Teuchos::FancyOStream& out,
			      const int index = -1,
			      const scalarType tol = 0.0 )
  {
    return Details::TupleMemberCompareHelper<0,std::tuple<Types...> >::compareTupleMembers(
                                                                 first_value,
                                                                 first_name,
                                                                 second_value,
                                                                 second_name,
                                                                 out,
                                                                 index,
                                                                 tol );
  }
};

/*! \brief The partial specialization of the Utility::ComparisonTraits for
 * const std::pair.
 * \ingroup comparison_traits
 */
template<typename T1, typename T2>
struct ComparisonTraits<std::pair<T1,T2> >
{
  typedef const double scalarType;
  static inline bool compare( const std::pair<T1,T2>& first_value,
			      const std::string& first_name,
			      const std::pair<T1,T2>& second_value,
			      const std::string& second_name,
			      Teuchos::FancyOStream& out,
			      const int index = -1,
			      const scalarType tol = 0.0 )
  {
    return Details::TupleMemberCompareHelper<0,std::pair<T1,T2> >::compareTupleMembers(
                                                                 first_value,
                                                                 first_name,
                                                                 second_value,
                                                                 second_name,
                                                                 out,
                                                                 index,
                                                                 tol );
  }
};

/*! \brief The partial specialization of the Utility::ComparisonTraits for
 * boost::units::quantity.
 * \ingroup comparison_traits
 */
template<typename Unit, typename T>
struct ComparisonTraits<boost::units::quantity<Unit,T> >
{
  typedef const T scalarType;

  static inline bool compare(const boost::units::quantity<Unit,T>& first_value,
			     const std::string& first_name,
			     const boost::units::quantity<Unit,T>& second_value,
			     const std::string& second_name,
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
      double err = relError( first_value.value(), second_value.value() );

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

} // end Utility namespace

#endif // end UTILITY_COMPARISON_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_ComparisonTraits.hpp
//---------------------------------------------------------------------------//
