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

// The invalid cell handle
auto Navigator::invalidCellHandle() -> InternalCellHandle
{
  return 0;
}

// The invalid surface handle
auto Navigator::invalidSurfaceHandle() -> InternalSurfaceHandle
{
  return 0;
}
  
} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geomtry_Navigator.cpp
//---------------------------------------------------------------------------//
