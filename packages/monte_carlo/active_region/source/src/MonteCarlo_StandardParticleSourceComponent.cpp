//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardParticleSourceComponent.cpp
//! \author Alex Robinson
//! \brief  The standard particle source component class instantiations
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardParticleSourceComponent.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::StandardNeutronSourceComponent );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::StandardParticleSourceComponent<MonteCarlo::NeutronState> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::StandardParticleSourceComponent<MonteCarlo::NeutronState> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::StandardPhotonSourceComponent );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::StandardParticleSourceComponent<MonteCarlo::PhotonState> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::StandardParticleSourceComponent<MonteCarlo::PhotonState> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::StandardElectronSourceComponent );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::StandardParticleSourceComponent<MonteCarlo::ElectronState> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::StandardParticleSourceComponent<MonteCarlo::ElectronState> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::StandardPositronSourceComponent );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::StandardParticleSourceComponent<MonteCarlo::PositronState> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::StandardParticleSourceComponent<MonteCarlo::PositronState> );

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleSourceComponent.cpp
//---------------------------------------------------------------------------//
