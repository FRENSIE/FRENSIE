//---------------------------------------------------------------------------//
//!
//! \file   Utility_Variant_def.hpp
//! \author Alex Robinson,
//! \brief  The variant template definitions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_VARIANT_DEF_HPP
#define UTILITY_VARIANT_DEF_HPP

// FRENSIE Includes
#include "Utility_LoggingMacros.hpp"

namespace Utility{

// Constructor
/*! \details To successfully convert the object of type T a Utility::Variant a 
 * specialization of the Utility::ToStringTraits class for type T
 * must exist.
 */
template<typename T>
Variant::Variant( const T& object )
  : d_stored_data( Utility::toString(object) )
{ /* ... */ }

// Create a variant
template<typename T>
Variant Variant::fromValue( const T& object )
{
  return Variant( object );
}

// Set the value of the variant
template<typename T>
void Variant::setValue( const T& object )
{
  d_stored_data = Utility::toString( object );
}

// Check if the variant can be converted to the type of interest
template<typename T>
bool Variant::canConvert() const
{
  try{
    Utility::fromString<T>( d_stored_data );
  }
  catch( ... )
  {
    return false;
  }

  return true;
}

// Convert the variant to the desired type
/*! \details If the conversion fails a std::runtime_error (or class derived
 * from it) will be thrown.
 */
template<typename T>
void Variant::convert( T& object ) const
{
  object = Utility::fromString<T>( d_stored_data );
}

// Convert the variant to the desired type
/*! \details To successfully convert the Variant object to an object of type T
 * a specialization of the Utility::FromStringTraits class for type T
 * must exist. If an error occurs in the conversion the success boolean
 * will be set to false (if it was passed in).
 */
template<typename T>
inline T Variant::toType( bool* success ) const
{
  // Initialize the  success variable
  if( success )
    *success = true;

  T converted_value;

  try{
    converted_value = Utility::fromString<T>( d_stored_data );
  }
  catch( ... )
  {
    // Failure to convert the variant to the desired type
    if( success )
      *success = false;
  }

  return converted_value;
}

// Cast the variant to the desired type
/*! \details If the cast fails a std::runtime_error (or class derived
 * from it) will be thrown.
 */
template<typename T>
T variant_cast( const Variant& variant )
{
  T object;

  variant.convert( object );

  return object;
}
  
} // end Utility namespace

#endif // end UTILITY_VARIANT_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_Variant_def.hpp
//---------------------------------------------------------------------------//
