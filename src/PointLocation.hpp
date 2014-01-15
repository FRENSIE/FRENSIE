//---------------------------------------------------------------------------//
//!
//! \file   PointLocation.hpp
//! \author Alex Robinson
//! \brief  Point location (relative to a cell) enumeration 
//!
//---------------------------------------------------------------------------//

#ifndef POINT_LOCATION_HPP
#define POINT_LOCATION_HPP

namespace FACEMC{

//! Point location (relative to a cell) enumeration
enum PointLocation{
  POINT_ON_CELL,
  POINT_OUTSIDE_CELL,
  POINT_INSIDE_CELL
};

} // end FACEMC namespace

#endif // end POINT_LOCATION_HPP

//---------------------------------------------------------------------------//
// end PointLocation.hpp
//---------------------------------------------------------------------------//
