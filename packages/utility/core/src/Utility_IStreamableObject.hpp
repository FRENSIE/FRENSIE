//---------------------------------------------------------------------------//
//!
//! \file   Utility_IStreamableObject.hpp
//! \author Alex Robinson
//! \brief  Input streamable object base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ISTREAMABLE_OBJECT_HPP
#define UTILITY_ISTREAMABLE_OBJECT_HPP

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Utility_FromStringTraits.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

namespace Utility{

/*! The base class for input streamable objects
 *
 * All classes that inherit from this base class can be initialized using the
 * Utility::fromString method and the Utility::fromStream method 
 * (a partial specialization of the Utility::FromStringTraits class is provided
 * for this base class).
 */
class IStreamableObject
{

public:

  //! Constructor
  IStreamableObject()
  { /* ... */ }

  //! Destructor
  virtual ~IStreamableObject()
  { /* ... */ }

  //! Method for initializing the object from an input stream
  virtual void fromStream( std::istream& is, const std::string& delims ) = 0;

  //! Method for initializing the object from an input stream
  void fromStream( std::istream& is )
  { this->fromStream( is, std::string() ); }
};

/*! \brief Specialization of Utility::FromStringTraits for 
 * Utility::IStreamableObject
 * \ingroup from_string_traits
 */
template<>
struct FromStringTraits<IStreamableObject>
{
  //! Extract a Utility::StreamableObject object from a stream
  static inline void fromStream( std::istream& is,
                                 IStreamableObject& obj,
                                 const std::string& delims = std::string() )
  {
    try{
      obj.fromStream( is, delims );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                Utility::StringConversionException,
                                "Could not extract an IStreamableObject from "
                                "the stream!" );
  }
};

/*! \brief Specialization of Utility::FromStringTraits for types that 
 * inherit from Utility::IStreamableObject
 * \ingroup from_string_traits
 */
template<typename DerivedType>
struct FromStringTraits<DerivedType,typename std::enable_if<std::is_base_of<IStreamableObject,DerivedType>::value && !std::is_abstract<DerivedType>::value>::type> : public FromStringTraits<IStreamableObject>
{
  //! The type that a string will be converted to
  typedef DerivedType ReturnType;

  //! Convert the string to a Utility::StreamableObject object
  static inline ReturnType fromString( const std::string& obj_rep )
  {
    std::istringstream iss( obj_rep );

    ReturnType obj;

    FromStringTraits<DerivedType>::fromStream( iss, obj );

    return obj;
  }
};
  
} // end Utility namespace

namespace std{

//! Extract a Utility::IStreamableObject from a stream
inline std::istream& operator>>( std::istream& is,
                                 Utility::IStreamableObject& obj )
{
  Utility::fromStream( is, obj );

  return is;
}
  
} // end std namespace

#endif // end UTILITY_ISTREAMABLE_OBJECT_HPP

//---------------------------------------------------------------------------//
// end Utility_IStreambleObject.hpp
//---------------------------------------------------------------------------//
