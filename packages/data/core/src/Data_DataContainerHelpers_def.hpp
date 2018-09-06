//---------------------------------------------------------------------------//
//!
//! \file   Data_DataContainerHelpers_def.hpp
//! \author Luke Kersting
//! \brief  The data container helpers def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_SortAlgorithms.hpp"
#include "Utility_DesignByContract.hpp"

namespace Data{

// Test preconditions for energy grids
template<typename Array>
inline bool energyGridValid( const Array& energy_grid )
{
  return( energy_grid.size() > 1 &&
          Utility::Sort::isSortedAscending( energy_grid.begin(),
                                            energy_grid.end() ) &&
          energy_grid.front() > 0.0 );
}

// Test preconditions for values in array greater than zero
template<typename Array>
inline bool valuesGreaterThanZero( const Array& values )
{
  return std::find_if( values.begin(),
                       values.end(),
                       isValueLessThanOrEqualToZero ) == values.end();
}

// Test preconditions for values in array greater than zero
template<typename Array>
inline bool valuesGreaterThanOrEqualToZero( const Array& values )
{
  return std::find_if( values.begin(),
                       values.end(),
                       isValueLessThanZero ) == values.end();
}

// Test preconditions for values in array less than one
template<typename Array>
inline bool valuesLessThanOne( const Array& values )
{
  return std::find_if( values.begin(),
                       values.end(),
                       isValueGreaterThanOrEqualToOne ) == values.end();
}

// Test preconditions for values in array less than one
template<typename Array>
inline bool valuesLessThanOrEqualToOne( const Array& values )
{
  return std::find_if( values.begin(),
                       values.end(),
                       isValueGreaterThanOne ) == values.end();
}

//// Test if a value is less than or equal to zero
//bool isValueLessThanOrEqualToZero( const double value )
//{
//  return value <= 0.0;
//}

//// Test if a value is less than zero
//bool isValueLessThanZero( const double value )
//{
//  return value < 0.0;
//}

//// Test if a value is greater than one
//bool isValueGreaterThanOne( const double value )
//{
//  return value > 1.0;
//}

//// Test if a value is greater than or equal to one
//bool isValueGreaterThanOrEqualToOne( const double value )
//{
//  return value >= 1.0;
//}

//// Test if a value is less than -1.0
//bool isValueLessThanMinusOne( const double value )
//{
//  return value < -1.0;
//}

//// Test if the TwoDInterpPolicy is valid
//bool isTwoDInterpPolicyValid( const std::string value )
//{
//  if ( value == "LinLinLin" || value == "LinLinLog" || value == "LinLogLin" ||
//       value == "LogLinLin" || value == "LinLogLog" || value == "LogLogLin" ||
//       value == "LogLinLog" || value == "LogLogLog" )
//    return true;
//  else
//    return false;
//}

//// Test if the InterpPolicy is valid
//bool isInterpPolicyValid( const std::string value )
//{
//  if ( value == "LinLin" || value == "LinLog" || value == "LogLin" ||
//       value == "LogLog" || value == "Histogram" || value == "Gamow" )
//    return true;
//  else
//    return false;
//}

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_DataContainerHelpers.cpp
//---------------------------------------------------------------------------//

