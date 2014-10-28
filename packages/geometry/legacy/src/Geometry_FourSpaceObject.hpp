//---------------------------------------------------------------------------//
//!
//! \file   Geometry_FourSpaceObject.hpp
//! \author Alex Robinson
//! \brief  FourSpaceObject class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_FOUR_SPACE_OBJECT_HPP
#define GEOMETRY_FOUR_SPACE_OBJECT_HPP

namespace Geometry{

//! Types of objects that can be encountered in four space
enum FourSpaceObjectType{
  FOUR_SPACE_VECTOR,
  FOUR_SPACE_MATRIX
};

//! Base class for all objects that reside in four space
class FourSpaceObject
{

public:

  //! Constructor
  FourSpaceObject( FourSpaceObjectType object_type )
  : d_object_type( object_type )
  { /* ... */ }

  //! Destructor
  virtual ~FourSpaceObject()
  { /* ... */ }

  //! Returns the type of four space object
  FourSpaceObjectType objectType()
  { return d_object_type; }

private:

  FourSpaceObjectType d_object_type;
};

} // end Geometry namespace

#endif // end GEOMETRY_FOUR_SPACE_OBJECT_HPP

//---------------------------------------------------------------------------//
// end Geometry_FourSpaceObject.hpp
//---------------------------------------------------------------------------//
