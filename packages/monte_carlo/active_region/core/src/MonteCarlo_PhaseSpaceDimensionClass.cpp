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

namespace Utility{

// Convert the dimension type enum to a string
std::string ToStringTraits<MonteCarlo::PhaseSpaceDimensionClass>::toString(
                   const MonteCarlo::PhaseSpaceDimensionClass dimension_class )
{
  switch( dimension_class )
  {
  case MonteCarlo::SPATIAL_DIMENSION_CLASS:
    return "Spatial Dimension Class";
  case MonteCarlo::DIRECTIONAL_DIMENSION_CLASS:
    return "Directional Dimension Class";
  case MonteCarlo::ENERGY_DIMENSION_CLASS:
    return "Energy Dimension Class";
  case MonteCarlo::TIME_DIMENSION_CLASS:
    return "Time Dimension Class";
  case MonteCarlo::WEIGHT_DIMENSION_CLASS:
    return "Weight Dimension Class";
  default:
    THROW_EXCEPTION( std::logic_error,
                     "An unknown PhaseSpaceDimensionClass was "
                     "encountered (" << (unsigned)dimension_class << ")!" );
  }
}

// Place the MonteCarlo::PhaseSpaceDimension in a stream
void ToStringTraits<MonteCarlo::PhaseSpaceDimensionClass>::toStream( std::ostream& os, const MonteCarlo::PhaseSpaceDimensionClass _class )
{
  os << ToStringTraits<MonteCarlo::PhaseSpaceDimensionClass>::toString( _class );
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhaseSpaceDimensionClass.cpp
//---------------------------------------------------------------------------//
