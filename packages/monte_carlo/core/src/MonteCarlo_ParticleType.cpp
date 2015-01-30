//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleType.cpp
//! \author Alex Robinson
//! \brief  Particle type enumeration and helper function definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ParticleType.hpp"
#include "Geometry_DagMCProperties.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Test if the particle type name is valid
bool isValidParticleTypeName( const std::string& particle_type_name )
{
  return particle_type_name.compare( "Photon" ) == 0 ||
    particle_type_name.compare( "Neutron" ) == 0 ||
    particle_type_name.compare( "Electron" ) == 0 ||
    particle_type_name.compare( "Adjoint Photon" ) == 0 ||
    particle_type_name.compare( "Adjoint Neutron" ) == 0 ||
    particle_type_name.compare( "Adjoint Electron" ) == 0;
}

// Convert shorthand particle type name to verbose particle type name
/*! \details These shorthand names should correspond to the names that would
 * be encountered in DagMC.
 */
std::string convertShortParticleTypeNameToVerboseParticleTypeName(
				 const std::string& short_particle_type_name )
{
  // Make sure the shorthand name is valid
  testPrecondition( Geometry::DagMCProperties::isParticleTypeValid( short_particle_type_name ));
  
  if( short_particle_type_name == "n" )
    return "Neutron";
  else if( short_particle_type_name == "p" )
    return "Photon";
  else if( short_particle_type_name == "e" )
    return "Electron";
}

// Convert the particle type name to a ParticleType enum
ParticleType convertParticleTypeNameToParticleTypeEnum(
					const std::string& particle_type_name )
{
  if( particle_type_name.compare( "Photon" ) == 0 )
    return PHOTON;
  else if( particle_type_name.compare( "Neutron" ) == 0 )
    return NEUTRON;
  else if( particle_type_name.compare( "Electron" ) == 0 )
    return ELECTRON;
  else if( particle_type_name.compare( "Adjoint Photon" ) == 0 )
    return ADJOINT_PHOTON;
  else if( particle_type_name.compare( "Adjoint Neutron" ) == 0 )
    return ADJOINT_NEUTRON;
  else if( particle_type_name.compare( "Adjoint Electron" ) == 0 )
    return ADJOINT_ELECTRON;
  else
    return UNKNOWN_PARTICLE;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleType.cpp
//---------------------------------------------------------------------------//
