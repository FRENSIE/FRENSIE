//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_MaterialParticleResponseFunction.cpp
//! \author Alex Robinson
//! \brief  Material particle response function class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_MaterialParticleResponseFunction.hpp"

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::NeutronMaterialParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::NeutronMaterial> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::NeutronMaterial> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ElectronMaterialParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::ElectronMaterial> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::ElectronMaterial> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::PositronMaterialParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::PositronMaterial> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::PositronMaterial> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::AdjointPhotonMaterialParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::AdjointPhotonMaterial> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::AdjointPhotonMaterial> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::AdjointElectronMaterialParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::AdjointElectronMaterial> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::AdjointElectronMaterial> );

//---------------------------------------------------------------------------//
// end MonteCarlo_MaterialParticleResponseFunction.cpp
//---------------------------------------------------------------------------//
