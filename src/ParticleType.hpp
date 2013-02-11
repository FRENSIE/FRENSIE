#ifndef PARTICLE_TYPE_HPP
#define PARTICLE_TYPE_HPP

namespace FAPMC{

//! Particle type enumeration
enum ParticleType{
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
extern const char* const ParticleTypeStr[];

} // end namespace FAPMC

#endif // end PARTICLE_TYPE_HPP

//---------------------------------------------------------------------------//
// end ParticleType.hpp
//---------------------------------------------------------------------------//
