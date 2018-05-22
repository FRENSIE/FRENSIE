//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_MaterialParticleResponseFunction.cpp
//! \author Alex Robinson
//! \brief  Material particle response function class template instantiations
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
#include "MonteCarlo_MaterialParticleResponseFunction.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::NeutronMaterialParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::NeutronMaterial> );
EXPLICIT_TEMPLATE_CLASS_SAVE_LOAD_INST( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::NeutronMaterial> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ElectronMaterialParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::ElectronMaterial> );
EXPLICIT_TEMPLATE_CLASS_SAVE_LOAD_INST( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::ElectronMaterial> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::PositronMaterialParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::PositronMaterial> );
EXPLICIT_TEMPLATE_CLASS_SAVE_LOAD_INST( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::PositronMaterial> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::AdjointPhotonMaterialParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::AdjointPhotonMaterial> );
EXPLICIT_TEMPLATE_CLASS_SAVE_LOAD_INST( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::AdjointPhotonMaterial> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::AdjointElectronMaterialParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::AdjointElectronMaterial> );
EXPLICIT_TEMPLATE_CLASS_SAVE_LOAD_INST( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::AdjointElectronMaterial> );

//---------------------------------------------------------------------------//
// end MonteCarlo_MaterialParticleResponseFunction.cpp
//---------------------------------------------------------------------------//
