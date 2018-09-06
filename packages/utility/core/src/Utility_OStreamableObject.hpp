//---------------------------------------------------------------------------//
//!
//! \file   Utility_OStreamableObject.hpp
//! \author Alex Robinson
//! \brief  Output streamable object base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_OSTREAMABLE_OBJECT_HPP
#define UTILITY_OSTREAMABLE_OBJECT_HPP

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"

namespace Utility{

/*! The base class for output streamable objects
 * 
 * All classes that inherit from this base class can be converted to a string
 * or placed in a stream using the Utility::toString and the Utility::toStream
 * methods respectively (a partial specialization of the 
 * Utility::ToStringTraits class is provided for this base class).
 */
class OStreamableObject
{
public:

  //! Constructor
  OStreamableObject()
  { /* ... */ }
  
  //! Destructor
  virtual ~OStreamableObject()
  { /* ... */ }

  //! Method for placing the object in an output stream
  virtual void toStream( std::ostream& os ) const = 0;

protected:

  //! Add data to the stream
  template<typename... Types>
  void toStreamImpl( std::ostream& os, const Types&... data ) const;
};

/*! Specialization of Utility::ToStringTraits for Utility::OStreamable object
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<OStreamableObject>
{
  //! Convert a Utility::OStreamableObject to a string
  static inline std::string toString( const OStreamableObject& obj )
  {
    std::ostringstream oss;

    ToStringTraits<OStreamableObject>::toStream( oss, obj );

    return oss.str();
  }

  //! Place the Utility::OStreamableObject in a stream
  static inline void toStream( std::ostream& os, const OStreamableObject& obj )
  { obj.toStream( os ); }
};

/*! \brief Partial specialization of Utility::ToStringTraits for types that
 * inherit from Utility::OStreamableObject
 * \ingroup to_string_traits
 */
template<typename DerivedType>
struct ToStringTraits<DerivedType,typename std::enable_if<std::is_base_of<OStreamableObject,DerivedType>::value>::type> : public ToStringTraits<OStreamableObject>
{ /* ... */ };
  
} // end Utility namespace

namespace std{

//! Place a Utility::OStreamableObject in a stream
inline std::ostream& operator<<( std::ostream& os,
                                 const Utility::OStreamableObject& obj )
{
  Utility::toStream( os, obj );

  return os;
}
  
} // end std namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_OStreamableObject_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_OSTREAMABLE_OBJECT_HPP

//---------------------------------------------------------------------------//
// end Utility_OStreamableObject.hpp
//---------------------------------------------------------------------------//
