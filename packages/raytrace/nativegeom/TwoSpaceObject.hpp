//---------------------------------------------------------------------------//
//!
//! \file   TwoSpaceObject.hpp
//! \author Alex Robinson
//! \brief  TwoSpaceObject class declaration
//!
//---------------------------------------------------------------------------//

#ifndef TWO_SPACE_OBJECT
#define TWO_SPACE_OBJECT

namespace FACEMC{

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

} // end FACEMC namespace

#endif // end TWO_SPACE_OBJECT

//---------------------------------------------------------------------------//
// end TwoSpaceObject.hpp
//---------------------------------------------------------------------------//
