//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PositronCollisionKernel.hpp
//! \author Luke Kersting
//! \brief  Positron collision kernel class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_POSITRON_COLLISION_KERNEL_HPP
#define MONTE_CARLO_POSITRON_COLLISION_KERNEL_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardParticleCollisionKernel.hpp"
#include "MonteCarlo_FilledPositronGeometryModel.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"

namespace MonteCarlo{

//! The positron collision kernel
typedef StandardParticleCollisionKernel<FilledPositronGeometryModel> PositronCollisionKernel;

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardParticleCollisionKernel<FilledPositronGeometryModel> );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_POSITRON_COLLISION_KERNEL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PositronCollisionKernel.hpp
//---------------------------------------------------------------------------//
