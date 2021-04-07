//---------------------------------------------------------------------------//
//!
//! \file   Utility_ToStringTraits.hpp
//! \author Alex Robinson
//! \brief  ToStringTraits class specializations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TO_STRING_TRAITS_HPP
#define UTILITY_TO_STRING_TRAITS_HPP

// Std Lib Includes
#include <sstream>
#include <type_traits>
#include <iterator>
#include <stdexcept>
#include <complex>
#include <locale>
#include <codecvt>
#include <memory>

// Boost Includes
#include <boost/units/quantity.hpp>

// FRENSIE Includes
#include "Utility_ToStringTraitsDecl.hpp"
#include "Utility_LogRecordType.hpp"
#include "Utility_UnitTraits.hpp"

namespace Utility{

/*! Specialization of ToStringTraits for std::string
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<std::string>
{
  //! Return the string
  static inline std::string toString( const std::string& obj )
  { return obj; }

  //! Place the string in a stream
  static inline void toStream( std::ostream& os, const std::string& obj )
  { os << obj; }
};

/*! Specialization of ToStringTraits for std::wstring
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<std::wstring>
{
  //! Return the string
  static inline std::string toString( const std::wstring& obj )
  {
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;

    return converter.to_bytes( obj );
  }

  //! Place the string in a stream
  static inline void toStream( std::ostream& os, const std::wstring& obj )
  { os << ToStringTraits<std::wstring>::toString(obj); }
};

/*! Specialization of ToStringTraits for const char*
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<const char*>
{
  //! Return the string
  static inline std::string toString( const char* obj )
  { return obj; }

  //! Place the c-string in a stream
  static inline void toStream( std::ostream& os, const char* obj )
  { os << obj; }
};

/*! Specialization of ToStringTraits for char*
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<char*> : public ToStringTraits<const char*>
{ /* ... */ };

/*! Partial specialization of ToStringTraits for char[]
 * \ingroup to_string_traits
 */
template<size_t N>
struct ToStringTraits<char[N]> : public ToStringTraits<const char*>
{ /* ... */ };

/*! Specialization of ToStringTraits for enum types
 *
 * The enum type must have an overload for the ostream << operator defined.
 * \ingroup to_string_traits
 */
template<typename T>
struct ToStringTraits<T,typename std::enable_if<std::is_enum<T>::value>::type>
{
  //! Return the string
  static std::string toString( const T enum_obj )
  {
    std::ostringstream oss;

    ToStringTraits<T>::toStream( oss, enum_obj );

    return oss.str();
  }

  //! Place the enum value in a stream
  static inline void toStream( std::ostream& os, const T enum_obj )
  { os << enum_obj; }
};
  
/*! Specialization of ToStringTraits for bool
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<bool>
{
  //! Convert the boolean to a string
  static inline std::string toString( const bool& obj )
  { return (obj ? "true" : "false"); }

  //! Place the boolean in a stream
  static inline void toStream( std::ostream& os, const bool& obj )
  { os << ToStringTraits<bool>::toString( obj ); }
};

/*! Specialization of ToStringTraits for float
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<float>
{
  //! Convert the float to a string
  static inline std::string toString( const float& obj )
  {
    std::ostringstream oss;

    ToStringTraits<float>::toStream( oss, obj );
    
    return oss.str();
  }

  //! Place to float in a stream
  static inline void toStream( std::ostream& os, const float& obj )
  {
    // Make the stream precision high enough to capture the float without any
    // rounding loss
    os.setf( std::ios::scientific );
    os.precision( 9 );
    
    os << obj;
  }
};

/*! Specialization of ToStringTraits for double
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<double>
{
  //! Convert the double to a string
  static inline std::string toString( const double& obj )
  {
    std::ostringstream oss;

    ToStringTraits<double>::toStream( oss, obj );
    
    return oss.str();
  }

  //! Place the double in a stream
  static inline void toStream( std::ostream& os, const double& obj )
  {
    // Make the stream precision high enough to capture the double without any
    // rounding loss
    os.setf( std::ios::scientific );
    os.precision( 18 );
    
    os << obj;
  }
};

/*! Specialization of ToStringTraits for long double
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<long double> : public ToStringTraits<double>
{ /* ... */ };

/*! Partial specialization of ToStringTraits for integral types
 * \ingroup to_string_traits
 */
template<typename T>
struct ToStringTraits<T,typename std::enable_if<std::is_integral<T>::value>::type>
{
  //! Convert the integral type to a string
  static inline std::string toString( const T& obj )
  {
    std::ostringstream oss;

    ToStringTraits<T>::toStream( oss, obj );

    return oss.str();
  }

  //! Place the integral type in a stream
  static inline void toStream( std::ostream& os, const T& obj )
  { os << obj; }
};

/*! Partial specialization of ToStringTraits for std::exception types
 * \ingroup to_string_traits
 */
template<typename T>
struct ToStringTraits<T,typename std::enable_if<std::is_base_of<std::exception,T>::value>::type>
{
  //! Convert the std::exception type to a string
  static inline std::string toString( const std::exception& obj )
  { return obj.what(); }

  //! Place the std::exception type in a stream
  static inline void toStream( std::ostream& os, const std::exception& obj )
  { os << obj.what(); }
};

/*! Partial specialization of ToStringTraits for std::complex types
 * \ingroup to_string_traits
 */
template<typename T>
struct ToStringTraits<std::complex<T> >
{
  //! Convert the std::complex type to a string
  static inline std::string toString( const std::complex<T>& obj )
  {
    std::ostringstream oss;

    ToStringTraits<std::complex<T> >::toStream( oss, obj );

    return oss.str();
  }

  //! Place the std::complex type in a stream
  static inline void toStream( std::ostream& os, const std::complex<T>& obj )
  {
    os << Utility::container_start_char
       << Utility::toString( obj.real() )
       << Utility::next_container_element_char << " "
       << Utility::toString( obj.imag() ) 
       << Utility::container_end_char;
  }
};

/*! Partial specialization of ToStringTraits for boost::units::quantity types
 * \ingroup to_string_traits
 */
template<typename Unit, typename T>
struct ToStringTraits<boost::units::quantity<Unit,T> >
{
  //! Convert the quantity type to a string
  static inline std::string toString( const boost::units::quantity<Unit,T>& obj )
  {
    std::ostringstream oss;

    ToStringTraits<boost::units::quantity<Unit,T> >::toStream( oss, obj );

    return oss.str();
  }

  //! Place the quantity type in a stream
  static inline void toStream( std::ostream& os,
                               const boost::units::quantity<Unit,T>& obj )
  {
    Utility::toStream( os, obj.value() );
    os << " " << Utility::UnitTraits<Unit>::symbol();
  }
};

/*! Partial specialization of ToStringTraits for raw pointer types
 * \ingroup to_string_traits
 */
template<typename T>
struct ToStringTraits<T*,typename std::enable_if<(sizeof(T)>1)>::type>
{
  //! Convert the pointer type to a string
  static inline std::string toString( const T* const & obj )
  {
    if( obj == NULL )
      return "NULL";
    else
    {
      std::ostringstream oss;
      oss << std::hex << obj;

      return oss.str();
    }
  }

  //! Place the pointer type in a stream
  static inline void toStream( std::ostream& os,
                               const T* const& obj )
  { os << ToStringTraits<T*>::toString( obj ); }
};

/*! Partial specialization of ToStringTraits for shared pointers types
 * \ingroup to_string_traits
 */
template<typename T>
struct ToStringTraits<std::shared_ptr<T>, typename std::enable_if<(sizeof(T)>1)>::type>
{
  //! Convert the pointer type to a string
  static inline std::string toString( const std::shared_ptr<T>& obj )
  { return ToStringTraits<T*>::toString( obj.get() ); }

  //! Place the pointer type in a stream
  static inline void toStream( std::ostream& os,
                               const std::shared_ptr<T>& obj )
  { return ToStringTraits<T*>::toStream( os, obj.get() ); }
};
  
namespace Details{

//! ToStringTraits helper class for types with iterators
template<typename T>
struct ToStringTraitsIteratorHelper
{
  //! Convert the object of type T to a string
  static inline std::string toString( const T& obj )
  { 
    std::ostringstream oss;

    ToStringTraits<T>::toStream( oss, obj );

    return oss.str();
  }

  //! Place the object of type T in a stream
  static inline void toStream( std::ostream& os, const T& obj )
  {
    os << Utility::container_start_char;

    typename T::const_iterator it, end;
    it = obj.begin();
    end = obj.end();

    while( it != end )
    {
      Utility::toStream( os, *it );

      ++it;

      if( it != end )
        os << Utility::next_container_element_char << " ";
    }

    os << Utility::container_end_char;
  }
};
  
} // end Details namespace

/*! Partial specialization of ToStringTraits for std::initializer_list types
 * \ingroup to_string_traits
 */
template<typename T>
struct ToStringTraits<std::initializer_list<T> > : public Details::ToStringTraitsIteratorHelper<std::initializer_list<T> >
{ /* ... */ };

// Convert the object to a string
template<typename T>
inline std::string toString( const T& obj )
{
  return Utility::ToStringTraits<T>::toString( obj );
}

// Convert an initializer list to a string
template<typename T>
inline std::string toString( std::initializer_list<T> obj )
{
  return Utility::ToStringTraits<std::initializer_list<T> >::toString( obj );
}

// Place the object in a stream
template<typename T>
inline void toStream( std::ostream& os, const T& obj )
{
  Utility::ToStringTraits<T>::toStream( os, obj );
}

// Place an initializer list in a stream
template<typename T>
void toStream( std::ostream& os, std::initializer_list<T> obj )
{
  Utility::ToStringTraits<std::initializer_list<T> >::toStream( os, obj );
}

} // end Utility namespace

#endif // end UTILITY_TO_STRING_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_ToStringTraits.hpp
//---------------------------------------------------------------------------//
