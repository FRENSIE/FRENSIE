//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSourceDimensionClassType.cpp
//! \author Alex Robinson
//! \brief  Particle source dimension class type helper function definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ParticleSourceDimensionClassType.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Convert the dimension type enum to a string
std::string convertParticleSourceDimensionClassTypeEnumToString(
                       const ParticleSourceDimensionClassType dimension_class )
{
  switch( dimension_class )
  {
  case SPATIAL_PS_DIMENSION_CLASS:
    return "Spatial Dimension Class";
  case DIRECTIONAL_PS_DIMENSION_CLASS:
    return "Directional Dimension Class";
  case ENERGY_PS_DIMENSION_CLASS:
    return "Energy Dimension Class";
  case TIME_PS_DIMENSION_CLASS:
    return "Time Dimension Class";
  case WEIGHT_PS_DIMENSION_CLASS:
    return "Weight Dimension Class";
  default:
    THROW_EXCEPTION( std::logic_error,
                     "Error: An unknown ParticleSourceDimensionClassType was "
                     "encountered (" << (unsigned)dimension_class << ")!" );
  }
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSourceDimensionClassType.cpp
//---------------------------------------------------------------------------//
