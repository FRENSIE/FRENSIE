//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IndependentEnergyAngleNuclearScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  The independent energy angle scattering dist. class instantiation
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_IndependentEnergyAngleNuclearScatteringDistribution.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_PhotonState.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( IndependentEnergyAngleNuclearScatteringDistribution<NeutronState,NeutronState,CMSystemConversionPolicy> );
EXPLICIT_TEMPLATE_CLASS_INST( IndependentEnergyAngleNuclearScatteringDistribution<NeutronState,NeutronState,LabSystemConversionPolicy> );

EXPLICIT_TEMPLATE_CLASS_INST( IndependentEnergyAngleNuclearScatteringDistribution<NeutronState,PhotonState,CMSystemConversionPolicy> );
EXPLICIT_TEMPLATE_CLASS_INST( IndependentEnergyAngleNuclearScatteringDistribution<NeutronState,PhotonState,LabSystemConversionPolicy> );

EXPLICIT_TEMPLATE_CLASS_INST( IndependentEnergyAngleNuclearScatteringDistribution<PhotonState,NeutronState,LabSystemConversionPolicy> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_IndependentEnergyAngleNuclearScatteringDistribution.cpp
//---------------------------------------------------------------------------//
