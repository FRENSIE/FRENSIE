//---------------------------------------------------------------------------//
// \file Particle.hpp
// \author Alex Robinson
// \brief Particle enumeration
//---------------------------------------------------------------------------//

#ifndef PARTICLE_HPP
#define PARTICLE_HPP

namespace FACEMC{

//! Particle type enumeration
enum Particle{
  NEUTRON,
  PHOTON,
  ELECTRON,
  ADJOINT_NEUTRON,
  ADJOINT_PHOTON,
  ADJOINT_ELECTRON,
  ADJOINT_NEUTRON_PROBE,
  ADJOINT_PHOTON_PROBE,
  ADJOINT_ELECTRON_PROBE
};

//! Particle type string
extern const char* const ParticleStr[];

} // end FACEMC namespace 

#endif // end PARTICLE_HPP

//---------------------------------------------------------------------------//
// end Particle.hpp
//---------------------------------------------------------------------------//
