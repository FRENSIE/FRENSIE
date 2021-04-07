//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NeutronCollisionKernel.cpp
//! \author Alex Robinson
//! \brief  Neutron collision kernel class explicit template instantiation
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_NeutronCollisionKernel.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( StandardParticleCollisionKernel<FilledNeutronGeometryModel> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronCollisionKernel.cpp
//---------------------------------------------------------------------------//
