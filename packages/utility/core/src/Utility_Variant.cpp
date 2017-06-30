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

// FRENSIE Includes
#include "Utility_Variant.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Default constructor
Variant::Variant()
  : d_stored_data()
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
bool Variant::isNull()
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

// Extract variant element string
std::string FromStringTraits<Variant>::extractVariantElementString(
                                                    std::istream& is,
                                                    const std::string& delims )
{
  // Count the number of '{' characters that occur before any other
  // characters (other than space characters)
  size_t num_start_delim_chars = 0;
  
  std::string sub_container_string;
  
  bool done = false;
  
  while( !done )
  {
    char string_element;
    is.get( string_element );
      
    TEST_FOR_EXCEPTION( is.eof(),
                        Utility::StringConversionException,
                        "Unable to get the string element (EOF reached "
                        "unexpectedly)!" );
    
    TEST_FOR_EXCEPTION( !is,
                        Utility::StringConversionException,
                        "Unable to get the string element (one or more "
                        "error flags have been set)!" );
    
    if( string_element == '{' )
      ++num_start_delim_chars;
    else if( string_element != ' ' )
      done = true;
    
    sub_container_string.push_back( string_element );
  }
    
  // Restore the stream
  if( num_start_delim_chars == 0 )
  {
    while( sub_container_string.size() > 0 )
    {
      is.putback( sub_container_string.back() );
      sub_container_string.pop_back();
    }

    // Extract a string from the stream
    Utility::fromStream( is, sub_container_string, delims );
  }
    
  // Continue reading until the correct number of consecutive end
  // deliminators are encountered
  else
  {
    // Count the number of '}' characters that occur consecutively (excluding
    // space characters)
    size_t num_end_delim_chars = 0;
    char previous_element = 'a';
    
    while( true )
    {
      char string_element;
      is.get( string_element );
      
      TEST_FOR_EXCEPTION( is.eof(),
                          Utility::StringConversionException,
                          "Unable to get the string element (EOF reached "
                          "unexpectedly)!" );
      
      TEST_FOR_EXCEPTION( !is,
                          Utility::StringConversionException,
                          "Unable to get the string element (one or more "
                          "error flags have been set)!" );
      
      if( string_element == '}' && previous_element == '}' )
        ++num_end_delim_chars;
      else if( string_element == '}' && previous_element != '}' )
      {
        num_end_delim_chars = 1;
        previous_element = '}';
      }
      else if( string_element != ' ' )
      {
        num_end_delim_chars = 0;
        previous_element = string_element;
      }

      sub_container_string.push_back( string_element );
      
      if( num_end_delim_chars == num_start_delim_chars )
        break;
    }

    return sub_container_string;
  }
}

// Extract a variant from a stream
void FromStringTraits<Variant>::fromStream( std::istream& is,
                                            Variant& obj,
                                            const std::string& delims )
{
  std::string obj_data;

  // Check if we're extracting a variant as an element of a container
  if( delims.find( "," ) < delims.size() &&
      delims.find( "}" ) < delims.size() )
  {
    obj_data =
      FromStringTraits<Variant>::extractVariantElementString( is, delims );
  }
  // Extract a string from the stream
  else
    Utility::fromStream( is, obj_data, delims );
  
  obj.setValue( obj_data );
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_Variant.cpp
//---------------------------------------------------------------------------//
