//---------------------------------------------------------------------------//
//!
//! \file   Data_DataContainerHelpers.cpp
//! \author Luke Kersting
//! \brief  The data container helpers def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_DataContainerHelpers.hpp"

namespace Data{

// Test if a value is less than or equal to zero
bool isValueLessThanOrEqualToZero( const double value )
{
  return value <= 0.0;
}

// Test if a value is less than zero
bool isValueLessThanZero( const double value )
{
  return value < 0.0;
}

// Test if a value is greater than one
bool isValueGreaterThanOne( const double value )
{
  return value > 1.0;
}

// Test if a value is greater than or equal to one
bool isValueGreaterThanOrEqualToOne( const double value )
{
  return value >= 1.0;
}

// Test if a value is less than -1.0
bool isValueLessThanMinusOne( const double value )
{
  return value < -1.0;
}

// Test if the TwoDInterpPolicy is valid
bool isTwoDInterpPolicyValid( const std::string value )
{
  if ( value == "Lin-Lin-Lin" || value == "Lin-Lin-Log" || value == "Lin-Log-Lin" ||
       value == "Log-Lin-Lin" || value == "Lin-Log-Log" || value == "Log-Log-Lin" ||
       value == "Log-Lin-Log" || value == "Log-Log-Log" )
    return true;
  else
    return false;
}

// Test if the TwoDGridPolicy is valid
bool isTwoDGridPolicyValid( const std::string value )
{
  if ( value == "Unit-base Correlated" || value == "Correlated" ||
       value == "Unit-base" || value == "Direct" )
    return true;
  else
    return false;
}

// Test if the InterpPolicy is valid
bool isInterpPolicyValid( const std::string value )
{
  if ( value == "Lin-Lin" || value == "Lin-Log" || value == "Log-Lin" ||
       value == "Log-Log" || value == "Histogram" || value == "Gamow" )
    return true;
  else
    return false;
}

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_DataContainerHelpers.cpp
//---------------------------------------------------------------------------//

