//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointPhotonCollisionHandler.cpp
//! \author Alex Robinson
//! \brief  Adjoint photon collision handler class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotoatomFactory.hpp"
#include "MonteCarlo_AdjointPhotonMaterial.hpp"
#include "MonteCarlo_AdjointPhotonCollisionHandler.hpp"
#include "MonteCarlo_AdjointPhotonProbeState.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<const MonteCarlo::AdjointPhotonMaterial> silicon;
std::shared_ptr<MonteCarlo::AdjointPhotonCollisionHandler> collision_handler;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that materials can be added to the collision handler
TEUCHOS_UNIT_TEST( AdjointPhotonCollisionHandler, addMaterial )
{
  TEST_ASSERT( collision_handler->isCellVoid( 1 ) );
  TEST_ASSERT( collision_handler->isCellVoid( 2 ) );
  TEST_ASSERT( collision_handler->isCellVoid( 3 ) );

  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>
    cells_containing_material( 3 );
  cells_containing_material[0] = 1;
  cells_containing_material[1] = 2;
  cells_containing_material[2] = 3;

  collision_handler->addMaterial( silicon, cells_containing_material );

  TEST_ASSERT( !collision_handler->isCellVoid( 1 ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 2 ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 3 ) );
}

//---------------------------------------------------------------------------//
// Check that a material contained in a cell can be retrieved
TEUCHOS_UNIT_TEST( AdjointPhotonCollisionHandler, getMaterial )
{
  Teuchos::RCP<const MonteCarlo::AdjointPhotonMaterial> cell_material =
    collision_handler->getMaterial( 1 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 0 );
  TEST_EQUALITY_CONST( cell_material, silicon );

  cell_material = collision_handler->getMaterial( 2 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 0 );
  TEST_EQUALITY_CONST( cell_material, silicon );

  cell_material = collision_handler->getMaterial( 3 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 0 );
  TEST_EQUALITY_CONST( cell_material, silicon );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total cross section in a cell can be retrieved
TEUCHOS_UNIT_TEST( AdjointPhotonCollisionHandler,
                   getMacroscopicTotalCrossSection )
{
  MonteCarlo::AdjointPhotonState adjoint_photon( 0 );
  adjoint_photon.setEnergy( 1e-3 );
  adjoint_photon.setCell( 1 );

  double cross_section =
    collision_handler->getMacroscopicTotalCrossSection( adjoint_photon );

  TEST_FLOATING_EQUALITY( cross_section, 2.1567210358522892, 1e-12 );

  adjoint_photon.setEnergy( 20.0 );

  cross_section =
    collision_handler->getMacroscopicTotalCrossSection( adjoint_photon );

  TEST_FLOATING_EQUALITY( cross_section, 4.2078239999303496e-07, 1e-12 );

  adjoint_photon.setCell( 2 );
  adjoint_photon.setEnergy( 1e-3 );

  cross_section =
    collision_handler->getMacroscopicTotalCrossSection( adjoint_photon );

  TEST_FLOATING_EQUALITY( cross_section, 2.1567210358522892, 1e-12 );

  adjoint_photon.setEnergy( 20.0 );

  cross_section =
    collision_handler->getMacroscopicTotalCrossSection( adjoint_photon );

  TEST_FLOATING_EQUALITY( cross_section, 4.2078239999303496e-07, 1e-12 );

  adjoint_photon.setCell( 3 );
  adjoint_photon.setEnergy( 1e-3 );

  cross_section =
    collision_handler->getMacroscopicTotalCrossSection( adjoint_photon );

  TEST_FLOATING_EQUALITY( cross_section, 2.1567210358522892, 1e-12 );

  adjoint_photon.setEnergy( 20.0 );

  cross_section =
    collision_handler->getMacroscopicTotalCrossSection( adjoint_photon );

  TEST_FLOATING_EQUALITY( cross_section, 4.2078239999303496e-07, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total forward cross section in a cell can be
// retrieved
TEUCHOS_UNIT_TEST( AdjointPhotonCollisionHandler,
                   getMacroscopicTotalForwardCrossSection )
{
  MonteCarlo::AdjointPhotonState adjoint_photon( 0 );
  adjoint_photon.setEnergy( 1e-3 );
  adjoint_photon.setCell( 1 );

  double cross_section =
    collision_handler->getMacroscopicTotalForwardCrossSection( adjoint_photon );

  TEST_FLOATING_EQUALITY( cross_section, 1568.1797769044053, 1e-12 );

  adjoint_photon.setEnergy( 20.0 );

  cross_section =
    collision_handler->getMacroscopicTotalForwardCrossSection( adjoint_photon );

  TEST_FLOATING_EQUALITY( cross_section, 0.02332997862851693, 1e-12 );

  adjoint_photon.setCell( 2 );
  adjoint_photon.setEnergy( 1e-3 );

  cross_section =
    collision_handler->getMacroscopicTotalForwardCrossSection( adjoint_photon );

  TEST_FLOATING_EQUALITY( cross_section, 1568.1797769044053, 1e-12 );

  adjoint_photon.setEnergy( 20.0 );

  cross_section =
    collision_handler->getMacroscopicTotalForwardCrossSection( adjoint_photon );

  TEST_FLOATING_EQUALITY( cross_section, 0.02332997862851693, 1e-12 );

  adjoint_photon.setCell( 3 );
  adjoint_photon.setEnergy( 1e-3 );

  cross_section =
    collision_handler->getMacroscopicTotalForwardCrossSection( adjoint_photon );

  TEST_FLOATING_EQUALITY( cross_section, 1568.1797769044053, 1e-12 );

  adjoint_photon.setEnergy( 20.0 );

  cross_section =
    collision_handler->getMacroscopicTotalForwardCrossSection( adjoint_photon );

  TEST_FLOATING_EQUALITY( cross_section, 0.02332997862851693, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic reaction cross section in a cell can be
// retrieved
TEUCHOS_UNIT_TEST( AdjointPhotonCollisionHandler,
                   getMacroscopicReactionCrossSection )
{
  MonteCarlo::AdjointPhotonState adjoint_photon( 0 );
  adjoint_photon.setEnergy( 1e-3 );
  adjoint_photon.setCell( 1 );

  double cross_section =
    collision_handler->getMacroscopicReactionCrossSection(
                              adjoint_photon,
                              MonteCarlo::TOTAL_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.1567210358522892, 1e-12 );

  adjoint_photon.setEnergy( 20.0 );
  
  cross_section = collision_handler->getMacroscopicReactionCrossSection(
                              adjoint_photon,
                              MonteCarlo::TOTAL_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 4.2078239999303496e-07, 1e-12 );

  adjoint_photon.setEnergy( 1e-3 );
  
  cross_section =
    collision_handler->getMacroscopicReactionCrossSection(
                   adjoint_photon,
                   MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.01331366707462057, 1e-12 );

  adjoint_photon.setEnergy( 20.0 );
  
  cross_section = collision_handler->getMacroscopicReactionCrossSection(
                   adjoint_photon,
                   MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  adjoint_photon.setEnergy( 1e-3 );
  
  cross_section =
    collision_handler->getMacroscopicReactionCrossSection(
                           adjoint_photon,
                           MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.1434073687776687, 1e-12 );

  adjoint_photon.setEnergy( 20.0 );
  
  cross_section = collision_handler->getMacroscopicReactionCrossSection(
                           adjoint_photon,
                           MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 4.2078239999303496e-07, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that an adjoint photon can collide with the material in a cell
TEUCHOS_UNIT_TEST( AdjointPhotonCollisionHandler,
                   collideWithCellMaterial_analogue )
{
  // Sample the incoherent reaction
  std::vector<double> fake_stream( 11 );
  fake_stream[0] = 0.99; // choose the only photoatom
  fake_stream[1] = 0.78; // choose incoherent scattering
  fake_stream[2] = 0.15; // branch 1
  fake_stream[3] = 0.4721647344828152; // select x = 0.9
  fake_stream[4] = 0.49; // accept
  fake_stream[5] = 0.91; // reject based on scattering function
  fake_stream[6] = 0.15; // branch 1
  fake_stream[7] = 0.4721647344828152; // select x = 0.9
  fake_stream[8] = 0.49; // accept
  fake_stream[9] = 0.909; // accept based on scattering function
  fake_stream[10] = 0.0;
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  MonteCarlo::AdjointPhotonState adjoint_photon( 0 );
  adjoint_photon.setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy/10.0 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );
  adjoint_photon.setWeight( 1.0 );
  adjoint_photon.setCell( 1 );

  MonteCarlo::ParticleBank bank;

  collision_handler->collideWithCellMaterial( adjoint_photon, bank );

  TEST_ASSERT( !adjoint_photon.isGone() );
  TEST_FLOATING_EQUALITY( adjoint_photon.getEnergy(),
			  0.05677765668111111,
			  1e-15 );
  TEST_FLOATING_EQUALITY( adjoint_photon.getWeight(),
                          0.571418454133749698,
                          1e-12 );
  TEST_EQUALITY_CONST( bank.size(), 0 );

  // Sample the coherent reaction
  fake_stream.resize( 7 );
  fake_stream[0] = 0.99; // choose the only photoatom
  fake_stream[1] = 0.79; // choose coherent scattering
  fake_stream[2] = 1.00475965594E-03; // sample form factor function squared (y = 1E6 cm)
  fake_stream[3] = 9.98800000000E-01; // reject the cosine scattering angle form function rejection loop
  fake_stream[4] = 6.50327467413E-01; // sample form factor function squared (y = 3E7 cm)
  fake_stream[5] = 5.07800000000E-01; // accept the cosine scattering angle form function rejection loop
  fake_stream[6] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  adjoint_photon.setEnergy( 4.95936772145E-03 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );
  adjoint_photon.setWeight( 1.0 );
  adjoint_photon.setCell( 1 );

  collision_handler->collideWithCellMaterial( adjoint_photon, bank );

  TEST_ASSERT( !adjoint_photon.isGone() );
  TEST_FLOATING_EQUALITY( adjoint_photon.getEnergy(),
			  4.95936772145E-03,
			  1e-15 );
  TEST_FLOATING_EQUALITY( adjoint_photon.getWeight(),
                          0.00554928318416651398,
                          1e-12 );
  TEST_EQUALITY_CONST( bank.size(), 0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that an adjoint photon can collide with the material in a cell
TEUCHOS_UNIT_TEST( AdjointPhotonCollisionHandler,
                   collideWithCellMaterial_survival_bias )
{
  // Reset the collision handler
  collision_handler.reset( new MonteCarlo::AdjointPhotonCollisionHandler( false ) );

  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>
    cells_containing_material( 3 );
  cells_containing_material[0] = 1;
  cells_containing_material[1] = 2;
  cells_containing_material[2] = 3;
  
  collision_handler->addMaterial( silicon, cells_containing_material );

  MonteCarlo::AdjointPhotonState adjoint_photon( 0 );
  adjoint_photon.setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy/10.0 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );
  adjoint_photon.setWeight( 1.0 );
  adjoint_photon.setCell( 1 );

  MonteCarlo::ParticleBank bank;

  collision_handler->collideWithCellMaterial( adjoint_photon, bank );

  TEST_FLOATING_EQUALITY( adjoint_photon.getWeight(),
                          0.571418454133749698,
                          1e-12 );

  adjoint_photon.setEnergy( 4.95936772145E-03 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );
  adjoint_photon.setWeight( 1.0 );
  adjoint_photon.setCell( 1 );

  collision_handler->collideWithCellMaterial( adjoint_photon, bank );

  TEST_FLOATING_EQUALITY( adjoint_photon.getWeight(),
                          0.00554928318416651398,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that an adjoint photon can collide with the material in a cell
// at a critical line energy
TEUCHOS_UNIT_TEST( AdjointPhotonCollisionHandler,
                   collideWithCellMaterial_line_energy )
{
  // Sample the pair production reaction
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 0.99; // select the only photoatom
  fake_stream[1] = 0.95; // select pair production
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  std::unique_ptr<MonteCarlo::AdjointPhotonState>
    adjoint_photon( new MonteCarlo::AdjointPhotonProbeState( 0 ) );
  adjoint_photon->setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy );
  adjoint_photon->setDirection( 0.0, 0.0, 1.0 );
  adjoint_photon->setWeight( 1.0 );
  adjoint_photon->setCell( 1 );

  MonteCarlo::ParticleBank bank;

  collision_handler->collideWithCellMaterial( *adjoint_photon, bank );

  TEST_ASSERT( adjoint_photon->isGone() );
  TEST_EQUALITY_CONST( bank.size(), 1 );
  TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 
                          2*Utility::PhysicalConstants::electron_rest_mass_energy,
                          1e-15 );
  out.precision( 18 );
  TEST_FLOATING_EQUALITY( bank.top().getWeight(),
                          3.80493907935216935,
                          1e-15 );

  bank.pop();

  // Sample the triplet production reaction
  fake_stream[0] = 0.99; // select the only photoatom
  fake_stream[1] = 0.96; // select triplet production
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  adjoint_photon.reset( new MonteCarlo::AdjointPhotonProbeState( 0 ) );
  adjoint_photon->setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy );
  adjoint_photon->setDirection( 0.0, 0.0, 1.0 );
  adjoint_photon->setWeight( 1.0 );
  adjoint_photon->setCell( 1 );

  collision_handler->collideWithCellMaterial( *adjoint_photon, bank );

  TEST_ASSERT( adjoint_photon->isGone() );
  TEST_EQUALITY_CONST( bank.size(), 1 );
  TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 
                          4*Utility::PhysicalConstants::electron_rest_mass_energy,
                          1e-15 );
  TEST_FLOATING_EQUALITY( bank.top().getWeight(),
                          3.80493907935216935,
                          1e-15 );

  bank.pop();

  Utility::RandomNumberGenerator::unsetFakeStream();

  // Make sure that a non-probe will not undergo a line energy reaction
  // even if it has the correct energy
  adjoint_photon.reset( new MonteCarlo::AdjointPhotonState( 0 ) );
  adjoint_photon->setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy );
  adjoint_photon->setDirection( 0.0, 0.0, 1.0 );
  adjoint_photon->setWeight( 1.0 );
  adjoint_photon->setCell( 1 );

  collision_handler->collideWithCellMaterial( *adjoint_photon, bank );

  TEST_ASSERT( !adjoint_photon->isGone() );
  TEST_FLOATING_EQUALITY( adjoint_photon->getWeight(),
                          3.03251221822496397,
                          1e-15 );
  TEST_EQUALITY_CONST( bank.size(), 0 );
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

  // Assign the atom fractions and names
  std::unordered_set<std::string> atom_aliases;
  atom_aliases.insert( "Si-Native" );

  Teuchos::Array<double> atom_fractions( 1 );
  Teuchos::Array<std::string> atom_names( 1 );

  atom_fractions[0] = -1.0; // weight fraction
  atom_names[0] = "Si-Native";

  // Create the atom factory
  MonteCarlo::SimulationProperties properties;
  properties.setMaxAdjointPhotonEnergy( 20.0 );
  properties.setNumberOfAdjointPhotonHashGridBins( 100 );
  properties.setIncoherentAdjointModelType( MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL );
  
  MonteCarlo::AdjointPhotoatomFactory factory(
                                             test_cross_sections_xml_directory,
                                             cross_section_table_info,
                                             atom_aliases,
                                             properties );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::AdjointPhotoatom> >
    adjoint_photoatom_map;

  factory.createAdjointPhotoatomMap( adjoint_photoatom_map );

  // Create silicon
  silicon.reset( new MonteCarlo::AdjointPhotonMaterial( 0,
                                                        -1.0,
                                                        adjoint_photoatom_map,
                                                        atom_fractions,
                                                        atom_names ) );

  // Initialize the collision handler
  collision_handler.reset( new MonteCarlo::AdjointPhotonCollisionHandler );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}


UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAdjointPhotonCollisionHandler.cpp
//---------------------------------------------------------------------------//
