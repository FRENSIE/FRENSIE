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
  bool energyGridValid( const Array& energy_grid );

  // Test preconditions for values in array greater than zero
  template<typename Array>
  bool valuesGreaterThanZero( const Array& values );

  // Test preconditions for values in array greater than or equal to zero
  template<typename Array>
  bool valuesGreaterThanOrEqualToZero( const Array& values );

  // Test preconditions for values in array less than one
  template<typename Array>
  bool valuesLessThanOne( const Array& values );

  // Test preconditions for values in array less than or equal to one
  template<typename Array>
  bool valuesLessThanOrEqualToOne( const Array& values );

  // Test if a value is less than or equal to zero
  bool isValueLessThanOrEqualToZero( const double value );

  // Test if a value is less than zero
  bool isValueLessThanZero( const double value );

  // Test if a value is greater than one
  bool isValueGreaterThanOne( const double value );

  // Test if a value is greater than or equal to one
  bool isValueGreaterThanOrEqualToOne( const double value );

  // Test if a value is less than minus one
  bool isValueLessThanMinusOne( const double value );

  // Test if the TwoDInterpPolicy is valid
  bool isTwoDInterpPolicyValid( const std::string value );

  // Test if the TwoDGridPolicy is valid
  bool isTwoDGridPolicyValid( const std::string value );

  // Test if the InterpPolicy is valid
  bool isInterpPolicyValid( const std::string value );

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
