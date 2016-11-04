//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclearScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  The nuclear scattering dist. base class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringDistribution.hpp"

namespace MonteCarlo{

// Explicit instantiation
template class NuclearScatteringDistribution<NeutronState,NeutronState>;
template class NuclearScatteringDistribution<NeutronState,PhotonState>;
template class NuclearScatteringDistribution<PhotonState,NeutronState>;
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearScatteringDistribution.cpp
//---------------------------------------------------------------------------//
