//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonCollisionKernel.hpp
//! \author Alex Robinson
//! \brief  Photon collision kernel class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTON_COLLISION_KERNEL_HPP
#define MONTE_CARLO_PHOTON_COLLISION_KERNEL_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardParticleCollisionKernel.hpp"
#include "MonteCarlo_FilledPhotonGeometryModel.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"

namespace MonteCarlo{

//! The photon collision kernel
typedef StandardParticleCollisionKernel<FilledPhotonGeometryModel> PhotonCollisionKernel;

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardParticleCollisionKernel<FilledPhotonGeometryModel> );
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTON_COLLISION_KERNEL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonCollisionKernel.hpp
//---------------------------------------------------------------------------//
