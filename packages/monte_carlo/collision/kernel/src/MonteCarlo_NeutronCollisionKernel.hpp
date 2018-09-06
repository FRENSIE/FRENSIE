//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NeutronCollisionKernel.hpp
//! \author Alex Robinson
//! \brief  Neutron collision kernel class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NEUTRON_COLLISION_KERNEL_HPP
#define MONTE_CARLO_NEUTRON_COLLISION_KERNEL_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardParticleCollisionKernel.hpp"
#include "MonteCarlo_FilledNeutronGeometryModel.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"

namespace MonteCarlo{

//! The neutron collision kernel
typedef StandardParticleCollisionKernel<FilledNeutronGeometryModel> NeutronCollisionKernel;

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardParticleCollisionKernel<FilledNeutronGeometryModel> );
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_NEUTRON_COLLISION_KERNEL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronCollisionKernel.hpp
//---------------------------------------------------------------------------//
