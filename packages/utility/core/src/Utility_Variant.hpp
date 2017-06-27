//---------------------------------------------------------------------------//
//!
//! \file   Utility_Variant.hpp
//! \author Alex Robinson
//! \brief  The variant class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_VARIANT_HPP
#define UTILITY_VARIANT_HPP

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
  Variant( const T& object );

  //! Destructor
  ~Variant()
  { /* ... */ }

  //! Assignment operator
  QVariant& operator=( const Variant& other );

  //! Create a variant
  template<typename T>
  static QVariant fromValue( const T& object );

  //! Set the value of the variant
  template<typename T>
  void setValue( const T& object );

  //! Swap this variant with another
  void swap( QVariant& other );

  //! Clear the variant
  void clear();

  //! Check if the variant can be converted to the type of interest
  template<typename T>
  bool canConvert() const;

  //! Convert the variant to the desired type
  template<typename T>
  void convert( T& object ) const noexcept;

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

  //! Convert the variant to a char16_t
  char16_t toChar16( bool* success = NULL ) const noexcept;

  //! Convert the variant to an int16_t
  int16_t toInt16( bool* success = NULL ) const noexcept;

  //! Convert the variant to a uint16_t
  uint16_t toUint16( bool* success = NULL ) const noexcept;

  //! Convert the variant to a char32_t
  char32_t toChar32( bool* success = NULL ) const noexcept;

  //! Convert the variant to a int32_t
  int32_t toInt32( bool* success = NULL ) const noexcept;

  //! Convert the variant to a uint32_t
  uint32_t toUint32( bool* success = NULL ) const noexcept;

  //! Convert the variant to a wchar_t
  wchar_t toWChar( bool* success = NULL ) const noexcept;

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
  std::vector<QVariant> toVector( bool* success = NULL ) const noexcept;

  //! Convert the variant to a list
  std::list<QVariant> toList( bool* success = NULL ) const noexcept;

  //! Convert the variant to forward list
  std::forward_list<QVariant> toForwardList( bool* success = NULL ) const noexcept;

  //! Convert the variant to a deque
  std::deque<QVariant> toDeque( bool* success = NULL ) const noexcept;

  //! Convert the variant to the desired type
  template<typename T>
  T toType() const;

  //! Inequality operator
  bool operator!=( const QVariant& other ) const;

  //! Equality operator
  bool operator==( const QVariant& other ) const;

private:

  // The store type
  std::string d_stored_data;
};

//! Cast the variant to the desired type
template<typename T>
T variant_cast( const Variant& variant );
  
} // end Utility namespace

#endif // end UTILITY_VARIANT_HPP

//---------------------------------------------------------------------------//
// end Utility_Variant.hpp
//---------------------------------------------------------------------------//
