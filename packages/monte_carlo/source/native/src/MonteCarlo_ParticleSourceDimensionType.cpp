//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSourceDimensionType.cpp
//! \author Alex Robinson
//! \brief  Particle source dimension type helper function definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ParticleSourceDimensionType.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Test if the dimension name is valid
bool isValidParticleSourceDimensionName( const std::string& dimension_name )
{
  if( dimension_name == "X Dimension" )
    return true;
  else if( dimension_name == "Y Dimension" )
    return true;
  else if( dimension_name == "Z Dimension" )
    return true;
  else if( dimension_name == "R Dimension" )
    return true;
  else if( dimension_name == "Axis Dimension" )
    return true;
  else if( dimension_name == "Spatial Polar Angle Dimension" )
    return true;
  else if( dimension_name == "Spatial Azimuthal Angle Dimension" )
    return true;
  else if( dimension_name == "Directional Polar Angle Dimension" )
    return true;
  else if( dimension_name == "Directional Azimuthal Angle Dimension" )
    return true;
  else if( dimension_name == "Energy Dimension" )
    return true;
  else if( dimension_name == "Time Dimension" )
    return true;
  else if( dimension_name == "Weight Dimension" )
    return true;
  else
    return false;
}

// Convert the dimension name to a dimension type enum
ParticleSourceDimensionType convertParticleSourceDimensionNameToEnum(
                                            const std::string& dimension_name )
{
  if( dimension_name == "X Dimension" )
    return X_PS_DIMENSION;
  else if( dimension_name == "Y Dimension" )
    return Y_PS_DIMENSION;
  else if( dimension_name == "Z Dimension" )
    return Z_PS_DIMENSION;
  else if( dimension_name == "R Dimension" )
    return R_PS_DIMENSION;
  else if( dimension_name == "Axis Dimension" )
    return AXIS_PS_DIMENSION;
  else if( dimension_name == "Spatial Polar Angle Dimension" )
    return SPATIAL_POLAR_ANGLE_PS_DIMENSION;
  else if( dimension_name == "Spatial Azimuthal Angle Dimension" )
    return SPATIAL_AZIMUTHAL_ANGLE_PS_DIMENSION;
  else if( dimension_name == "Directional Polar Angle Dimension" )
    return DIRECTIONAL_POLAR_ANGLE_PS_DIMENSION;
  else if( dimension_name == "Directional Azimuthal Angle Dimension" )
    return DIRECTIONAL_AZIMUTHAL_ANGLE_PS_DIMENSION;
  else if( dimension_name == "Energy Dimension" )
    return ENERGY_PS_DIMENSION;
  else if( dimension_name == "Time Dimension" )
    return TIME_PS_DIMENSION;
  else if( dimension_name == "Weight Dimension" )
    return WEIGHT_PS_DIMENSION;
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Error: Dimension name " << dimension_name << " is not "
                     "supported!" );
  }
}

// Convert the dimension type enum to a string
std::string convertParticleSourceDimensionTypeEnumToString(
                                  const ParticleSourceDimensionType dimension )
{
  switch( dimension )
  {
  case X_PS_DIMENSION:
    return "X Dimension";
  case Y_PS_DIMENSION:
    return "Y Dimension";
  case Z_PS_DIMENSION:
    return "Z Dimension";
  case R_PS_DIMENSION:
    return "R Dimension";
  case AXIS_PS_DIMENSION:
    return "Axis Dimension";
  case SPATIAL_POLAR_ANGLE_PS_DIMENSION:
    return "Spatial Polar Angle Dimension";
  case SPATIAL_AZIMUTHAL_ANGLE_PS_DIMENSION:
    return "Spatial Azimuthal Angle Dimension";
  case DIRECTIONAL_POLAR_ANGLE_PS_DIMENSION:
    return "Directional Polar Angle Dimension";
  case DIRECTIONAL_AZIMUTHAL_ANGLE_PS_DIMENSION:
    return "Directional Azimuthal Angle Dimension";
  case ENERGY_PS_DIMENSION:
    return "Energy Dimension";
  case TIME_PS_DIMENSION:
    return "Time Dimension";
  case WEIGHT_PS_DIMENSION:
    return "Weight Dimension";
  default:
    THROW_EXCEPTION( std::logic_error,
                     "Error: An unknown ParticleSourceDimensionType was "
                     "encountered (" << (unsigned)dimension << ")!" );
  }
}
  
// Get the dimension class associated with a dimension
ParticleSourceDimensionClassType getClassOfParticleSourceDimensionType(
                                  const ParticleSourceDimensionType dimension )
{
  switch( dimension )
  {
  case X_PS_DIMENSION:
    return SPATIAL_PS_DIMENSION_CLASS;
  case Y_PS_DIMENSION:
    return SPATIAL_PS_DIMENSION_CLASS;
  case Z_PS_DIMENSION:
    return SPATIAL_PS_DIMENSION_CLASS;
  case R_PS_DIMENSION:
    return SPATIAL_PS_DIMENSION_CLASS;
  case AXIS_PS_DIMENSION:
    return SPATIAL_PS_DIMENSION_CLASS;
  case SPATIAL_POLAR_ANGLE_PS_DIMENSION:
    return SPATIAL_PS_DIMENSION_CLASS;
  case SPATIAL_AZIMUTHAL_ANGLE_PS_DIMENSION:
    return SPATIAL_PS_DIMENSION_CLASS;
  case DIRECTIONAL_POLAR_ANGLE_PS_DIMENSION:
    return DIRECTIONAL_PS_DIMENSION_CLASS;
  case DIRECTIONAL_AZIMUTHAL_ANGLE_PS_DIMENSION:
    return DIRECTIONAL_PS_DIMENSION_CLASS;
  case ENERGY_PS_DIMENSION:
    return ENERGY_PS_DIMENSION_CLASS;
  case TIME_PS_DIMENSION:
    return TIME_PS_DIMENSION_CLASS;
  case WEIGHT_PS_DIMENSION:
    return WEIGHT_PS_DIMENSION_CLASS;
  default:
    THROW_EXCEPTION( std::logic_error,
                     "Error: An unknown ParticleSourceDimensionType was "
                     "encountered (" << (unsigned)dimension << ")!" );
  }
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSourceDimensionType.cpp
//---------------------------------------------------------------------------//
