//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectronCollisionKernel.hpp
//! \author Alex Robinson
//! \brief  Electron collision kernel class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTRON_COLLISION_KERNEL_HPP
#define MONTE_CARLO_ELECTRON_COLLISION_KERNEL_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardParticleCollisionKernel.hpp"
#include "MonteCarlo_FilledElectronGeometryModel.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"

namespace MonteCarlo{

//! The electron collision kernel
typedef StandardParticleCollisionKernel<FilledElectronGeometryModel> ElectronCollisionKernel;

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardParticleCollisionKernel<FilledElectronGeometryModel> );
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTRON_COLLISION_KERNEL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectronCollisionKernel.hpp
//---------------------------------------------------------------------------//
