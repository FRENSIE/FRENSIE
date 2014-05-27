//---------------------------------------------------------------------------//
//!
//! \file   Utility_Axis.hpp
//! \author Alex Robinson
//! \brief  Axis and Axis direction enumeration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_AXIS_HPP
#define UTILITY_AXIS_HPP

namespace Utility{

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

} // end Utility namespace

#endif // end UTILITY_AXIS_HPP

//---------------------------------------------------------------------------//
// end Utility_Axis.hpp
//---------------------------------------------------------------------------//
