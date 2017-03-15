//---------------------------------------------------------------------------//
//!
//! \file   Geometry_DagMCParticleType.hpp
//! \author Alex Robinson
//! \brief  DagMC particle type enumeration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_DAGMC_PARTICLE_TYPE_HPP
#define GEOMETRY_DAGMC_PARTICLE_TYPE_HPP

namespace Geometry{

//! The DagMC particle type enum
enum DagMCParticleType{
  DAGMC_PHOTON = 0,
  DAGMC_NEUTRON,
  DAGMC_ELECTRON,
  DAGMC_ADJOINT_PHOTON,
  DAGMC_ADJOINT_NEUTRON,
  DAGMC_ADJOINT_ELECTRON
};
  
} // end Geometry namespace

#endif // end GEOMETRY_DAGMC_PARTICLE_TYPE_HPP

//---------------------------------------------------------------------------//
// end Geometry_DagMCParticleType.hpp
//---------------------------------------------------------------------------//
