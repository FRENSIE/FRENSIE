//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhaseSpaceDimension.hpp
//! \author Alex Robinson
//! \brief  Phase space dimension enum and helper function decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHASE_SPACE_DIMENSION_HPP
#define MONTE_CARLO_PHASE_SPACE_DIMENSION_HPP

// Std Lib Includes
#include <string>
#include <iostream>

// FRENSIE Includes
#include "Utility_SpatialDimensionType.hpp"
#include "Utility_DirectionalDimensionType.hpp"

namespace MonteCarlo{

//! The phase space dimension type enumeration
enum PhaseSpaceDimension
{
  PRIMARY_SPATIAL_DIMENSION = 0,
  SECONDARY_SPATIAL_DIMENSION,
  TERTIARY_SPATIAL_DIMENSION,
  PRIMARY_DIRECTIONAL_DIMENSION,
  SECONDARY_DIRECTIONAL_DIMENSION,
  TERTIARY_DIRECTIONAL_DIMENSION,
  ENERGY_DIMENSION,
  TIME_DIMENSION,
  WEIGHT_DIMENSION
};

//! Test if the dimension name is valid
bool isValidPhaseSpaceDimensionName( const std::string& dimension_name );

//! Convert the dimension name to a dimension type enum
PhaseSpaceDimension convertPhaseSpaceDimensionNameToEnum(
                                           const std::string& dimension_name );

//! Convert the dimension type enum to a string
std::string convertPhaseSpaceDimensionEnumToString(
                                 const PhaseSpaceDimension dimension );

//! Convert the spatial dimension to the equivalent phase space dimension
PhaseSpaceDimension convertSpatialDimensionToPhaseSpaceDimension(
                       const Utility::SpatialDimensionType spatial_dimension );

//! Convert the directional dimension to the equivalent phase space dimension
PhaseSpaceDimension convertDirectionalDimensionToPhaseSpaceDimension(
               const Utility::DirectionalDimensionType directional_dimension );

//! Stream operator for printing dimension type enums
inline std::ostream& operator<<( std::ostream& os,
                                 const PhaseSpaceDimension dimension )
{
  os << convertPhaseSpaceDimensionEnumToString( dimension );
  return os;
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHASE_SPACE_DIMENSION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhaseSpaceDimension.hpp
//---------------------------------------------------------------------------//
