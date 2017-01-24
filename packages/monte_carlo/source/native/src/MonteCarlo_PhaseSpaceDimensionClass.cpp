//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhaseSpaceDimensionClass.cpp
//! \author Alex Robinson
//! \brief  Phase space dimension class helper function definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_PhaseSpaceDimensionClass.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Convert the dimension type enum to a string
std::string convertPhaseSpaceDimensionClassEnumToString(
                       const PhaseSpaceDimensionClass dimension_class )
{
  switch( dimension_class )
  {
  case SPATIAL_DIMENSION_CLASS:
    return "Spatial Dimension Class";
  case DIRECTIONAL_DIMENSION_CLASS:
    return "Directional Dimension Class";
  case ENERGY_DIMENSION_CLASS:
    return "Energy Dimension Class";
  case TIME_DIMENSION_CLASS:
    return "Time Dimension Class";
  case WEIGHT_DIMENSION_CLASS:
    return "Weight Dimension Class";
  default:
    THROW_EXCEPTION( std::logic_error,
                     "Error: An unknown PhaseSpaceDimensionClass was "
                     "encountered (" << (unsigned)dimension_class << ")!" );
  }
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhaseSpaceDimensionClass.cpp
//---------------------------------------------------------------------------//
