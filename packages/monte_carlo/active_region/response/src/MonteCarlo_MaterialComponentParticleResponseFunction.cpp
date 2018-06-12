//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_MaterialComponentParticleResponseFunction.hpp
//! \author Alex Robinson
//! \brief  Material component particle response function class template
//!         instantiations
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
#include "MonteCarlo_MaterialComponentParticleResponseFunction.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::NeutronMaterialComponentParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::NeutronMaterial> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::NeutronMaterial> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ElectronMaterialComponentParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::ElectronMaterial> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::ElectronMaterial> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::PositronMaterialComponentParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::PositronMaterial> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::PositronMaterial> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::AdjointPhotonMaterialComponentParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::AdjointPhotonMaterial> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::AdjointPhotonMaterial> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::AdjointElectronMaterialComponentParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::AdjointElectronMaterial> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::AdjointElectronMaterial> );

//---------------------------------------------------------------------------//
// end MonteCarlo_MaterialComponentParticleResponseFunction.hpp
//---------------------------------------------------------------------------//
