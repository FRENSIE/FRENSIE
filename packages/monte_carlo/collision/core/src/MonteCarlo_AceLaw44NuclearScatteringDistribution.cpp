//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AceLaw44NuclearScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  The law 44 scattering distribution class instantiation
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AceLaw44NuclearScatteringDistribution.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_PhotonState.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( AceLaw44NuclearScatteringDistribution<NeutronState,NeutronState,CMSystemConversionPolicy> );
EXPLICIT_TEMPLATE_CLASS_INST( AceLaw44NuclearScatteringDistribution<NeutronState,NeutronState,LabSystemConversionPolicy> );

EXPLICIT_TEMPLATE_CLASS_INST( AceLaw44NuclearScatteringDistribution<NeutronState,PhotonState,CMSystemConversionPolicy> );
EXPLICIT_TEMPLATE_CLASS_INST( AceLaw44NuclearScatteringDistribution<NeutronState,PhotonState,LabSystemConversionPolicy> );

EXPLICIT_TEMPLATE_CLASS_INST( AceLaw44NuclearScatteringDistribution<PhotonState,NeutronState,LabSystemConversionPolicy> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AceLaw44NuclearScatteringDistribution.cpp
//---------------------------------------------------------------------------//
