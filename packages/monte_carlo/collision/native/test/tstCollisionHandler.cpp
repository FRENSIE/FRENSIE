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

Teuchos::RCP<const MonteCarlo::NeutronMaterial> neutron_hydrogen;
Teuchos::RCP<const MonteCarlo::PhotonMaterial> photon_hydrogen;
Teuchos::RCP<const MonteCarlo::AdjointPhotonMaterial> adjoint_photon_hydrogen;
Teuchos::RCP<const MonteCarlo::ElectronMaterial> electron_hydrogen;

std::shared_ptr<MonteCarlo::CollisionHandler> collision_handler;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that material can be added to the collision handler
TEUCHOS_UNIT_TEST( CollisionHandler, addMaterial_neutron_only )
{
  collision_handler.reset( new MonteCarlo::CollisionHandler );
  
  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::NEUTRON ) );

  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>
    cells_containing_material( 1, 1 );
  
  collision_handler->addMaterial( neutron_hydrogen, cells_containing_material );

  TEST_ASSERT( !collision_handler->isCellVoid( 1, MonteCarlo::NEUTRON ) );
}

//---------------------------------------------------------------------------//
// Check that material can be added to the collision handler
TEUCHOS_UNIT_TEST( CollisionHandler, addMaterial_photon_only )
{
  collision_handler.reset( new MonteCarlo::CollisionHandler );

  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::PHOTON ) );

  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>
    cells_containing_material( 1, 1 );

  collision_handler->addMaterial( photon_hydrogen, cells_containing_material );

  TEST_ASSERT( !collision_handler->isCellVoid( 1, MonteCarlo::PHOTON ) );
}

//---------------------------------------------------------------------------//
// Check that material can be added to the collision handler
TEUCHOS_UNIT_TEST( CollisionHandler, addMaterial_adjoint_photon_only )
{
  collision_handler.reset( new MonteCarlo::CollisionHandler );

  TEST_ASSERT( collision_handler->isCellVoid(1, MonteCarlo::ADJOINT_PHOTON) );

  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>
    cells_containing_material( 1, 1 );

  collision_handler->addMaterial( adjoint_photon_hydrogen,
                                  cells_containing_material );

  TEST_ASSERT( !collision_handler->isCellVoid(1, MonteCarlo::ADJOINT_PHOTON) );
}

//---------------------------------------------------------------------------//
// Check that material can be added to the collision handler
TEUCHOS_UNIT_TEST( CollisionHandler, addMaterial_electron_only )
{
  collision_handler.reset( new MonteCarlo::CollisionHandler );

  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::ELECTRON ) );

  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>
    cells_containing_material( 1, 1 );

  collision_handler->addMaterial( electron_hydrogen,
                                  cells_containing_material );

  TEST_ASSERT( !collision_handler->isCellVoid( 1, MonteCarlo::ELECTRON ) );
}

//---------------------------------------------------------------------------//
// Check that material can be added to the collision handler
TEUCHOS_UNIT_TEST( CollisionHandler, addMaterial_neutron_photon )
{
  collision_handler.reset( new MonteCarlo::CollisionHandler );

  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::PHOTON ) );

  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>
    cells_containing_material( 1, 1 );

  collision_handler->addMaterial( neutron_hydrogen,
                                  photon_hydrogen,
                                  cells_containing_material );

  TEST_ASSERT( !collision_handler->isCellVoid( 1, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 1, MonteCarlo::PHOTON ) );
}

//---------------------------------------------------------------------------//
// Check that material can be added to the collision handler
TEUCHOS_UNIT_TEST( CollisionHandler, addMaterial_photon_electron )
{
  collision_handler.reset( new MonteCarlo::CollisionHandler );

  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::ELECTRON ) );

  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>
    cells_containing_material( 1, 1 );

  collision_handler->addMaterial( photon_hydrogen,
                                  electron_hydrogen,
                                  cells_containing_material );

  TEST_ASSERT( !collision_handler->isCellVoid( 1, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 1, MonteCarlo::ELECTRON ) );
}

//---------------------------------------------------------------------------//
// Check that material can be added to the collision handler
TEUCHOS_UNIT_TEST( CollisionHandler, addMaterial_neutron_photon_electron )
{
  collision_handler.reset( new MonteCarlo::CollisionHandler );

  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::ELECTRON ) );

  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>
    cells_containing_material( 1, 1 );

  collision_handler->addMaterial( neutron_hydrogen,
                                  photon_hydrogen,
                                  electron_hydrogen,
                                  cells_containing_material );

  TEST_ASSERT( !collision_handler->isCellVoid( 1, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 1, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 1, MonteCarlo::ELECTRON ) );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total cross section in a cell can be retrieved
TEUCHOS_UNIT_TEST( CollisionHandler, getMacroscopicTotalCrossSection )
{
  collision_handler.reset( new MonteCarlo::CollisionHandler );

  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>
    cells_containing_material( 1, 1 );

  collision_handler->addMaterial( neutron_hydrogen,
                                  photon_hydrogen,
                                  electron_hydrogen,
                                  cells_containing_material );
  
  collision_handler->addMaterial( adjoint_photon_hydrogen,
                                  cells_containing_material );

  // Neutron cross sections
  MonteCarlo::NeutronState neutron( 0ull );
  neutron.setEnergy( 1.0 );
  neutron.setCell( 1 );

  double cross_section =
    collision_handler->getMacroscopicTotalCrossSection( neutron );

  TEST_ASSERT( cross_section > 0.0 );

  // Photon cross sections
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 1.0 );
  photon.setCell( 1 );

  cross_section =
    collision_handler->getMacroscopicTotalCrossSection( photon );

  TEST_ASSERT( cross_section > 0.0 );

  // Electron cross sections
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0 );
  electron.setCell( 1 );

  cross_section =
    collision_handler->getMacroscopicTotalCrossSection( electron );

  TEST_ASSERT( cross_section > 0.0 );

  // Adjoint photon cross sections
  MonteCarlo::AdjointPhotonState adjoint_photon( 0 );
  adjoint_photon.setEnergy( 1.0 );
  adjoint_photon.setCell( 1 );

  cross_section =
    collision_handler->getMacroscopicTotalCrossSection( adjoint_photon );

  TEST_ASSERT( cross_section > 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total forward cross section in a cell can be
// retrieved
TEUCHOS_UNIT_TEST( CollisionHandler, getMacroscopicTotalForwardCrossSection )
{
  collision_handler.reset( new MonteCarlo::CollisionHandler );

  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>
    cells_containing_material( 1, 1 );

  collision_handler->addMaterial( neutron_hydrogen,
                                  photon_hydrogen,
                                  electron_hydrogen,
                                  cells_containing_material );
  
  collision_handler->addMaterial( adjoint_photon_hydrogen,
                                  cells_containing_material );

  // Neutron cross sections
  MonteCarlo::NeutronState neutron( 0ull );
  neutron.setEnergy( 1.0 );
  neutron.setCell( 1 );

  double cross_section =
    collision_handler->getMacroscopicTotalForwardCrossSection( neutron );

  TEST_ASSERT( cross_section > 0.0 );

  // Photon cross sections
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 1.0 );
  photon.setCell( 1 );

  cross_section =
    collision_handler->getMacroscopicTotalForwardCrossSection( photon );

  TEST_ASSERT( cross_section > 0.0 );

  // Electron cross sections
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0 );
  electron.setCell( 1 );

  cross_section =
    collision_handler->getMacroscopicTotalForwardCrossSection( electron );

  TEST_ASSERT( cross_section > 0.0 );

  // Adjoint photon cross sections
  MonteCarlo::AdjointPhotonState adjoint_photon( 0 );
  adjoint_photon.setEnergy( 1.0 );
  adjoint_photon.setCell( 1 );

  cross_section =
    collision_handler->getMacroscopicTotalForwardCrossSection( adjoint_photon );

  TEST_ASSERT( cross_section > 0.0 );
}

//---------------------------------------------------------------------------//
// Check that a neutron can collide with the material in a cell
TEUCHOS_UNIT_TEST( CollisionHandler, collideWithCellMaterial_analogue )
{
  collision_handler.reset( new MonteCarlo::CollisionHandler );

  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>
    cells_containing_material( 1, 1 );

  collision_handler->addMaterial( neutron_hydrogen,
                                  photon_hydrogen,
                                  electron_hydrogen,
                                  cells_containing_material );
  
  collision_handler->addMaterial( adjoint_photon_hydrogen,
                                  cells_containing_material );
  
  // Neutron collision
  MonteCarlo::NeutronState neutron( 0ull );
  neutron.setCell( 1 );
  neutron.setDirection( 0.0, 0.0, 1.0 );
  neutron.setEnergy( 1.0 );
  neutron.setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  collision_handler->collideWithCellMaterial( neutron, bank );

  TEST_EQUALITY_CONST( neutron.getWeight(), 1.0 );

  // Photon collision
  MonteCarlo::PhotonState photon( 0 );
  photon.setCell( 1 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  photon.setEnergy( 1.0 );
  photon.setWeight( 1.0 );

  collision_handler->collideWithCellMaterial( photon, bank );

  TEST_EQUALITY_CONST( photon.getWeight(), 1.0 );

  // Electron collision
  MonteCarlo::ElectronState electron( 0 );
  electron.setCell( 1 );
  electron.setDirection( 0.0, 0.0, 1.0 );
  electron.setEnergy( 1.0 );
  electron.setWeight( 1.0 );

  collision_handler->collideWithCellMaterial( electron, bank );

  TEST_EQUALITY_CONST( electron.getWeight(), 1.0 );

  // Adjoint photon collision
  MonteCarlo::AdjointPhotonState adjoint_photon( 0 );
  adjoint_photon.setCell( 1 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );
  adjoint_photon.setEnergy( 1.0 );
  adjoint_photon.setWeight( 1.0 );

  collision_handler->collideWithCellMaterial( adjoint_photon, bank );
  
  TEST_FLOATING_EQUALITY( adjoint_photon.getWeight(),
                          1.8606465722488712,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a neutron can collide with the material in a cell
TEUCHOS_UNIT_TEST( CollisionHandler, collideWithCellMaterial_survival_bias )
{
  collision_handler.reset( new MonteCarlo::CollisionHandler( false ) );

  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>
    cells_containing_material( 1, 1 );

  collision_handler->addMaterial( neutron_hydrogen,
                                  photon_hydrogen,
                                  electron_hydrogen,
                                  cells_containing_material );
  
  collision_handler->addMaterial( adjoint_photon_hydrogen,
                                  cells_containing_material );
  
  // Neutron collision
  MonteCarlo::NeutronState neutron( 0ull );
  neutron.setCell( 1 );
  neutron.setDirection( 0.0, 0.0, 1.0 );
  neutron.setEnergy( 1.0 );
  neutron.setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;
  
  collision_handler->collideWithCellMaterial( neutron, bank );
  out.precision( 18 );
  TEST_FLOATING_EQUALITY( neutron.getWeight(), 
                          9.99992063679718601e-01,
                          1e-12 );

  // Photon collision
  MonteCarlo::PhotonState photon( 0 );
  photon.setCell( 1 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  photon.setEnergy( 1.0 );
  photon.setWeight( 1.0 );

  collision_handler->collideWithCellMaterial( photon, bank );

  TEST_FLOATING_EQUALITY( photon.getWeight(),
                          9.99999990707165831e-01,
                          1e-12 );

  // Electron collision
  MonteCarlo::ElectronState electron( 0 );
  electron.setCell( 1 );
  electron.setDirection( 0.0, 0.0, 1.0 );
  electron.setEnergy( 1.0 );
  electron.setWeight( 1.0 );

  collision_handler->collideWithCellMaterial( electron, bank );

  TEST_FLOATING_EQUALITY( electron.getWeight(), 1.0, 1e-12 );

  // Adjoint photon collision
  MonteCarlo::AdjointPhotonState adjoint_photon( 0 );
  adjoint_photon.setCell( 1 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );
  adjoint_photon.setEnergy( 1.0 );
  adjoint_photon.setWeight( 1.0 );

  collision_handler->collideWithCellMaterial( adjoint_photon, bank );
  
  TEST_FLOATING_EQUALITY( adjoint_photon.getWeight(),
                          1.8606465722488712,
                          1e-12 );
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
  
  // Create hydrogen
  Teuchos::Array<double> nuclide_fractions( 1 );
  Teuchos::Array<std::string> nuclide_names( 1 );
  
  nuclide_fractions[0] = -1.0;
  nuclide_names[0] = "H-1_293.6K";
  
  neutron_hydrogen.reset( new MonteCarlo::NeutronMaterial( 0,
                                                           -1.0,
                                                           nuclide_map,
                                                           nuclide_fractions,
                                                           nuclide_names ) );
  
  // Create the atomic relaxation factory
  Teuchos::RCP<MonteCarlo::AtomicRelaxationModelFactory>
    atomic_relaxation_model_factory(
                                new MonteCarlo::AtomicRelaxationModelFactory );

  // Create the photoatom factory
  MonteCarlo::PhotoatomFactory photoatom_factory(
		 test_cross_sections_xml_directory,
		 cross_section_table_info,
		 nuclide_aliases,
		 atomic_relaxation_model_factory,
		 1000,
		 MonteCarlo::DECOUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL,
		 3.0,
		 false,
		 true );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Photoatom> >
    photoatom_map;

  photoatom_factory.createPhotoatomMap( photoatom_map );
  
  // Create hydrogen for photons
  photon_hydrogen.reset( new MonteCarlo::PhotonMaterial( 0,
                                                         -1.0,
                                                         photoatom_map,
                                                         nuclide_fractions,
                                                         nuclide_names ) );

  double upper_cutoff_angle_cosine = 1.0;
  unsigned hash_grid_bins = 1000;

  // Create the electroatom factory
  MonteCarlo::ElectroatomFactory electroatom_factory(
                                             test_cross_sections_xml_directory,
                                             cross_section_table_info,
                                             nuclide_aliases,
                                             atomic_relaxation_model_factory,
                                             hash_grid_bins,
                                             MonteCarlo::TWOBS_DISTRIBUTION,
                                             true,
                                             upper_cutoff_angle_cosine );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Electroatom> >
    electroatom_map;

  electroatom_factory.createElectroatomMap( electroatom_map );
  
  // Create hydgrogen for electrons
  electron_hydrogen.reset( new MonteCarlo::ElectronMaterial( 0,
                                                             -1.0,
                                                             electroatom_map,
                                                             nuclide_fractions,
                                                             nuclide_names ) );

  // Create the atom factory
  Teuchos::Array<double> user_critical_line_energies;
  
  MonteCarlo::AdjointPhotoatomFactory factory(
                                       test_cross_sections_xml_directory,
                                       cross_section_table_info,
                                       nuclide_aliases,
                                       20.0,
                                       100,
                                       MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL,
                                       user_critical_line_energies );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::AdjointPhotoatom> >
    adjoint_photoatom_map;

  factory.createAdjointPhotoatomMap( adjoint_photoatom_map );

  // Create hydrogen for adjoint photons
  adjoint_photon_hydrogen.reset( new MonteCarlo::AdjointPhotonMaterial(
                                                         0,
                                                         -1.0,
                                                         adjoint_photoatom_map,
                                                         nuclide_fractions,
                                                         nuclide_names ) );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstCollisionHandler.cpp
//---------------------------------------------------------------------------//
