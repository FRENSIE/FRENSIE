//---------------------------------------------------------------------------//
//!
//! \file   Axis.hpp
//! \author Alex Robinson
//! \brief  Axis and Axis direction enumeration.
//!
//---------------------------------------------------------------------------//

#ifndef AXIS_HPP
#define AXIS_HPP

namespace FACEMC{

//! Enum for specifying which axis to align eigenvectors with
enum Axis{
  X_AXIS,
  Y_AXIS,
  Z_AXIS,
  UNDEFINED_AXIS
};

//! Direction of the axis vector that will be created
enum AxisVectorDirection{
  POSITIVE_DIRECTION,
  NEGATIVE_DIRECTION
};

} // end FACEMC namespace

#endif // end AXIS_HPP

//---------------------------------------------------------------------------//
// end Axis.hpp
//---------------------------------------------------------------------------//
