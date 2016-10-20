//---------------------------------------------------------------------------//
//!
//! \file   tstCollisionHandler.cpp
//! \author Alex Robinson
//! \brief  Collision handler class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>

// FRENSIE Includes
#include "MonteCarlo_NuclideFactory.hpp"
#include "MonteCarlo_NeutronMaterial.hpp"
#include "MonteCarlo_PhotoatomFactory.hpp"
#include "MonteCarlo_PhotonMaterial.hpp"
#include "MonteCarlo_AdjointPhotoatomFactory.hpp"
#include "MonteCarlo_AdjointPhotonMaterial.hpp"
#include "MonteCarlo_ElectroatomFactory.hpp"
#include "MonteCarlo_ElectronMaterial.hpp"
#include "MonteCarlo_CollisionHandler.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::NeutronMaterial> cold_hydrogen;
Teuchos::RCP<MonteCarlo::NeutronMaterial> hot_hydrogen;
Teuchos::RCP<MonteCarlo::PhotonMaterial> photon_lead;
Teuchos::RCP<MonteCarlo::AdjointPhotonMaterial> adjoint_photon_si;
Teuchos::RCP<MonteCarlo::ElectronMaterial> electron_lead;


//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that material can be added to the collision handler
TEUCHOS_UNIT_TEST( CollisionHandler, addMaterial )
{
  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>
    cells_containing_material( 3 );
  cells_containing_material[0] = 1;
  cells_containing_material[1] = 2;
  cells_containing_material[2] = 3;

  MonteCarlo::CollisionHandler::addMaterial( cold_hydrogen,
					     cells_containing_material );

  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 1, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 2, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 3, MonteCarlo::NEUTRON ) );

  cells_containing_material[0] = 4;
  cells_containing_material[1] = 5;
  cells_containing_material[2] = 6;

  MonteCarlo::CollisionHandler::addMaterial( hot_hydrogen,
					     cells_containing_material );

  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 4, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 5, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 6, MonteCarlo::NEUTRON ) );

  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 0, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 7, MonteCarlo::NEUTRON ) );

  MonteCarlo::CollisionHandler::addMaterial( photon_lead,
					     cells_containing_material );

  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 4, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 5, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 6, MonteCarlo::PHOTON ) );

  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 0, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 7, MonteCarlo::PHOTON ) );

  MonteCarlo::CollisionHandler::addMaterial( electron_lead,
					     cells_containing_material );

  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 4, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 5, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 6, MonteCarlo::ELECTRON ) );

  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 0, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 7, MonteCarlo::ELECTRON ) );

  MonteCarlo::CollisionHandler::addMaterial( adjoint_photon_si,
                                             cells_containing_material );

  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 4, MonteCarlo::ADJOINT_PHOTON ) );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 5, MonteCarlo::ADJOINT_PHOTON ) );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 6, MonteCarlo::ADJOINT_PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 0, MonteCarlo::ADJOINT_PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 7, MotneCarlo::ADJOINT_PHOTON ) );
}

//---------------------------------------------------------------------------//
// Check that the material contained in a cell can be retrieved
TEUCHOS_UNIT_TEST( CollisionHandler, getCellNeutronMaterial )
{
  Teuchos::RCP<MonteCarlo::NeutronMaterial> cell_material =
    MonteCarlo::CollisionHandler::getCellNeutronMaterial( 1 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 0 );

  cell_material = MonteCarlo::CollisionHandler::getCellNeutronMaterial( 2 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 0 );

  cell_material = MonteCarlo::CollisionHandler::getCellNeutronMaterial( 3 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 0 );

  cell_material = MonteCarlo::CollisionHandler::getCellNeutronMaterial( 4 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 1 );

  cell_material = MonteCarlo::CollisionHandler::getCellNeutronMaterial( 5 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 1 );

  cell_material = MonteCarlo::CollisionHandler::getCellNeutronMaterial( 6 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 1 );
}

//---------------------------------------------------------------------------//
// Check that the material contained within a cell can be retrieved
TEUCHOS_UNIT_TEST( CollisionHandler, getCellPhotonMaterial )
{
  Teuchos::RCP<MonteCarlo::PhotonMaterial> cell_material =
    MonteCarlo::CollisionHandler::getCellPhotonMaterial( 4 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 0 );

  cell_material = MonteCarlo::CollisionHandler::getCellPhotonMaterial( 5 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 0 );

  cell_material = MonteCarlo::CollisionHandler::getCellPhotonMaterial( 6 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the material contained within a cell can be retrieved
TEUCHOS_UNIT_TEST( CollisionHandler, getCellElectronMaterial )
{
  Teuchos::RCP<MonteCarlo::ElectronMaterial> cell_material =
    MonteCarlo::CollisionHandler::getCellElectronMaterial( 4 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 0 );

  cell_material = MonteCarlo::CollisionHandler::getCellElectronMaterial( 5 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 0 );

  cell_material = MonteCarlo::CollisionHandler::getCellElectronMaterial( 6 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total cross section in a cell can be retrieved
TEUCHOS_UNIT_TEST( CollisionHandler, getMacroscopicTotalCrossSection )
{
  // Neutron cross sections
  MonteCarlo::NeutronState neutron( 0ull );
  neutron.setEnergy( 1.0e-11 );
  neutron.setCell( 1 );

  double cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicTotalCrossSection( neutron );

  TEST_FLOATING_EQUALITY( cross_section, 703.45055504218, 1e-13 );

  neutron.setEnergy( 2.0e1 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicTotalCrossSection( neutron );

  TEST_FLOATING_EQUALITY( cross_section, 0.28847574157342, 1e-9 );

  neutron.setEnergy( 1.0e-11 );
  neutron.setCell( 2 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicTotalCrossSection( neutron );

  TEST_FLOATING_EQUALITY( cross_section, 703.45055504218, 1e-13 );

  neutron.setEnergy( 2.0e1 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicTotalCrossSection( neutron );

  TEST_FLOATING_EQUALITY( cross_section, 0.28847574157342, 1e-9 );

  neutron.setEnergy( 1.0e-11 );
  neutron.setCell( 3 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicTotalCrossSection( neutron );

  TEST_FLOATING_EQUALITY( cross_section, 703.45055504218, 1e-13 );

  neutron.setEnergy( 2.0e1 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicTotalCrossSection( neutron );

  TEST_FLOATING_EQUALITY( cross_section, 0.28847574157342, 1e-9 );

  // Photon cross sections
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 1.0000000000042743e-06 );
  photon.setCell( 4 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicTotalCrossSection( photon );

  TEST_FLOATING_EQUALITY( cross_section, 1.823831998305667e-05, 1e-12 );

  photon.setEnergy( 99999.99999997711 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicTotalCrossSection( photon );

  TEST_FLOATING_EQUALITY( cross_section, 0.11970087585747362, 1e-12 );

  photon.setCell( 5 );
  photon.setEnergy( 1.0000000000042743e-06 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicTotalCrossSection( photon );

  TEST_FLOATING_EQUALITY( cross_section, 1.823831998305667e-05, 1e-12 );

  photon.setEnergy( 99999.99999997711 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicTotalCrossSection( photon );

  TEST_FLOATING_EQUALITY( cross_section, 0.11970087585747362, 1e-12 );

  photon.setCell( 6 );
  photon.setEnergy( 1.0000000000042743e-06 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicTotalCrossSection( photon );

  TEST_FLOATING_EQUALITY( cross_section, 1.823831998305667e-05, 1e-12 );

  photon.setEnergy( 99999.99999997711 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicTotalCrossSection( photon );

  TEST_FLOATING_EQUALITY( cross_section, 0.11970087585747362, 1e-12 );

  // Electron cross sections
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.00000e-05 );
  electron.setCell( 4 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicTotalCrossSection( electron );

  TEST_FLOATING_EQUALITY( cross_section,
                          7.641204418336E+06,
                          1e-12 );

  electron.setEnergy( 1.00000e+05 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicTotalCrossSection( electron );

  TEST_FLOATING_EQUALITY( cross_section,
                          8.269992326372E+03,
                          1e-12 );

  electron.setCell( 5 );
  electron.setEnergy( 1.00000e-05 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicTotalCrossSection( electron );

  TEST_FLOATING_EQUALITY( cross_section,
                          7.641204418336E+06,
                          1e-12 );

  electron.setEnergy( 1.00000e+05 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicTotalCrossSection( electron );

  TEST_FLOATING_EQUALITY( cross_section,
                          8.269992326372E+03,
                          1e-12 );

  electron.setCell( 6 );
  electron.setEnergy( 1.00000e-05 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicTotalCrossSection( electron );

  TEST_FLOATING_EQUALITY( cross_section,
                          7.641204418336E+06,
                          1e-12 );

  electron.setEnergy( 1.00000e+05 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicTotalCrossSection( electron );

  TEST_FLOATING_EQUALITY( cross_section,
                          8.269992326372E+03,
                          1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the macroscopic reaction cross section in a cell can be retrieved
TEUCHOS_UNIT_TEST( CollisionHandler, getMacroscopicReactionCrossSection )
{
  // Neutron reactions
  MonteCarlo::NeutronState neutron( 0ull );
  neutron.setEnergy( 1.0e-11 );
  neutron.setCell( 1 );

  double cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection(
						   neutron,
						   MonteCarlo::N__TOTAL_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 703.45055504218, 1e-13 );

  neutron.setEnergy( 2.0e1 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection(
						   neutron,
						   MonteCarlo::N__TOTAL_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.28847574157342, 1e-9 );

  neutron.setEnergy( 1.0e-11 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection(
					       neutron,
					       MonteCarlo::N__N_ELASTIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 693.47099764974, 1e-13 );

  neutron.setEnergy( 2.0e1 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection(
					       neutron,
					       MonteCarlo::N__N_ELASTIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.28845947418338, 1e-13 );

  neutron.setEnergy( 1.0e-11 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection(
					       neutron,
					       MonteCarlo::N__GAMMA_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 9.9795573924326, 1e-13 );

  neutron.setEnergy( 2.0e1 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection(
					       neutron,
					       MonteCarlo::N__GAMMA_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.6267115171099e-5, 1e-13 );

  neutron.setEnergy( 1.0e-11 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection(
					       neutron,
					       MonteCarlo::N__TOTAL_D_PRODUCTION );

  TEST_FLOATING_EQUALITY( cross_section, 9.9795573924326, 1e-13 );

  neutron.setEnergy( 2.0e1 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection(
					       neutron,
					       MonteCarlo::N__TOTAL_D_PRODUCTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.6267115171099e-5, 1e-13 );

  neutron.setEnergy( 1.0e-11 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection(
					       neutron,
					       MonteCarlo::N__DPA );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-15 );

  neutron.setEnergy( 2.0e1 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection(
					       neutron,
					       MonteCarlo::N__DPA );

  TEST_FLOATING_EQUALITY( cross_section, 1.833066682067e-4, 1e-13 );

  neutron.setEnergy( 1.0e-11 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection(
					       neutron,
					       MonteCarlo::N__FISSION_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-15 );

  // Photoatomic reactions
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 1.0000000000042743e-06 );
  photon.setCell( 4 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection(
			   photon,
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 4.460222195795113e-09, 1e-12 );

  photon.setEnergy( 99999.99999997711 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection(
			   photon,
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 4.060877396028078e-06, 1e-12 );

  photon.setEnergy( 1.0000000000042743e-06 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection(
				   photon,
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.8233859760860873e-05, 1e-12 );

  photon.setEnergy( 99999.99999997711 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection(
				   photon,
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.712301051729535e-13, 1e-12 );

  photon.setEnergy( 1.0000000000042743e-06 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection(
		   photon,
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

   TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

   photon.setEnergy( 99999.99999997711 );

   cross_section =
     MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection(
		   photon,
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

   TEST_FLOATING_EQUALITY( cross_section, 3.4075097760409515e-08, 1e-12 );

   photon.setEnergy( 1.0000000000042743e-06 );

   cross_section =
     MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection(
		  photon,
		  MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

   TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

   photon.setEnergy( 99999.99999997711 );

   cross_section =
     MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection(
		  photon,
		  MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

   TEST_FLOATING_EQUALITY( cross_section, 1.5612230905027824e-13, 1e-12 );

   photon.setEnergy( 1.0000000000042743e-06 );

   cross_section =
     MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection(
		  photon,
		  MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

   TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

   photon.setEnergy( 99999.99999997711 );

   cross_section =
     MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection(
		  photon,
		  MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

   TEST_FLOATING_EQUALITY( cross_section, 0.11969677359280363, 1e-12 );

   // Electroatomic reactions
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.00000E-05 );
  electron.setCell( 4 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection(
				 electron,
				 MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.545329003693E+04, 1e-12 );

  electron.setEnergy( 1.00000E+05 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection(
				 electron,
				 MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 4.588134602166E+03, 1e-12 );

  electron.setEnergy( 1.00000E-05 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection(
				   electron,
				   MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.415377951846E+01, 1e-12 );

  electron.setEnergy( 1.00000E+05 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection(
				   electron,
				   MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 5.679677054824E+00, 1e-12 );

  electron.setEnergy( 1.00000E-05 );

  cross_section =
    MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection(
		   electron,
		   MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

   TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

   electron.setEnergy( 1.00000E+05 );

   cross_section =
     MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection(
		   electron,
		   MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

   TEST_FLOATING_EQUALITY( cross_section, 1.060615028974E-01, 1e-12 );

   electron.setEnergy( 1.00000E-05 );

   cross_section =
     MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection(
		  electron,
		  MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

   TEST_FLOATING_EQUALITY( cross_section, 3.096230095899E+05, 1e-12 );

   electron.setEnergy( 1.00000E+05 );

   cross_section =
     MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection(
		  electron,
		  MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

   TEST_FLOATING_EQUALITY( cross_section, 5.296521123591E+02, 1e-12 );


   double energy = 1.00000e-05;

   electron.setEnergy( energy );

   cross_section =
     MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection(
		  electron,
		  MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

   TEST_FLOATING_EQUALITY( cross_section,
                           7.234825686582E+06,
                           1e-12 );


   energy = 1.00000e+05;

   electron.setEnergy( energy );

   cross_section =
     MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection(
		  electron,
		  MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

   TEST_FLOATING_EQUALITY( cross_section,
                          2.566534386946E-04,
                          1e-12 );

}

//---------------------------------------------------------------------------//
// Check that a neutron can collide with the material in a cell
TEUCHOS_UNIT_TEST( CollisionHandler, collideWithCellMaterial )
{
  // Neutron collision
  MonteCarlo::NeutronState neutron( 0ull );
  neutron.setCell( 1 );
  neutron.setDirection( 0.0, 0.0, 1.0 );
  neutron.setEnergy( 1.0 );
  neutron.setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  MonteCarlo::CollisionHandler::collideWithCellMaterial( neutron, bank, true );

  TEST_EQUALITY_CONST( neutron.getWeight(), 1.0 );

  neutron.setCell( 4 );
  neutron.setEnergy( 1.0 );

  MonteCarlo::CollisionHandler::collideWithCellMaterial( neutron, bank, true );

  TEST_EQUALITY_CONST( neutron.getWeight(), 1.0 );

  neutron.setCell( 1 );
  neutron.setEnergy( 1.03125e-11 );

  MonteCarlo::CollisionHandler::collideWithCellMaterial( neutron, bank, false );

  TEST_FLOATING_EQUALITY( neutron.getWeight(), 0.98581348192787, 1e-14 );

  // Photon collision
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  photon.setCell( 4 );

  // Set up the random number stream
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.5; // select the pb atom
  fake_stream[1] = 0.9; // select the incoherent reaction
  fake_stream[2] = 0.001; // sample from first term of koblinger's method
  fake_stream[3] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[4] = 0.5; // accept x in scattering function rejection loop
  fake_stream[5] = 0.005; // select first shell for collision - old
  fake_stream[6] = 0.005; // select first shell for collision - endf
  fake_stream[7] = 6.427713151861e-01; // select pz = 40.0
  fake_stream[8] = 0.25; // select energy loss

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::CollisionHandler::collideWithCellMaterial( photon, bank, true );

  TEST_FLOATING_EQUALITY( photon.getEnergy(), 0.352804013048420073, 1e-12 );
  TEST_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // Electron collision
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );
  electron.setCell( 4 );

  // Set up the random number stream
  std::vector<double> fake_electron_stream( 3 );
  fake_electron_stream[0] = 0.5; // select the pb atom
  fake_electron_stream[1] = 0.36; // select the elastic reaction
  fake_electron_stream[2] = 0.5; // sample mu = 0.9874366113907

  Utility::RandomNumberGenerator::setFakeStream( fake_electron_stream );

  MonteCarlo::CollisionHandler::collideWithCellMaterial( electron, bank, true );

  //! \todo Double check the distribution type (Histogram)
  TEST_EQUALITY_CONST( electron.getEnergy(), 1e-3 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(),
			  0.9874366113907,
			  1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();

}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_cross_sections_xml_directory;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_cross_sections_xml_directory",
                   &test_cross_sections_xml_directory,
                   "Directory where test cross_sections.xml file is located.");
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Assign the name of the cross_sections.xml file with path
  std::string cross_section_xml_file = test_cross_sections_xml_directory;
  cross_section_xml_file += "/cross_sections.xml";

  Teuchos::ParameterList cross_section_table_info;
  
  // Read in the xml file storing the cross section table information
  Teuchos::updateParametersFromXmlFile(
			         cross_section_xml_file,
			         Teuchos::inoutArg(cross_section_table_info) );

  std::unordered_set<std::string> nuclide_aliases;
  nuclide_aliases.insert( "H-1_293.6K" );
  nuclide_aliases.insert( "H-1_900K" );

  // Create the nuclide factory
  MonteCarlo::NuclideFactory nuclide_factory(
					     test_cross_sections_xml_directory,
					     cross_section_table_info,
					     nuclide_aliases,
					     false,
					     false );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Nuclide> >
    nuclide_map;

  nuclide_factory.createNuclideMap( nuclide_map );
  
  // Create cold hydrogen
  Teuchos::Array<double> nuclide_fractions( 1 );
  Teuchos::Array<std::string> nuclide_names( 1 );
  
  nuclide_fractions[0] = -1.0;
  nuclide_names[0] = "H-1_293.6K";
  
  cold_hydrogen.reset( new MonteCarlo::NeutronMaterial( 0,
                                                        -1.0,
                                                        nuclide_map,
                                                        nuclide_fractions,
                                                        nuclide_names ) );
  
  // Create hot hydrogen
  nuclide_names[0] = "H-1_900K";
  
  hot_hydrogen.reset( new MonteCarlo::NeutronMaterial( 1,
                                                       -1.0,
                                                       nuclide_map,
                                                       nuclide_fractions,
                                                       nuclide_names ) );
  
  // Assign the atom fractions and names
  std::unordered_set<std::string> atom_aliases;
  atom_aliases.insert( "Pb" );
  
  Teuchos::Array<double> atom_fractions( 1 );
  Teuchos::Array<std::string> atom_names( 1 );
  
  atom_fractions[0] = -1.0; // weight fraction
  atom_names[0] = "Pb";
  
  // Create the atomic relaxation factory
  Teuchos::RCP<MonteCarlo::AtomicRelaxationModelFactory>
    atomic_relaxation_model_factory(
                                new MonteCarlo::AtomicRelaxationModelFactory );

  // Create the photoatom factory
  MonteCarlo::PhotoatomFactory photoatom_factory(
		 test_cross_sections_xml_directory,
		 cross_section_table_info,
		 atom_aliases,
		 atomic_relaxation_model_factory,
		 1000,
		 MonteCarlo::DECOUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL,
		 3.0,
		 false,
		 true );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Photoatom> >
    photoatom_map;

  photoatom_factory.createPhotoatomMap( photoatom_map );
  
  // Create lead for photons
  photon_lead.reset( new MonteCarlo::PhotonMaterial( 0,
                                                     -1.0,
                                                     photoatom_map,
                                                     atom_fractions,
                                                     atom_names ) );

  double upper_cutoff_angle_cosine = 1.0;
  unsigned hash_grid_bins = 1000;

  // Create the electroatom factory
  MonteCarlo::ElectroatomFactory electroatom_factory(
                                             test_cross_sections_xml_directory,
                                             cross_section_table_info,
                                             atom_aliases,
                                             atomic_relaxation_model_factory,
                                             hash_grid_bins,
                                             MonteCarlo::TWOBS_DISTRIBUTION,
                                             true,
                                             upper_cutoff_angle_cosine );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Electroatom> >
    electroatom_map;

  electroatom_factory.createElectroatomMap( electroatom_map );
  
  // Create lead for electrons
  electron_lead.reset( new MonteCarlo::ElectronMaterial( 0,
                                                         -1.0,
                                                         electroatom_map,
                                                         atom_fractions,
                                                         atom_names ) );

  // Create the adjoint photoatom factory
  atom_aliases.clear();
  atom_aliases.insert( "Si-Native" );
  
  atom_names[0] = "Si-Native";

  // Create the atom factory
  Teuchos::Array<double> user_critical_line_energies;
  
  MonteCarlo::AdjointPhotoatomFactory factory(
                                       test_cross_sections_xml_directory,
                                       cross_section_table_info,
                                       atom_aliases,
                                       20.0,
                                       100,
                                       MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL,
                                       user_critical_line_energies );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::AdjointPhotoatom> >
    adjoint_photoatom_map;

  factory.createAdjointPhotoatomMap( adjoint_photoatom_map );

  // Create Si for adjoint photons
  adjoint_photon_si.reset( new MonteCarlo::AdjointPhotonMaterial(
                                                         0,
                                                         -1.0,
                                                         adjoint_photoatom_map,
                                                         atom_fractions,
                                                         atom_names ) );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstCollisionHandler.cpp
//---------------------------------------------------------------------------//
