//---------------------------------------------------------------------------//
//!
//! \file   Utility_SerializableObject.hpp
//! \author Alex Robinson
//! \brief  Serializable object base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SERIALIZABLE_OBJECT_HPP
#define UTILITY_SERIALIZABLE_OBJECT_HPP

// Std Lib Includes
#include <string>

namespace Utility{

//! The base class for serializable objects
class SerializableObject
{

public:

  //! Pack the data in the container into a string
  virtual std::string packDataInString() const = 0;

  //! Unpack the data from a string and store in the container
  virtual void unpackDataFromString( const std::string& packed_string ) = 0;
};

} // end Utility namespace

#endif // end UTILITY_SERIALIZABLE_OBJECT_HPP

//---------------------------------------------------------------------------//
// end Utility_SerializableObject.hpp
//---------------------------------------------------------------------------//
