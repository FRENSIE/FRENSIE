//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AceLaw61NuclearScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  The law 61 scattering distribution class instantiation
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AceLaw61NuclearScatteringDistribution.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_PhotonState.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( AceLaw61NuclearScatteringDistribution<NeutronState,NeutronState,CMSystemConversionPolicy> );
EXPLICIT_TEMPLATE_CLASS_INST( AceLaw61NuclearScatteringDistribution<NeutronState,NeutronState,LabSystemConversionPolicy> );

EXPLICIT_TEMPLATE_CLASS_INST( AceLaw61NuclearScatteringDistribution<NeutronState,PhotonState,CMSystemConversionPolicy> );
EXPLICIT_TEMPLATE_CLASS_INST( AceLaw61NuclearScatteringDistribution<NeutronState,PhotonState,LabSystemConversionPolicy> );

EXPLICIT_TEMPLATE_CLASS_INST( AceLaw61NuclearScatteringDistribution<PhotonState,NeutronState,LabSystemConversionPolicy> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AceLaw61NuclearScatteringDistribution.cpp
//---------------------------------------------------------------------------//
