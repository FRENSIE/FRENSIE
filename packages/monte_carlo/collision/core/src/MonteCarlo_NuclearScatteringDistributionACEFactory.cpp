//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclearScatteringDistributionACEFactory.cpp
//! \author Alex Robinson
//! \brief  The nuclear scattering distribution ACE factory instantiation
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_PhotonState.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( NuclearScatteringDistributionACEFactory<NeutronState,PhotonState> );
EXPLICIT_TEMPLATE_CLASS_INST( NuclearScatteringDistributionACEFactory<PhotonState,NeutronState> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//
