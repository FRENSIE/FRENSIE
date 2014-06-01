//---------------------------------------------------------------------------//
//!
//! \file   Utility_XMLCompatibleObject.hpp
//! \author Alex Robinson
//! \brief  XML compatible object base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_XML_COMPATIBLE_OBJECT_HPP
#define UTILITY_XML_COMPATIBLE_OBJECT_HPP

// Std Lib Includes
#include <string>
#include <iostream>
#include <sstream>

// Teuchos Includes
#include <Teuchos_TypeNameTraits.hpp>

namespace Utility{

//! The base class for XML compatible objects
template<typename DerivedType>
class XMLCompatibleObject
{

public:

  //! Constructor
  XMLCompatibleObject();
  
  //! Destructor
  virtual ~XMLCompatibleObject()
  { /* ... */ }

  //! Method for placing the object in an output stream
  virtual void toStream( std::ostream& os ) const = 0;

  //! Method for initializing the object from an input stream
  virtual void fromStream( std::istream& is ) = 0;

  //! Method for testing if two objects are equivalent
  virtual bool isEqual( const DerivedType& other ) const = 0;

  //! Method for placing the object in a string
  void toString( std::string& obj_string ) const;

  //! Method for initializing an object from a string
  void fromString( const std::string& obj_string );
};

// Method for placing the object in a string
template<typename DerivedType>
inline void XMLCompatibleObject<DerivedType>::toString( 
					        std::string& obj_string ) const
{
  std::ostringstream oss;

  this->toStream( oss );

  obj_string = oss.str();
}

// Method for initializing an object from a string
template<typename DerivedType>
inline void XMLCompatibleObject<DerivedType>::fromString( 
						const std::string& obj_string )
{
  std::istringstream iss( obj_string );

  this->fromStream( iss );
}

//! Stream operator for placing an object in an output stream
template<typename DerivedType>
inline std::ostream& operator<<( 
			 std::ostream &os,
			 const Utility::XMLCompatibleObject<DerivedType> &obj )
{
  obj.toStream( os );
}

//! Stream operator for initializing an object from a stream
template<typename DerivedType>
inline std::istream& operator>>( 
			       std::istream &is,
			       Utility::XMLCompatibleObject<DerivedType> &obj )
{
  obj.fromStream( is );
}

//! Method for testing if two objects are equal
template<typename DerivedTypeA, typename DerivedTypeB>
inline bool operator==(const Utility::XMLCompatibleObject<DerivedTypeA> &obj_a,
		       const Utility::XMLCompatibleObject<DerivedTypeB> &obj_b)
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

#include "Utility_XMLCompatibleObject_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_XML_COMPATIBLE_OBJECT_HPP

//---------------------------------------------------------------------------//
// end Utility_XMLCompatibleObject.hpp
//---------------------------------------------------------------------------//
