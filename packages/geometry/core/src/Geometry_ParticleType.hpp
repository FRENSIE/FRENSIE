//---------------------------------------------------------------------------//
//!
//! \file   Geometry_ParticleType.hpp
//! \author Alex Robinson
//! \brief  Particle type enumeration (used with cached estimator data)
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_PARTICLE_TYPE_HPP
#define GEOMETRY_PARTICLE_TYPE_HPP

namespace Geometry{

//! The geometry particle type enum
enum ParticleType{
  PHOTON = 0,
  NEUTRON,
  ELECTRON,
  POSITRON,
  ADJOINT_PHOTON,
  ADJOINT_NEUTRON,
  ADJOINT_ELECTRON,
  ADJOINT_POSITRON
};
  
} // end Geometry namespace

#endif // end GEOMETRY_PARTICLE_TYPE_HPP

//---------------------------------------------------------------------------//
// end Geometry_ParticleType.hpp
//---------------------------------------------------------------------------//
