//---------------------------------------------------------------------------//
//!
//! \file   Geometry_TwoSpaceObject.hpp
//! \author Alex Robinson
//! \brief  TwoSpaceObject class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_TWO_SPACE_OBJECT
#define GEOMETRY_TWO_SPACE_OBJECT

namespace Geometry{

//! Types of objects that can be encountered in two space
enum TwoSpaceObjectType{
  TWO_SPACE_VECTOR,
  TWO_SPACE_MATRIX
};

//! Base class for all objects that reside in two space
class TwoSpaceObject
{

public:

  //! Constructor
  TwoSpaceObject( TwoSpaceObjectType object_type )
  : d_object_type( object_type )
  { /* ... */ }

  //! Destructor
  virtual ~TwoSpaceObject()
  { /* ... */ }

  //! Returns the type of two space object
  TwoSpaceObject objectType()
  { return d_object_type; }

private:

  TwoSpaceObjectType d_object_type;
};

} // end Geometry namespace

#endif // end GEOMETRY_TWO_SPACE_OBJECT

//---------------------------------------------------------------------------//
// end Geometry_TwoSpaceObject.hpp
//---------------------------------------------------------------------------//
