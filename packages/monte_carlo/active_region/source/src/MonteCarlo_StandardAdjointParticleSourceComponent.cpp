//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardAdjointParticleSourceComponent.cpp
//! \author Alex Robinson
//! \brief  The standard adjoint particle source component class instantiations
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
#include "MonteCarlo_StandardAdjointParticleSourceComponent.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::StandardAdjointPhotonSourceComponent );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::StandardAdjointParticleSourceComponent<MonteCarlo::AdjointPhotonState,MonteCarlo::AdjointPhotonProbeState> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::StandardAdjointParticleSourceComponent<MonteCarlo::AdjointPhotonState,MonteCarlo::AdjointPhotonProbeState> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::StandardAdjointElectronSourceComponent );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::StandardAdjointParticleSourceComponent<MonteCarlo::AdjointElectronState,MonteCarlo::AdjointElectronProbeState> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::StandardAdjointParticleSourceComponent<MonteCarlo::AdjointElectronState,MonteCarlo::AdjointElectronProbeState> );

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardAdjointParticleSourceComponent.cpp
//---------------------------------------------------------------------------//

