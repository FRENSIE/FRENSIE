//---------------------------------------------------------------------------//
//!
//! \file   Utility_Variant.cpp
//! \author Alex Robinson
//! \brief  The variant class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <algorithm>
#include <functional>
#include <cctype>

// Boost Includes
#include <boost/algorithm/string.hpp>

// FRENSIE Includes
#include "Utility_Variant.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

// Default constructor
Variant::Variant()
  : d_stored_data()
{ /* ... */ }

// String constructor
/*! \details This constructor is not explicit - implicit conversion from
 * std::string to Utility::Variant is allowed (unlike with other types).
 */
Variant::Variant( const std::string& object )
  : d_stored_data( object )
{ /* ... */ }

// Copy constructor
Variant::Variant( const Variant& other )
  : d_stored_data( other.d_stored_data )
{ /* ... */ }

// Assignment operator
Variant& Variant::operator=( const Variant& that )
{
  if( this != &that )
    d_stored_data = that.d_stored_data;

  return *this;
}

// Check if the variant is null (no stored object)
bool Variant::isNull() const
{
  return d_stored_data.size() == 0;
}

// Swap this variant with another
void Variant::swap( Variant& other )
{
  const std::string this_stored_data_copy = d_stored_data;
  
  d_stored_data = other.d_stored_data;

  other.d_stored_data = this_stored_data_copy;
}

// Clear the variant
void Variant::clear()
{
  d_stored_data.clear();
}

// Check if the variant stores a basic type
bool Variant::storesBasicType() const
{
  if( d_stored_data.size() > 1 )
  {
    return d_stored_data.find( Utility::container_start_char ) > d_stored_data.size() &&
      d_stored_data.find( Utility::container_end_char ) > d_stored_data.size();
  }
  else
    return true;
}

// Check if the variant stores a container type
bool Variant::storesContainerType() const
{
  if( d_stored_data.size() > 1 )
  {
    return (d_stored_data.find( Utility::container_start_char ) < d_stored_data.size() ||
            d_stored_data.find( Utility::container_end_char ) < d_stored_data.size());
  }
  else
    return false;
}

// Convert the variant to a bool
/*! \details If an error occurs in the conversion the success boolean
 * will be set to false (if it was passed in).
 */
bool Variant::toBool( bool* success ) const noexcept
{
  return this->toType<bool>( success );
}

// Convert the variant to a char
/*! \details If an error occurs in the conversion the success boolean
 * will be set to false (if it was passed in).
 */
char Variant::toChar( bool* success ) const noexcept
{
  return this->toType<char>( success );
}

// Convert the variant to a signed char
/*! \details If an error occurs in the conversion the success boolean
 * will be set to false (if it was passed in).
 */
signed char Variant::toSignedChar( bool* success ) const noexcept
{
  return this->toType<signed char>( success );
}

// Convert the variant to an unsigned char
/*! \details If an error occurs in the conversion the success boolean
 * will be set to false (if it was passed in).
 */
unsigned char Variant::toUnsignedChar( bool* success ) const noexcept
{
  return this->toType<unsigned char>( success );
}

// Convert the variant to an int8_t
/*! \details If an error occurs in the conversion the success boolean
 * will be set to false (if it was passed in).
 */
int8_t Variant::toInt8( bool* success ) const noexcept
{
  return this->toType<int8_t>( success );
}

// Convert the variant to an uint8_t
/*! \details If an error occurs in the conversion the success boolean
 * will be set to false (if it was passed in).
 */
uint8_t Variant::toUint8( bool* success ) const noexcept
{
  return this->toType<uint8_t>( success );
}

// Convert the variant to an int16_t
/*! \details If an error occurs in the conversion the success boolean
 * will be set to false (if it was passed in).
 */
int16_t Variant::toInt16( bool* success ) const noexcept
{
  return this->toType<int16_t>( success );
}

// Convert the variant to a uint16_t
/*! \details If an error occurs in the conversion the success boolean
 * will be set to false (if it was passed in).
 */
uint16_t Variant::toUint16( bool* success ) const noexcept
{
  return this->toType<uint16_t>( success );
}

// Convert the variant to a int32_t
/*! \details If an error occurs in the conversion the success boolean
 * will be set to false (if it was passed in).
 */
int32_t Variant::toInt32( bool* success ) const noexcept
{
  return this->toType<int32_t>( success );
}

// Convert the variant to a uint32_t
/*! \details If an error occurs in the conversion the success boolean
 * will be set to false (if it was passed in).
 */
uint32_t Variant::toUint32( bool* success ) const noexcept
{
  return this->toType<uint32_t>( success );
}

// Convert the variant to a short
/*! \details If an error occurs in the conversion the success boolean
 * will be set to false (if it was passed in).
 */
short Variant::toShort( bool* success ) const noexcept
{
  return this->toType<short>( success );
}

// Convert the variant to an unsigned short
/*! \details If an error occurs in the conversion the success boolean
 * will be set to false (if it was passed in).
 */
unsigned short Variant::toUnsignedShort( bool* success ) const
{
  return this->toType<unsigned short>( success );
}

// Convert the variant to an int
/*! \details If an error occurs in the conversion the success boolean
 * will be set to false (if it was passed in).
 */
int Variant::toInt( bool* success ) const noexcept
{
  return this->toType<int>( success );
}

// Convert the variant to an unsigned int
/*! \details If an error occurs in the conversion the success boolean
 * will be set to false (if it was passed in).
 */
unsigned int Variant::toUnsignedInt( bool* success ) const noexcept
{
  return this->toType<unsigned int>( success );
}

// Convert the variant to a long
/*! \details If an error occurs in the conversion the success boolean
 * will be set to false (if it was passed in).
 */
long Variant::toLong( bool* success ) const noexcept
{
  return this->toType<long>( success );
}

// Convert the variant to an unsigned long
/*! \details If an error occurs in the conversion the success boolean
 * will be set to false (if it was passed in).
 */
unsigned long Variant::toUnsignedLong( bool* success ) const noexcept
{
  return this->toType<unsigned long>( success );
}

// Convert the variant to a long long
/*! \details If an error occurs in the conversion the success boolean
 * will be set to false (if it was passed in).
 */
long long Variant::toLongLong( bool* success ) const noexcept
{
  return this->toType<long long>( success );
}

// Convert the variant to an unsigned long long
/*! \details If an error occurs in the conversion the success boolean
 * will be set to false (if it was passed in).
 */
unsigned long long Variant::toUnsignedLongLong( bool* success ) const noexcept
{
  return this->toType<unsigned long long>( success );
}

// Convert the variant to an int64_t
/*! \details If an error occurs in the conversion the success boolean
 * will be set to false (if it was passed in).
 */
int64_t Variant::toInt64( bool* success ) const noexcept
{
  return this->toType<int64_t>( success );
}

// Conver the variant to an uint64_t
/*! \details If an error occurs in the conversion the success boolean
 * will be set to false (if it was passed in).
 */
uint64_t Variant::toUint64( bool* success ) const noexcept
{
  return this->toType<uint64_t>( success );
}

// Convert the variant to a float
/*! \details If an error occurs in the conversion the success boolean
 * will be set to false (if it was passed in).
 */
float Variant::toFloat( bool* success ) const noexcept
{
  return this->toType<float>( success );
}

// Convert the variant to a double
/*! \details If an error occurs in the conversion the success boolean
 * will be set to false (if it was passed in).
 */
double Variant::toDouble( bool* success ) const noexcept
{
  return this->toType<double>( success );
}

// Convert the variant to string
/*! \details If an error occurs in the conversion the success boolean
 * will be set to false (if it was passed in).
 */
std::string Variant::toString( bool* success ) const noexcept
{
  if( success )
    *success = true;
  
  return d_stored_data;
}

// Convert the variant to a lowercase string
/*! \details If an error occurs in the conversion the success boolean
 * will be set to false (if it was passed in).
 */
std::string Variant::toLowerString( bool* success ) const noexcept
{
  if( success )
    *success = true;
  
  return boost::algorithm::to_lower_copy( d_stored_data );
}

// Convert the variant to an uppercase string
/*! \details If an error occurs in the conversion the success boolean
 * will be set to false (if it was passed in).
 */
std::string Variant::toUpperString( bool* success ) const noexcept
{
  if( success )
    *success = true;
  
  return boost::algorithm::to_upper_copy( d_stored_data );
}

// Convert the variant to a vector
/*! \details If an error occurs in the conversion the success boolean
 * will be set to false (if it was passed in).
 */
VariantVector Variant::toVector( bool* success ) const noexcept
{
  return this->toContainerType<VariantVector>( success );
}

// Convert the variant to a list
/*! \details If an error occurs in the conversion the success boolean
 * will be set to false (if it was passed in).
 */
VariantList Variant::toList( bool* success ) const noexcept
{
  return this->toContainerType<VariantList>( success );
}

// Convert the variant to forward list
/*! \details If an error occurs in the conversion the success boolean
 * will be set to false (if it was passed in).
 */
VariantForwardList Variant::toForwardList( bool* success ) const noexcept
{
  return this->toContainerType<VariantForwardList>( success );
}

// Convert the variant to a deque
/*! \details If an error occurs in the conversion the success boolean
 * will be set to false (if it was passed in).
 */
VariantDeque Variant::toDeque( bool* success ) const noexcept
{
  return this->toContainerType<VariantDeque>( success );
}

// Convert the variant to a map
/*! \details If an error occurs in the conversion the success boolean
 * will be set to false (if it was passed in).
 */
VariantMap Variant::toMap( bool* success ) const noexcept
{
  return this->toType<VariantMap>( success );
}

// Compactify the underlying data
/*! \details This method will eliminate all white space characters from
 * the stored data string. If the stored type is a string, calling this method
 * will change the stored string.
 */
Variant& Variant::compactify()
{
  d_stored_data.erase( std::remove_if(d_stored_data.begin(), d_stored_data.end(), std::bind<bool>(&std::isspace<char>, std::placeholders::_1, std::locale())), d_stored_data.end() );

  return *this;
}

// Inequality operator
bool Variant::operator!=( const Variant& other ) const
{
  return d_stored_data != other.d_stored_data;
}

// Equality operator
bool Variant::operator==( const Variant& other ) const
{
  return d_stored_data == other.d_stored_data;
}

// Inline addition operator
/*! \details This method will append a sequence element to the stored variant
 * data. If the stored variant data is not a sequence type, it will be
 * converted to a sequence type.
 */ 
Variant& Variant::operator+=( const Variant& other )
{
  VariantList list = this->toList();

  *this += other.toList();

  return *this;
}

// Inline addition operator
/*! \details This inline addition overload is primarily for std::string
 * interfaces (it is a required by the Utility::PropertyTree).
 */
Variant& Variant::operator+=( const char& string_element )
{
  d_stored_data += string_element;

  return *this;
}

// Implicit conversion to std::string
Variant::operator std::string() const
{
  return d_stored_data;
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_Variant.cpp
//---------------------------------------------------------------------------//
