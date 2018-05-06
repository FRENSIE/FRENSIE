//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectronCollisionHandler.hpp
//! \author Alex Robinson
//! \brief  Electron collision handler class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTRON_COLLISION_HANDLER_HPP
#define MONTE_CARLO_ELECTRON_COLLISION_HANDLER_HPP

// FRENSIE Includes
#include "MonteCarlo_ElectronMaterial.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_StandardParticleCollisionHandler.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"

namespace MonteCarlo{

//! The electron collision handler
typedef StandardParticleCollisionHandler<ElectronMaterial> ElectronCollisionHandler;

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardParticleCollisionHandler<ElectronMaterial> );
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTRON_COLLISION_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectronCollisionHandler.hpp
//---------------------------------------------------------------------------//
