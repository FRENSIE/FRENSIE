//---------------------------------------------------------------------------//
//!
//! \file   Geometry_PointLocation.hpp
//! \author Alex Robinson
//! \brief  Point location (relative to a cell) enumeration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_POINT_LOCATION_HPP
#define GEOMETRY_POINT_LOCATION_HPP

namespace Geometry{

//! Point location (relative to a cell) enumeration
enum PointLocation{
  POINT_ON_CELL,
  POINT_OUTSIDE_CELL,
  POINT_INSIDE_CELL
};

} // end Geometry namespace

#endif // end GEOMETRY_POINT_LOCATION_HPP

//---------------------------------------------------------------------------//
// end Geometry_PointLocation.hpp
//---------------------------------------------------------------------------//
