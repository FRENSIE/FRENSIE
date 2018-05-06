//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NeutronCollisionHandler.hpp
//! \author Alex Robinson
//! \brief  Neutron collision handler class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NEUTRON_COLLISION_HANDLER_HPP
#define MONTE_CARLO_NEUTRON_COLLISION_HANDLER_HPP

// FRENSIE Includes
#include "MonteCarlo_NeutronMaterial.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_StandardParticleCollisionHandler.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"

namespace MonteCarlo{

//! The neutron collision handler
typedef StandardParticleCollisionHandler<NeutronMaterial> NeutronCollisionHandler;

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardParticleCollisionHandler<NeutronMaterial> );
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_NEUTRON_COLLISION_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronCollisionHandler.hpp
//---------------------------------------------------------------------------//
