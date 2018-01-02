//---------------------------------------------------------------------------//
//!
//! \file   Data_DataContainerHelpers.hpp
//! \author Luke Kersting
//! \brief  The data container helpers decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_DATA_CONTAINER_HELPERS_HPP
#define DATA_DATA_CONTAINER_HELPERS_HPP

// Std Lib Includes
#include <string>

// Boost Includes
#include <boost/serialization/nvp.hpp>

// FRENSIE Includes
#include "Utility_Tuple.hpp"
#include "Utility_Map.hpp"
#include "Utility_Set.hpp"
#include "Utility_Vector.hpp"

//! Macro for use with the boost serialization library
#define DATA_MAKE_NVP( archive, data_field_prefix, data_field_base_name ) \
  archive & boost::serialization::make_nvp( #data_field_base_name, data_field_prefix ## data_field_base_name )

//! Macro for use with the boost serialization library
#define DATA_MAKE_NVP_DEFAULT( archive, data_field_base_name ) \
  DATA_MAKE_NVP( archive, d_, data_field_base_name ) 

namespace Data{

  // Test preconditions for energy grids
  template<typename Array>
  void testPreconditionEnergyGrid( const Array& energy_grid );

  // Test preconditions for values in array greater than zero
  template<typename Array>
  void testPreconditionValuesGreaterThanZero( const Array& values );

  // Test preconditions for values in array greater than or equal to zero
  template<typename Array>
  void testPreconditionValuesGreaterThanOrEqualToZero( const Array& values );

  // Test if a value is less than or equal to zero
  static bool isValueLessThanOrEqualToZero( const double value );

  // Test if a value is less than zero
  static bool isValueLessThanZero( const double value );

  // Test if a value is greater than one
  static bool isValueGreaterThanOne( const double value );

  // Test if a value is less than minus one
  static bool isValueLessThanMinusOne( const double value );

} // end Data namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Data_DataContainerHelpers_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_DATA_CONTAINER_HELPERS_HPP

//---------------------------------------------------------------------------//
// end Data_DataContainerHelpers.hpp
//---------------------------------------------------------------------------//
