//---------------------------------------------------------------------------//
//!
//! \file   Utility_ParameterListCompatibleObject.hpp
//! \author Alex Robinson
//! \brief  ParameterList compatible object base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_PARAMETER_LIST_COMPATIBLE_OBJECT_HPP
#define UTILITY_PARAMETER_LIST_COMPATIBLE_OBJECT_HPP

// Std Lib Includes
#include <string>
#include <iostream>
#include <sstream>

// Teuchos Includes
#include <Teuchos_TypeNameTraits.hpp>

// FRENSIE Includes
#include "Utility_SerializableObject.hpp"

namespace Utility{

//! The base class for ParameterList compatible objects
template<typename DerivedType>
class ParameterListCompatibleObject : public SerializableObject
{

public:

  //! Constructor
  ParameterListCompatibleObject();

  //! Destructor
  virtual ~ParameterListCompatibleObject()
  { /* ... */ }

  //! Method for placing the object in an output stream
  virtual void toStream( std::ostream& os ) const = 0;

  //! Method for initializing the object from an input stream
  virtual void fromStream( std::istream& is ) = 0;

  //! Method for testing if two objects are equivalent
  virtual bool isEqual( const DerivedType& other ) const = 0;

  //! Pack the data in the container into a string
  std::string packDataInString() const;

  //! Unpack the data from a string and store in the container
  void unpackDataFromString( const std::string& packed_string );
};

// Method for placing the object in a string
template<typename DerivedType>
inline std::string ParameterListCompatibleObject<DerivedType>::packDataInString() const
{
  std::ostringstream oss;

  this->toStream( oss );

  return oss.str();
}

// Method for initializing an object from a string
template<typename DerivedType>
inline void ParameterListCompatibleObject<DerivedType>::unpackDataFromString(
					     const std::string& packed_string )
{
  std::istringstream iss( packed_string );

  this->fromStream( iss );
}

//! Stream operator for placing an object in an output stream
template<typename DerivedType>
inline std::ostream& operator<<(
	       std::ostream &os,
	       const Utility::ParameterListCompatibleObject<DerivedType> &obj )
{
  obj.toStream( os );
}

//! Stream operator for initializing an object from a stream
template<typename DerivedType>
inline std::istream& operator>>(
			       std::istream &is,
			       Utility::ParameterListCompatibleObject<DerivedType> &obj )
{
  obj.fromStream( is );
}

//! Method for testing if two objects are equal
template<typename DerivedTypeA, typename DerivedTypeB>
inline bool operator==(const Utility::ParameterListCompatibleObject<DerivedTypeA> &obj_a,
		       const Utility::ParameterListCompatibleObject<DerivedTypeB> &obj_b)
{
  if( Teuchos::TypeNameTraits<DerivedTypeA>::name() ==
      Teuchos::TypeNameTraits<DerivedTypeB>::name() )
  {
    const DerivedTypeA& obj_b_derived =
      dynamic_cast<const DerivedTypeA&>( obj_b );

    return obj_a.isEqual( obj_b_derived );
  }
  else
    return false;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "Utility_ParameterListCompatibleObject_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_PARAMETER_LIST_COMPATIBLE_OBJECT_HPP

//---------------------------------------------------------------------------//
// end Utility_ParameterListCompatibleObject.hpp
//---------------------------------------------------------------------------//
