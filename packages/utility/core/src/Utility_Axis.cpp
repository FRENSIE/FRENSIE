//---------------------------------------------------------------------------//
//!
//! \file   Utility_Axis.cpp
//! \author Alex Robinson
//! \brief  Axis helper definitions.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_Axis.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

// Test if the axis name is valid
bool isValidAxisName( const std::string& axis_name )
{
  return axis_name.compare( "X" ) == 0 ||
    axis_name.compare( "Y" ) == 0 ||
    axis_name.compare( "Z" ) == 0;
}

// Convert the axis name to an Axis enum
Axis convertAxisNameToAxisEnum( const std::string& axis_name )
{
  switch( axis_name.c_str()[0] )
  {
  case 'X':
    return X_AXIS;
  case 'Y':
    return Y_AXIS;
  case 'Z':
    return Z_AXIS;
  default:
    return UNDEFINED_AXIS;
  }
}


} // end Utility namespace
//---------------------------------------------------------------------------//
// end Utility_Axis.cpp
//---------------------------------------------------------------------------//
