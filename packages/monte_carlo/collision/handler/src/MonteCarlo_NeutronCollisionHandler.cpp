//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NeutronCollisionHandler.cpp
//! \author Alex Robinson
//! \brief  Neutron collision handler class explicit template instantiation
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_NeutronCollisionHandler.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( StandardParticleCollisionHandler<NeutronMaterial> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronCollisionHandler.cpp
//---------------------------------------------------------------------------//
