//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardAdjointParticleSourceComponent.cpp
//! \author Alex Robinson
//! \brief  The standard adjoint particle source component class instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_StandardAdjointParticleSourceComponent.hpp"

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::StandardAdjointPhotonSourceComponent );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::StandardAdjointParticleSourceComponent<MonteCarlo::AdjointPhotonState,MonteCarlo::AdjointPhotonProbeState> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::StandardAdjointParticleSourceComponent<MonteCarlo::AdjointPhotonState,MonteCarlo::AdjointPhotonProbeState> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::StandardAdjointElectronSourceComponent );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::StandardAdjointParticleSourceComponent<MonteCarlo::AdjointElectronState,MonteCarlo::AdjointElectronProbeState> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::StandardAdjointParticleSourceComponent<MonteCarlo::AdjointElectronState,MonteCarlo::AdjointElectronProbeState> );

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardAdjointParticleSourceComponent.cpp
//---------------------------------------------------------------------------//

