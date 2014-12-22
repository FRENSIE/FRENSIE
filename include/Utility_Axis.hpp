//---------------------------------------------------------------------------//
//!
//! \file   Utility_Axis.hpp
//! \author Alex Robinson
//! \brief  Axis enumerations and helper declarations.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_AXIS_HPP
#define UTILITY_AXIS_HPP

// Std Lib Includes
#include <string>

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

//! Test if the axis name is valid
bool isValidAxisName( const std::string& axis_name );

//! Convert the axis name to an Axis enum
Axis convertAxisNameToAxisEnum( const std::string& axis_name );

} // end Utility namespace

#endif // end UTILITY_AXIS_HPP

//---------------------------------------------------------------------------//
// end Utility_Axis.hpp
//---------------------------------------------------------------------------//
