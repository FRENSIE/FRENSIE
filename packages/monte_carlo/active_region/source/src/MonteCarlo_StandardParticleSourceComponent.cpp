//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardParticleSourceComponent.cpp
//! \author Alex Robinson
//! \brief  The standard particle source component class instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_StandardParticleSourceComponent.hpp"

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::StandardNeutronSourceComponent );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::StandardParticleSourceComponent<MonteCarlo::NeutronState> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::StandardParticleSourceComponent<MonteCarlo::NeutronState> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::StandardPhotonSourceComponent );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::StandardParticleSourceComponent<MonteCarlo::PhotonState> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::StandardParticleSourceComponent<MonteCarlo::PhotonState> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::StandardElectronSourceComponent );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::StandardParticleSourceComponent<MonteCarlo::ElectronState> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::StandardParticleSourceComponent<MonteCarlo::ElectronState> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::StandardPositronSourceComponent );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::StandardParticleSourceComponent<MonteCarlo::PositronState> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::StandardParticleSourceComponent<MonteCarlo::PositronState> );

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleSourceComponent.cpp
//---------------------------------------------------------------------------//
