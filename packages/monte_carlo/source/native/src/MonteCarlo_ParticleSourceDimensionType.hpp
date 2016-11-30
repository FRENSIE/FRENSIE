//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSourceDimensionType.hpp
//! \author Alex Robinson
//! \brief  Particle source dimension type enum and helper function decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_SOURCE_DIMENSION_TYPE_HPP
#define MONTE_CARLO_PARTICLE_SOURCE_DIMENSION_TYPE_HPP

// Std Lib Includes
#include <string>
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_ParticleSourceDimensionClassType.hpp"

namespace MonteCarlo{

enum ParticleSourceDimensionType
{
  X_PS_DIMENSION = 0,
  Y_PS_DIMENSION,
  Z_PS_DIMENSION,
  R_PS_DIMENSION,
  AXIS_PS_DIMENSION,
  SPATIAL_POLAR_ANGLE_PS_DIMENSION,
  SPATIAL_AZIMUTHAL_ANGLE_PS_DIMENSION,
  DIRECTIONAL_POLAR_ANGLE_PS_DIMENSION,
  DIRECTIONAL_AZIMUTHAL_ANGLE_PS_DIMENSION,
  ENERGY_PS_DIMENSION,
  TIME_PS_DIMENSION,
  WEIGHT_PS_DIMENSION
};

//! Test if the dimension name is valid
bool isValidParticleSourceDimensionName( const std::string& dimension_name );

//! Convert the dimension name to a dimension type enum
ParticleSourceDimensionType convertParticleSourceDimensionNameToEnum(
                                           const std::string& dimension_name );

//! Convert the dimension type enum to a string
std::string convertParticleSourceDimensionTypeEnumToString(
                                 const ParticleSourceDimensionType dimension );

//! Get the dimension class associated with a dimension
ParticleSourceDimensionClassType getClassOfParticleSourceDimensionType(
                                 const ParticleSourceDimensionType dimension );

//! Stream operator for printing dimension type enums
inline std::ostream& operator<<( std::ostream& os,
                                 const ParticleSourceDimensionType dimension )
{
  os << convertParticleSourceDimensionTypeEnumToString( dimension );
  return os;
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_SOURCE_DIMENSION_TYPE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSourceDimensionType.hpp
//---------------------------------------------------------------------------//
