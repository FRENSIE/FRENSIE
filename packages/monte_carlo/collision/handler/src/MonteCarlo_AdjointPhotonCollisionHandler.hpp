//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotonCollisionHandler.hpp
//! \author Alex Robinson
//! \brief  Adjoint photon collision handler class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_PHOTON_COLLISION_HANDLER_HPP
#define MONTE_CARLO_ADJOINT_PHOTON_COLLISION_HANDLER_HPP

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotonMaterial.hpp"
#include "MonteCarlo_AdjointPhotonState.hpp"
#include "MonteCarlo_StandardAdjointParticleCollisionHandler.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"

namespace MonteCarlo{

//! The adjoint photon collision handler
typedef StandardParticleCollisionHandler<AdjointPhotonMaterial> AdjointPhotonCollisionHandler

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardParticleCollisionHandler<AdjointPhotonMaterial> );
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_PHOTON_COLLISION_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotonCollisionHandler.hpp
//---------------------------------------------------------------------------//
