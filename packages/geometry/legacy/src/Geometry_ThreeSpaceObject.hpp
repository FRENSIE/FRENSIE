//---------------------------------------------------------------------------//
//!
//! \file   Geometry_ThreeSpaceObject.hpp
//! \author Alex Robinson
//! \brief  ThreeSpaceObject class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_THREE_SPACE_OBJECT_HPP
#define GEOMETRY_THREE_SPACE_OBJECT_HPP

namespace Geometry{

//! Types of objects that can be encountered in three space
enum ThreeSpaceObjectType{
  THREE_SPACE_POINT,
  THREE_SPACE_VECTOR,
  THREE_SPACE_MATRIX,
  THREE_SPACE_SURFACE,
  THREE_SPACE_POLYGON,
  THREE_SPACE_CELL
};

//! Base class for all objects that reside in three space
class ThreeSpaceObject
{

public:

  //! Constructor
  ThreeSpaceObject( ThreeSpaceObjectType object_type )
  : d_object_type( object_type )
  { /* ... */ }

  //! Destructor
  virtual ~ThreeSpaceObject()
  { /* ... */ }

  //! Returns the type of three space object
  ThreeSpaceObjectType objectType()
  { return d_object_type; }

private:

  ThreeSpaceObjectType d_object_type;
};

} // end Geometry namespace

#endif // end GEOMETRY_THREE_SPACE_OBJECT_HPP

//---------------------------------------------------------------------------//
// end Geometry_ThreeSpaceObject.hpp
//---------------------------------------------------------------------------//
