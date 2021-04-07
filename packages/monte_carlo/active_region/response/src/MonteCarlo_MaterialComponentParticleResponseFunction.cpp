//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_MaterialComponentParticleResponseFunction.hpp
//! \author Alex Robinson
//! \brief  Material component particle response function class template
//!         instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_MaterialComponentParticleResponseFunction.hpp"

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::NeutronMaterialComponentParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::NeutronMaterial> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::NeutronMaterial> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ElectronMaterialComponentParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::ElectronMaterial> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::ElectronMaterial> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::PositronMaterialComponentParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::PositronMaterial> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::PositronMaterial> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::AdjointPhotonMaterialComponentParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::AdjointPhotonMaterial> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::AdjointPhotonMaterial> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::AdjointElectronMaterialComponentParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::AdjointElectronMaterial> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::AdjointElectronMaterial> );

//---------------------------------------------------------------------------//
// end MonteCarlo_MaterialComponentParticleResponseFunction.hpp
//---------------------------------------------------------------------------//
