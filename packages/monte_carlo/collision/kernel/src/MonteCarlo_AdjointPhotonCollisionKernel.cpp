//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotonCollisionKernel.cpp
//! \author Alex Robinson
//! \brief  Adjoint photon collision kernel class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotonCollisionKernel.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( StandardAdjointParticleCollisionKernel<FilledAdjointPhotonGeometryModel> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotonCollisionKernel.cpp
//---------------------------------------------------------------------------//
