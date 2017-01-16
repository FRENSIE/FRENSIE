//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSourceDimensionClassType.hpp
//! \author Alex Robinson
//! \brief  Particle source dimension class type enum and helper function decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_SOURCE_DIMENSION_CLASS_TYPE_HPP
#define MONTE_CARLO_PARTICLE_SOURCE_DIMENSION_CLASS_TYPE_HPP

// Std Lib Includes
#include <iostream>
#include <string>

namespace MonteCarlo{

//! The particle source dimension type enumeration
enum ParticleSourceDimensionClassType
{
  SPATIAL_PS_DIMENSION_CLASS = 0,
  DIRECTIONAL_PS_DIMENSION_CLASS,
  ENERGY_PS_DIMENSION_CLASS,
  TIME_PS_DIMENSION_CLASS,
  WEIGHT_PS_DIMENSION_CLASS
};

//! Convert the dimension class type enum to a string
std::string convertParticleSourceDimensionClassTypeEnumToString(
                      const ParticleSourceDimensionClassType dimension_class );

//! Stream operator for printing dimension type enums
inline std::ostream& operator<<(
                       std::ostream& os,
                       const ParticleSourceDimensionClassType dimension_class )
{
  os << convertParticleSourceDimensionClassTypeEnumToString( dimension_class );
  return os;
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_SOURCE_DIMENSION_CLASS_TYPE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSourceDimensionClassType.hpp
//---------------------------------------------------------------------------//
