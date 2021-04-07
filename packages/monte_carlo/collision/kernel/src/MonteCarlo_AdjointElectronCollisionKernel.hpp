//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectronCollisionKernel.hpp
//! \author Luke Kersting
//! \brief  Adjoint electron collision kernel class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_ELECTRON_COLLISION_KERNEL_HPP
#define MONTE_CARLO_ADJOINT_ELECTRON_COLLISION_KERNEL_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardAdjointParticleCollisionKernel.hpp"
#include "MonteCarlo_FilledAdjointElectronGeometryModel.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"

namespace MonteCarlo{

//! The adjoint electron collision kernel
typedef StandardAdjointParticleCollisionKernel<FilledAdjointElectronGeometryModel> AdjointElectronCollisionKernel;

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardAdjointParticleCollisionKernel<FilledAdjointElectronGeometryModel> );
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_ELECTRON_COLLISION_KERNEL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectronCollisionKernel.hpp
//---------------------------------------------------------------------------//
