//---------------------------------------------------------------------------//
//!
//! \file   Geometry_Navigator.cpp
//! \author Alex Robinson
//! \brief  The geometry navigator base class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "Geometry_Navigator.hpp"

namespace Geometry{

// Constructor
/*! \details The advance callback will be called immediately after an advance
 * has occurred.
 */
Navigator::Navigator( const AdvanceCompleteCallback& advance_complete_callback )

  : d_on_advance_complete( advance_complete_callback )
{ /* ... */ }

// Copy constructor
Navigator::Navigator( const Navigator& other )
  : d_on_advance_complete( other.d_on_advance_complete )
{ /* ... */ }

// The invalid cell id
auto Navigator::invalidCellId() -> EntityId
{
  return 0;
}

// The invalid surface id
auto Navigator::invalidSurfaceId() -> EntityId
{
  return 0;
}

} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geomtry_Navigator.cpp
//---------------------------------------------------------------------------//
