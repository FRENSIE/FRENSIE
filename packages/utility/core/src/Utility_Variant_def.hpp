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

namespace Details{

//! Convert helper class
template<typename T, typename Enabled>
struct ConvertHelper
{
  //! Check if a Utility::Variant can be converted to the desired type
  static inline bool canConvert( const Utility::Variant& variant )
  {
    try{
      Utility::fromString<T>( variant.d_stored_data );
    }
    catch( ... )
    {
      return false;
    }

    return true;
  }

  //! Convert a Utility::Variant to the desired type (safe)
  static inline T safeConvert( const Utility::Variant& variant,
                               bool* success )
  {
    // Initialize the success variable
    if( success )
      *success = true;

    T converted_value;

    try{
      converted_value = Utility::fromString<T>( variant.d_stored_data );
    }
    catch( ... )
    {
      // Failure to convert the variant to the desired type
      if( success )
        *success = false;
    }

    return converted_value;
  }

  //! Convert a Utility::Variant to the desired type
  static inline void convert( const Utility::Variant& variant, T& object )
  { object = Utility::fromString<T>( variant.d_stored_data ); }
};

//! Convert helper class specialization for containers of variants
template<typename T>
struct ConvertHelper<T,typename std::enable_if<std::is_same<typename T::value_type,Utility::Variant>::value>::type>
{
  //! Check if a Utility::Variant can be converted to the desired type
  static inline bool canConvert( const Utility::Variant& variant )
  { return true; }

  //! Convert a Utility::Variant to the desired type (safe)
  static inline T safeConvert( const Utility::Variant& variant,
                               bool* success )
  {
    // Initialize the success variable
    if( success )
      *success = true;

    T converted_container;
    
    try{
      converted_container =
        Utility::fromString<T>( variant.d_stored_data );
    }
    // Failure to convert the variant to the desired container type - add this
    // variant to the container
    catch( ... )
    {
      converted_container = T({variant});
    }

    return converted_container;
  }

  //! Convert a Utility::Variant to the desired type
  static inline void convert( const Utility::Variant& variant, T& object )
  { object = ConvertHelper<T,typename std::enable_if<std::is_same<typename T::value_type,Utility::Variant>::value>::type>::safeConvert( variant, NULL ); }
};
  
} // end Details namespace

// Constructor
/*! \details To successfully convert the object of type T a Utility::Variant a 
 * specialization of the Utility::ToStringTraits class for type T
 * must exist.
 */
template<typename T>
Variant::Variant( const T& object )
  : d_stored_data( Utility::toString(object) )
{ /* ... */ }

// General assignment operator
/*! \details To successfully convert the object of type T a Utility::Variant a 
 * specialization of the Utility::ToStringTraits class for type T
 * must exist.
 */
template<typename T>
Variant& Variant::operator=( const T& that )
{
  d_stored_data = Utility::toString(that);
}

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
inline bool Variant::canConvert() const
{
  return Details::ConvertHelper<T>::canConvert( *this );
}

// Convert the variant to the desired type
/*! \details If the conversion fails a std::runtime_error (or class derived
 * from it) will be thrown.
 */
template<typename T>
inline void Variant::convert( T& object ) const
{
  Details::ConvertHelper<T>::convert( *this, object );
}

// Convert the variant to the desired type
/*! \details To successfully convert the Variant object to an object of type T
 * a specialization of the Utility::FromStringTraits class for type T
 * must exist. If an error occurs in the conversion the success boolean
 * will be set to false (if it was passed in).
 */
template<typename T>
inline T Variant::toType( bool* success ) const noexcept
{
  return Details::ConvertHelper<T>::safeConvert( *this, success );
}

// Convert the variant to a general container of variants
template<typename Container>
typename std::enable_if<std::is_same<typename Container::value_type,Utility::Variant>::value,Container>::type
Variant::toContainerType( bool* success ) const noexcept
{
  return Details::ConvertHelper<Container>::safeConvert( *this, success );
}

// Inline addition operator
template<template<typename,typename...> class STLCompliantSequenceContainer>
Variant& Variant::operator+=( const STLCompliantSequenceContainer<Variant>& other )
{
  VariantList list = this->toList();

  list.insert( list.end(), other.begin(), other.end() );

  *this = Variant( list );
  
  return *this;
}

// Inline addition operator
template<template<typename,typename,typename...> class STLCompliantAssociativeContainer>
Variant& Variant::operator+=( const STLCompliantAssociativeContainer<std::string,Variant>& other )
{
  VariantList list = this->toList();

  typename STLCompliantAssociativeContainer<std::string,Variant>::const_iterator
    other_it, other_end;
  other_it = other.begin();
  other_end = other.end();

  while( other_it != other_end )
  {
    list.push_back( Variant(*other_it) );
    ++other_it;
  }

  *this = Variant( list );
  
  return *this;
}

// Cast the variant to the desired type
/*! \details If the cast fails a std::runtime_error (or class derived
 * from it) will be thrown.
 */
template<typename T>
T variant_cast( const Variant& variant )
{
  T object;

  Details::ConvertHelper<T>::convert( variant, object );

  return object;
}
  
} // end Utility namespace

#endif // end UTILITY_VARIANT_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_Variant_def.hpp
//---------------------------------------------------------------------------//
