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
#include <deque>

// FRENSIE Includes
#include "Utility_Vector.hpp"
#include "Utility_List.hpp"
#include "Utility_Deque.hpp"
#include "Utility_ToStringTraits.hpp"
#include "Utility_FromStringTraits.hpp"

namespace Utility{

//! The variant class
class Variant
{

public:

  //! Default constructor
  Variant();

  //! Copy constructor
  Variant( const Variant& other );

  //! Constructor
  template<typename T>
  explicit Variant( const T& object );

  //! Destructor
  ~Variant()
  { /* ... */ }

  //! Assignment operator
  Variant& operator=( const Variant& that );

  //! Create a variant
  template<typename T>
  static Variant fromValue( const T& object );

  //! Set the value of the variant
  template<typename T>
  void setValue( const T& object );

  //! Check if the variant is null (no stored object)
  bool isNull();

  //! Swap this variant with another
  void swap( Variant& other );

  //! Clear the variant
  void clear();

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

  //! Convert the variant to a vector
  std::vector<Variant> toVector( bool* success = NULL ) const noexcept;

  //! Convert the variant to a list
  std::list<Variant> toList( bool* success = NULL ) const noexcept;

  //! Convert the variant to forward list
  std::forward_list<Variant> toForwardList( bool* success = NULL ) const noexcept;

  //! Convert the variant to a deque
  std::deque<Variant> toDeque( bool* success = NULL ) const noexcept;

  //! Convert the variant to the desired type
  template<typename T>
  T toType( bool* success = NULL ) const;

  //! Inequality operator
  bool operator!=( const Variant& other ) const;

  //! Equality operator
  bool operator==( const Variant& other ) const;

private:

  // The store type
  std::string d_stored_data;
};

//! Cast the variant to the desired type
template<typename T>
T variant_cast( const Variant& variant );

/*! Specialization of Utility::ToStringTraits for Utility::Variant
 * \ingropu to_string_traits
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
    std::string obj_data;
    Utility::fromStream( is, obj_data, delims );
                        
    obj.setValue( obj_data );
  }
};

//! Place a Variant in a stream
inline std::ostream& operator<<( std::ostream& os, const Variant& variant )
{
  Utility::toStream( os, variant );

  return os;
}

//! Extract a Variant from a stream
inline std::istream& operator>>( std::istream& is, Variant& variant )
{
  Utility::fromStream( is, variant );

  return is;
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_Variant_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_VARIANT_HPP

//---------------------------------------------------------------------------//
// end Utility_Variant.hpp
//---------------------------------------------------------------------------//
