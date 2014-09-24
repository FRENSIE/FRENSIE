//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleType.cpp
//! \author Alex Robinson
//! \brief  Particle type enumeration and helper function definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ParticleType.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Test if the particle type name is valid
bool isValidParticleTypeName( const std::string& particle_type_name )
{
  return particle_type_name.compare( "Photon" ) == 0 ||
    particle_type_name.compare( "Neutron" ) == 0 ||
    particle_type_name.compare( "Adjoint Photon" ) == 0 ||
    particle_type_name.compare( "Adjoint Neutron" ) == 0;
}

// Convert the particle type name to a ParticleType enum
ParticleType convertParticleTypeNameToParticleTypeEnum(
					const std::string& particle_type_name )
{
  if( particle_type_name.compare( "Photon" ) == 0 )
    return PHOTON;
  else if( particle_type_name.compare( "Neutron" ) == 0 )
    return NEUTRON;
  else if( particle_type_name.compare( "Adjoint Photon" ) == 0 )
    return ADJOINT_PHOTON;
  else if( particle_type_name.compare( "Adjoint Neutron" ) == 0 )
    return ADJOINT_NEUTRON;
  else
    return UNKNOWN_PARTICLE;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleType.cpp
//---------------------------------------------------------------------------//
