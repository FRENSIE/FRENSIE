//---------------------------------------------------------------------------//
//!
//! \file   Utility_Variant.hpp
//! \author Alex Robinson
//! \brief  The variant class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_VARIANT_HPP
#define UTILITY_VARIANT_HPP

// Std Lib Includes
#include <string>
#include <type_traits>

// FRENSIE Includes
#include "Utility_Vector.hpp"
#include "Utility_List.hpp"
#include "Utility_Deque.hpp"
#include "Utility_Map.hpp"
#include "Utility_ToStringTraits.hpp"
#include "Utility_FromStringTraits.hpp"

/*! \defgroup variant Variant.
 *
 * The Utility::Variant class and many of the helper methods were inspired
 * by the Qt::Variant class, which is part of the Qt library.
 */

namespace Utility{

namespace Details{
  
template<typename T, typename Enabled = void>
struct ConvertHelper;
  
}

class Variant;

/*! The vector of Utility::Variant type
 * \ingroup variant
 */
typedef std::vector<Variant> VariantVector;

/*! The list of Utility::Variant type
 * \ingroup variant
 */
typedef std::list<Variant> VariantList;

/*! The forward list of Utility::Variant type
 * \ingroup variant
 */
typedef std::forward_list<Variant> VariantForwardList;

/*! The deque of Utility::Variant type
 * \ingroup variant
 */
typedef std::deque<Variant> VariantDeque;

/*! The map of std::string, Utility::Variant type
 * \ingroup variant
 */
typedef std::map<std::string,Variant> VariantMap;

/*! The variant class
 * \ingroup variant
 */
class Variant
{

public:

  //! Typedefs for std::string interfaces
  typedef std::string::value_type value_type;

  //! Default constructor
  Variant();

  //! Copy constructor
  Variant( const Variant& other );

  //! String constructor
  Variant( const std::string& object );

  //! Constructor
  template<typename T>
  explicit Variant( const T& object );

  //! Destructor
  ~Variant()
  { /* ... */ }

  //! Assignment operator
  Variant& operator=( const Variant& that );

  //! General assignment operator
  template<typename T>
  Variant& operator=( const T& that );

  //! Create a variant
  template<typename T>
  static Variant fromValue( const T& object );

  //! Set the value of the variant
  template<typename T>
  void setValue( const T& object );

  //! Check if the variant is null (no stored object)
  bool isNull() const;

  //! Swap this variant with another
  void swap( Variant& other );

  //! Clear the variant
  void clear();

  //! Check if the variant stores a basic type
  bool storesBasicType() const;

  //! Check if the variant stores a container type
  bool storesContainerType() const;

  //! Check if the variant can be converted to the type of interest
  template<typename T>
  bool canConvert() const;

  //! Convert the variant to the desired type
  template<typename T>
  void convert( T& object ) const;

  //! Convert the variant to a bool
  bool toBool( bool* success = NULL ) const noexcept;

  //! Convert the variant to a char
  char toChar( bool* success = NULL ) const noexcept;

  //! Convert the variant to a signed char
  signed char toSignedChar( bool* success = NULL ) const noexcept;

  //! Convert the variant to an unsigned char
  unsigned char toUnsignedChar( bool* success = NULL ) const noexcept;

  //! Convert the variant to an int8_t
  int8_t toInt8( bool* success = NULL ) const noexcept;

  //! Convert the variant to an uint8_t
  uint8_t toUint8( bool* success = NULL ) const noexcept;

  //! Convert the variant to an int16_t
  int16_t toInt16( bool* success = NULL ) const noexcept;

  //! Convert the variant to a uint16_t
  uint16_t toUint16( bool* success = NULL ) const noexcept;

  //! Convert the variant to a int32_t
  int32_t toInt32( bool* success = NULL ) const noexcept;

  //! Convert the variant to a uint32_t
  uint32_t toUint32( bool* success = NULL ) const noexcept;

  //! Convert the variant to a short
  short toShort( bool* success = NULL ) const noexcept;

  //! Convert the variant to an unsigned short
  unsigned short toUnsignedShort( bool* success = NULL ) const;

  //! Convert the variant to an int
  int toInt( bool* success = NULL ) const noexcept;

  //! Convert the variant to an unsigned int
  unsigned int toUnsignedInt( bool* success = NULL ) const noexcept;

  //! Convert the variant to a long
  long toLong( bool* success = NULL ) const noexcept;

  //! Convert the variant to an unsigned long
  unsigned long toUnsignedLong( bool* success = NULL ) const noexcept;

  //! Convert the variant to a long long
  long long toLongLong( bool* success = NULL ) const noexcept;

  //! Convert the variant to an unsigned long long
  unsigned long long toUnsignedLongLong( bool* success = NULL ) const noexcept;

  //! Convert the variant to an int64_t
  int64_t toInt64( bool* success = NULL ) const noexcept;

  //! Conver the variant to an uint64_t
  uint64_t toUint64( bool* success = NULL ) const noexcept;

  //! Convert the variant to a float
  float toFloat( bool* success = NULL ) const noexcept;

  //! Convert the variant to a double
  double toDouble( bool* success = NULL ) const noexcept;

  //! Convert the variant to string
  std::string toString( bool* success = NULL ) const noexcept;

  //! Convert the variant to a lowercase string
  std::string toLowerString( bool* success = NULL ) const noexcept;

  //! Convert the variant to an uppercase string
  std::string toUpperString( bool* success = NULL ) const noexcept;

  //! Convert the variant to a vector
  VariantVector toVector( bool* success = NULL ) const noexcept;

  //! Convert the variant to a list
  VariantList toList( bool* success = NULL ) const noexcept;

  //! Convert the variant to forward list
  VariantForwardList toForwardList( bool* success = NULL ) const noexcept;

  //! Convert the variant to a deque
  VariantDeque toDeque( bool* success = NULL ) const noexcept;

  //! Convert the variant to a map
  VariantMap toMap( bool* success = NULL ) const noexcept;

  //! Convert the variant to the desired type
  template<typename T>
  T toType( bool* success = NULL ) const noexcept;

  //! Compactify the underlying data
  Variant& compactify();

  //! Inequality operator
  bool operator!=( const Variant& other ) const;

  //! Equality operator
  bool operator==( const Variant& other ) const;

  //! Inline addition operator
  Variant& operator+=( const Variant& other );

  //! Inline addition operator
  template<template<typename,typename...> class STLCompliantSequenceContainer>
  Variant& operator+=( const STLCompliantSequenceContainer<Variant>& other );

  //! Inline addition operator
  template<template<typename,typename,typename...> class STLCompliantAssociativeContainer>
  Variant& operator+=( const STLCompliantAssociativeContainer<std::string,Variant>& other );

  //! Inline addition operator
  Variant& operator+=( const char& string_element );

  //! Implicit conversion to std::string
  operator std::string() const;

private:

  // Convert the variant to a general container of variants
  template<typename Container>
  typename std::enable_if<std::is_same<typename Container::value_type,Utility::Variant>::value,Container>::type toContainerType( bool* success = NULL ) const noexcept;

  // The convert helper is a friend class
  template<typename T, typename Enabled = void>
  friend class Details::ConvertHelper;

  // The store type
  std::string d_stored_data;
};

/*! Cast the variant to the desired type
 * \ingroup variant
 */
template<typename T>
T variant_cast( const Variant& variant );

/*! Specialization of Utility::ToStringTraits for Utility::Variant
 * \ingroup variant
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<Variant>
{
  //! Convert a Variant to a string
  static inline std::string toString( const Variant& obj )
  { return obj.toString(); }

  //! Place the Variant in a stream
  static inline void toStream( std::ostream& os, const Variant& obj )
  { os << obj.toString(); }
};

/*! Specialization of Utility:FromStringTraits for Utility::Variant
 * \ingroup variant
 * \ingroup from_string_traits
 */
template<>
struct FromStringTraits<Variant>
{
  //! The type that a string will be converted to
  typedef Variant ReturnType;

  //! Convert the string to a Variant object
  static inline ReturnType fromString( const std::string& obj_rep )
  { return ReturnType( obj_rep ); }

  //! Extract a variant from a stream
  static inline void fromStream( std::istream& is,
                                 Variant& obj,
                                 const std::string& delims = std::string() )
  {
    std::string obj_rep;

    try{
      Utility::fromStream( is, obj_rep, delims );
    }
    EXCEPTION_CATCH_RETHROW( Utility::StringConversionException,
                             "Could not extract a variant from the stream!" );

    obj.setValue( obj_rep );
  }
};
  
} // end Utility namespace

namespace std{

/*! Swap two variants
 * \ingroup variant
 */
inline void swap( Utility::Variant& left, Utility::Variant& right )
{
  left.swap( right );
}

/*! Place a Utility::Variant in a stream
 * \ingroup variant
 */
inline std::ostream& operator<<( std::ostream& os,
                                 const Utility::Variant& variant )
{
  Utility::toStream( os, variant );

  return os;
}

/*! Extract a Utility::Variant from a stream
 * \ingroup variant
 */
inline std::istream& operator>>( std::istream& is, Utility::Variant& variant )
{
  Utility::fromStream( is, variant );

  return is;
}
  
} // end std namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_Variant_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_VARIANT_HPP

//---------------------------------------------------------------------------//
// end Utility_Variant.hpp
//---------------------------------------------------------------------------//
