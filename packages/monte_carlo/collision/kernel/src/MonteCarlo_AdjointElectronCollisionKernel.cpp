//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectronCollisionKernel.cpp
//! \author Luke Kersting
//! \brief  Adjoint electron collision kernel class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AdjointElectronCollisionKernel.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( StandardAdjointParticleCollisionKernel<FilledAdjointElectronGeometryModel> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectronCollisionKernel.cpp
//---------------------------------------------------------------------------//
