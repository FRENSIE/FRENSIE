//---------------------------------------------------------------------------//
//!
//! \file   Utility_StandardSerializationObject.hpp
//! \author Alex Robinson
//! \brief  Standard serializable object base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_STANDARD_SERIALIZABLE_OBJECT_HPP
#define UTILITY_STANDARD_SERIALIZABLE_OBJECT_HPP

// FRENSIE Includes
#include "Utility_SerializableObject.hpp"

namespace Utility{

//! The base class for standard serializable objects
template<typename DerivedType, bool packing_allowed=true>
class StandardSerializableObject : public virtual SerializableObject
{

public:

  // Add the packDataInString member function to the public interface
};

//! The base class for standard serializable objects
template<typename DerivedType>
class StandardSerializableObject<DerivedType,false> : public virtual SerializableObject
{

public:

  //! Unpack the data from a string and store in the container
  void unpackDataFromString( const std::string& packed_string );

protected:

  //! Pack the data in the container into a string
  std::string packDataInString() const;
};

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_StandardSerializableObject_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_STANDARD_SERIALIZABLE_OBJECT_HPP

//---------------------------------------------------------------------------//
// end Utility_StandardSerializableObject.hpp
//---------------------------------------------------------------------------//
