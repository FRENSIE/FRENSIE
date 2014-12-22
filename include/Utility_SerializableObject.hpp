//---------------------------------------------------------------------------//
//!
//! \file   Utility_SerializableObject.hpp
//! \author Alex Robinson
//! \brief  Serializable object base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SERIALIZABLE_OBJECT_HPP
#define UTILITY_SERIALIZABLE_OBJECT_HPP

namespace Utility{

//! The base class for serializable objects
class SerializableObject
{

public:

  //! Constructor
  SerializableObject()
  { /* ... */ }
  
  //! Destructor
  virtual ~SerializableObject()
  { /* ... */ }

  //! Return the storage required to serialize the object
  virtual unsigned long long getBufferSize() const = 0;

  //! Serialize the object to a char* buffer
  virtual void serialize( char* buffer ) const = 0;

  //! Deserialize the object from a char* buffer
  virtual void deserialize( const char* buffer ) = 0;
};

} // end Utility namespace

#endif // end UTILITY_SERIALIZABLE_OBJECT_HPP

//---------------------------------------------------------------------------//
// end Utility_SerializableObject.hpp
//---------------------------------------------------------------------------//
