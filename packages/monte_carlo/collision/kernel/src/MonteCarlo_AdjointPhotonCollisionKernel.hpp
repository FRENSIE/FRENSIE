//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotonCollisionKernel.hpp
//! \author Alex Robinson
//! \brief  Adjoint photon collision kernel class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_PHOTON_COLLISION_KERNEL_HPP
#define MONTE_CARLO_ADJOINT_PHOTON_COLLISION_KERNEL_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardAdjointParticleCollisionKernel.hpp"
#include "MonteCarlo_FilledAdjointPhotonGeometryModel.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"

namespace MonteCarlo{

//! The adjoint photon collision kernel
typedef StandardAdjointParticleCollisionKernel<FilledAdjointPhotonGeometryModel> AdjointPhotonCollisionKernel;

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardAdjointParticleCollisionKernel<FilledAdjointPhotonGeometryModel> );
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_PHOTON_COLLISION_KERNEL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotonCollisionKernel.hpp
//---------------------------------------------------------------------------//
