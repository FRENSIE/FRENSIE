//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclearScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  The nuclear scattering dist. base class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringDistribution.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_PhotonState.hpp"

namespace MonteCarlo{

// Explicit instantiation
EXPLICIT_TEMPLATE_CLASS_INST( NuclearScatteringDistribution<NeutronState,NeutronState> );
EXPLICIT_TEMPLATE_CLASS_INST( NuclearScatteringDistribution<NeutronState,PhotonState> );
EXPLICIT_TEMPLATE_CLASS_INST( NuclearScatteringDistribution<PhotonState,NeutronState> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearScatteringDistribution.cpp
//---------------------------------------------------------------------------//
