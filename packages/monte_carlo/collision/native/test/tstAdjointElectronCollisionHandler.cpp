//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointElectronCollisionHandler.cpp
//! \author Luke Kersting
//! \brief  Adjoint electron collision handler class unit tests
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
#include "MonteCarlo_AdjointElectroatomFactory.hpp"
#include "MonteCarlo_AdjointElectronMaterial.hpp"
#include "MonteCarlo_AdjointElectronCollisionHandler.hpp"
#include "MonteCarlo_AdjointElectronProbeState.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

typedef boost::unordered_map<MonteCarlo::AdjointElectroatomicReactionType,
                           std::shared_ptr<const MonteCarlo::AdjointElectroatomicReaction> >
  ConstReactionMap;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

MonteCarlo::AdjointElectroatomCore silicon_core;
Teuchos::RCP<const MonteCarlo::AdjointElectronMaterial> silicon;
std::shared_ptr<MonteCarlo::AdjointElectronCollisionHandler> collision_handler;
double num_density;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that materials can be added to the collision handler
TEUCHOS_UNIT_TEST( AdjointElectronCollisionHandler, addMaterial )
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
TEUCHOS_UNIT_TEST( AdjointElectronCollisionHandler, getMaterial )
{
  Teuchos::RCP<const MonteCarlo::AdjointElectronMaterial> cell_material =
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
TEUCHOS_UNIT_TEST( AdjointElectronCollisionHandler,
                   getMacroscopicTotalCrossSection )
{
  MonteCarlo::AdjointElectronState adjoint_electron( 0 );
  adjoint_electron.setEnergy( 1e-3 );
  adjoint_electron.setCell( 1 );

  double cross_section =
    collision_handler->getMacroscopicTotalCrossSection( adjoint_electron );

  TEST_FLOATING_EQUALITY( cross_section, 2.8908200395739925e+08*num_density, 1e-12 );

  adjoint_electron.setEnergy( 20.0 );

  cross_section =
    collision_handler->getMacroscopicTotalCrossSection( adjoint_electron );

  TEST_FLOATING_EQUALITY( cross_section, 9.1185529218012723e+05*num_density, 1e-12 );

  adjoint_electron.setCell( 2 );
  adjoint_electron.setEnergy( 1e-3 );

  cross_section =
    collision_handler->getMacroscopicTotalCrossSection( adjoint_electron );

  TEST_FLOATING_EQUALITY( cross_section, 2.8908200395739925e+08*num_density, 1e-12 );

  adjoint_electron.setEnergy( 20.0 );

  cross_section =
    collision_handler->getMacroscopicTotalCrossSection( adjoint_electron );

  TEST_FLOATING_EQUALITY( cross_section, 9.1185529218012723e+05*num_density, 1e-12 );

  adjoint_electron.setCell( 3 );
  adjoint_electron.setEnergy( 1e-3 );

  cross_section =
    collision_handler->getMacroscopicTotalCrossSection( adjoint_electron );

  TEST_FLOATING_EQUALITY( cross_section, 2.8908200395739925e+08*num_density, 1e-12 );

  adjoint_electron.setEnergy( 20.0 );

  cross_section =
    collision_handler->getMacroscopicTotalCrossSection( adjoint_electron );

  TEST_FLOATING_EQUALITY( cross_section, 9.1185529218012723e+05*num_density, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total forward cross section in a cell can be
// retrieved
TEUCHOS_UNIT_TEST( AdjointElectronCollisionHandler,
                   getMacroscopicTotalForwardCrossSection )
{
  MonteCarlo::AdjointElectronState adjoint_electron( 0 );
  adjoint_electron.setEnergy( 1e-3 );
  adjoint_electron.setCell( 1 );

  double cross_section =
    collision_handler->getMacroscopicTotalForwardCrossSection( adjoint_electron );

  TEST_FLOATING_EQUALITY( cross_section, 3.2242787392660552e+08*num_density, 1e-12 );

  adjoint_electron.setEnergy( 20.0 );

  cross_section =
    collision_handler->getMacroscopicTotalForwardCrossSection( adjoint_electron );

  TEST_FLOATING_EQUALITY( cross_section, 1.2840414116627080e+06*num_density, 1e-12 );

  adjoint_electron.setCell( 2 );
  adjoint_electron.setEnergy( 1e-3 );

  cross_section =
    collision_handler->getMacroscopicTotalForwardCrossSection( adjoint_electron );

  TEST_FLOATING_EQUALITY( cross_section, 3.2242787392660552e+08*num_density, 1e-12 );

  adjoint_electron.setEnergy( 20.0 );

  cross_section =
    collision_handler->getMacroscopicTotalForwardCrossSection( adjoint_electron );

  TEST_FLOATING_EQUALITY( cross_section, 1.2840414116627080e+06*num_density, 1e-12 );

  adjoint_electron.setCell( 3 );
  adjoint_electron.setEnergy( 1e-3 );

  cross_section =
    collision_handler->getMacroscopicTotalForwardCrossSection( adjoint_electron );

  TEST_FLOATING_EQUALITY( cross_section, 3.2242787392660552e+08*num_density, 1e-12 );

  adjoint_electron.setEnergy( 20.0 );

  cross_section =
    collision_handler->getMacroscopicTotalForwardCrossSection( adjoint_electron );

  TEST_FLOATING_EQUALITY( cross_section, 1.2840414116627080e+06*num_density, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic reaction cross section in a cell can be
// retrieved
TEUCHOS_UNIT_TEST( AdjointElectronCollisionHandler,
                   getMacroscopicReactionCrossSection )
{
  MonteCarlo::AdjointElectronState adjoint_electron( 0 );
  adjoint_electron.setEnergy( 1e-3 );
  adjoint_electron.setCell( 1 );

  double cross_section =
    collision_handler->getMacroscopicReactionCrossSection(
              adjoint_electron,
              MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.2614892538788208e+08*num_density, 1e-12 );

  adjoint_electron.setEnergy( 20.0 );
  cross_section = collision_handler->getMacroscopicReactionCrossSection(
              adjoint_electron,
              MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 4.0100099282810203e+05*num_density, 1e-12 );

  adjoint_electron.setEnergy( 1e-3 );
  cross_section =
    collision_handler->getMacroscopicReactionCrossSection(
              adjoint_electron,
              MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 3.9820612307338689e+02*num_density, 1e-12 );

  adjoint_electron.setEnergy( 20.0 );
  cross_section = collision_handler->getMacroscopicReactionCrossSection(
              adjoint_electron,
              MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 8.5160362346724039*num_density, 1e-12 );

  adjoint_electron.setEnergy( 1e-3 );
  cross_section =
    collision_handler->getMacroscopicReactionCrossSection(
              adjoint_electron,
              MonteCarlo::COUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.3530678412550578e+08*num_density, 1e-12 );

  adjoint_electron.setEnergy( 20.0 );
  cross_section = collision_handler->getMacroscopicReactionCrossSection(
              adjoint_electron,
              MonteCarlo::COUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 4.2512515821171633e+05*num_density, 1e-12 );

  adjoint_electron.setEnergy( 1e-3 );
  cross_section =
    collision_handler->getMacroscopicReactionCrossSection(
              adjoint_electron,
              MonteCarlo::DECOUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  adjoint_electron.setEnergy( 20.0 );
  cross_section = collision_handler->getMacroscopicReactionCrossSection(
              adjoint_electron,
              MonteCarlo::DECOUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  adjoint_electron.setEnergy( 1e-3 );
  cross_section =
    collision_handler->getMacroscopicReactionCrossSection(
      adjoint_electron,
      MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.0490996365619276e+06*num_density, 1e-12 );

  adjoint_electron.setEnergy( 20.0 );
  cross_section = collision_handler->getMacroscopicReactionCrossSection(
      adjoint_electron,
      MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.7768342197055884e+02*num_density, 1e-12 );

  adjoint_electron.setEnergy( 1e-3 );
  cross_section =
    collision_handler->getMacroscopicReactionCrossSection(
      adjoint_electron,
      MonteCarlo::M3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 9.1448895633298811e+06*num_density, 1e-12 );

  adjoint_electron.setEnergy( 20.0 );
  cross_section = collision_handler->getMacroscopicReactionCrossSection(
      adjoint_electron,
      MonteCarlo::M3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 4.3042142907373425e+04*num_density, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that an adjoint electron can collide with the material in a cell
TEUCHOS_UNIT_TEST( AdjointElectronCollisionHandler,
                   collideWithCellMaterial_analogue )
{
  double energy = 1e-3;
  double sampling_ratio = 0.0;
  double partial_cross_section = 0.0;

  ConstReactionMap::const_iterator start =
    silicon_core.getScatteringReactions().begin();

  while( start != silicon_core.getScatteringReactions().end() )
  {
    double reaction_cross_section = start->second->getCrossSection( energy );

    if( start->first ==
        MonteCarlo::COUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION )
    {
      sampling_ratio = (partial_cross_section + 0.5*reaction_cross_section);
    }

    partial_cross_section += reaction_cross_section;
    ++start;
  }
  sampling_ratio /= partial_cross_section;

  // Sample the elastic reaction
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.99; // choose the only electroatom
  if( BOOST_VERSION < 106000 )
    fake_stream[1] = sampling_ratio; // select elastic (for boost below version 1.60)
  else
    fake_stream[1] = 1.0-sampling_ratio; // select elastic (for boost above version 1.60)
  fake_stream[2] = 0.0; // sample cutoff distribution
  fake_stream[3] = 0.0; // sample mu = -1.0


  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::AdjointElectronState adjoint_electron( 0 );
  adjoint_electron.setEnergy( energy );
  adjoint_electron.setDirection( 0.0, 0.0, 1.0 );
  adjoint_electron.setWeight( 1.0 );
  adjoint_electron.setCell( 1 );

  MonteCarlo::ParticleBank bank;

  collision_handler->collideWithCellMaterial( adjoint_electron, bank );

  TEST_ASSERT( !adjoint_electron.isGone() );
  TEST_FLOATING_EQUALITY( adjoint_electron.getEnergy(), 1e-3, 1e-15 );
  TEST_FLOATING_EQUALITY( adjoint_electron.getZDirection(), -1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( adjoint_electron.getWeight(),
                          8.9657882377502873e-01,
                          1e-12 );
  TEST_EQUALITY_CONST( bank.size(), 0 );

  energy = 1.55;
  sampling_ratio = 0.0;
  partial_cross_section = 0.0;

  start = silicon_core.getScatteringReactions().begin();

  while( start != silicon_core.getScatteringReactions().end() )
  {
    double reaction_cross_section = start->second->getCrossSection( energy );

    if( start->first ==
        MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION )
    {
      sampling_ratio = (partial_cross_section + 0.5*reaction_cross_section);
    }

    partial_cross_section += reaction_cross_section;
    ++start;
  }
  sampling_ratio /= partial_cross_section;

  // Sample the brem reaction
  fake_stream.resize( 3 );
  fake_stream[0] = 0.99; // choose the only electroatom
  if( BOOST_VERSION < 106000 )
    fake_stream[1] = sampling_ratio; // select brem (for boost below version 1.60)
  else
    fake_stream[1] = 1.0-sampling_ratio; // select brem (for boost above version 1.60)
  fake_stream[2] = 0.0; // sample outgoing energy = 1.5500002011844041

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  adjoint_electron.setEnergy( 1.55 );
  adjoint_electron.setDirection( 0.0, 0.0, 1.0 );
  adjoint_electron.setWeight( 1.0 );
  adjoint_electron.setCell( 1 );

  collision_handler->collideWithCellMaterial( adjoint_electron, bank );

  TEST_ASSERT( !adjoint_electron.isGone() );
  TEST_FLOATING_EQUALITY( adjoint_electron.getEnergy(),
                          1.5500002011844041,
                          1e-15 );
  TEST_FLOATING_EQUALITY( adjoint_electron.getZDirection(), 1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( adjoint_electron.getWeight(),
                          7.8002539212309341e-01,
                          1e-12 );
  TEST_EQUALITY_CONST( bank.size(), 0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that an adjoint electron can collide with the material in a cell
TEUCHOS_UNIT_TEST( AdjointElectronCollisionHandler,
                   collideWithCellMaterial_survival_bias )
{
  // Reset the collision handler
  collision_handler.reset( new MonteCarlo::AdjointElectronCollisionHandler( false ) );

  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>
    cells_containing_material( 3 );
  cells_containing_material[0] = 1;
  cells_containing_material[1] = 2;
  cells_containing_material[2] = 3;

  collision_handler->addMaterial( silicon, cells_containing_material );

  MonteCarlo::AdjointElectronState adjoint_electron( 0 );
  adjoint_electron.setEnergy( 1e-3 );
  adjoint_electron.setDirection( 0.0, 0.0, 1.0 );
  adjoint_electron.setWeight( 1.0 );
  adjoint_electron.setCell( 1 );

  MonteCarlo::ParticleBank bank;

  collision_handler->collideWithCellMaterial( adjoint_electron, bank );

  TEST_FLOATING_EQUALITY( adjoint_electron.getWeight(),
                          8.9657882377502873e-01,
                          1e-12 );

  adjoint_electron.setEnergy( 1.55 );
  adjoint_electron.setDirection( 0.0, 0.0, 1.0 );
  adjoint_electron.setWeight( 1.0 );
  adjoint_electron.setCell( 1 );

  collision_handler->collideWithCellMaterial( adjoint_electron, bank );

  TEST_FLOATING_EQUALITY( adjoint_electron.getWeight(),
                          7.8002539212309341e-01,
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

  // Assign the atom fractions and names
  std::unordered_set<std::string> atom_aliases;
  atom_aliases.insert( "Si-Native" );

  // Create the atom factory
  MonteCarlo::SimulationProperties properties;
  properties.setMaxAdjointElectronEnergy( 20.0 );
  properties.setNumberOfAdjointElectronHashGridBins( 100 );

  MonteCarlo::AdjointElectroatomFactory factory(
                                             test_cross_sections_xml_directory,
                                             cross_section_table_info,
                                             atom_aliases,
                                             properties );

std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::AdjointElectroatom> >
  adjoint_electroatom_map;

  factory.createAdjointElectroatomMap( adjoint_electroatom_map );

  silicon_core = adjoint_electroatom_map["Si-Native"]->getCore();

  Teuchos::Array<double> atom_fractions( 1 );
  Teuchos::Array<std::string> atom_names( 1 );

  atom_fractions[0] = -1.0; // weight fraction
  atom_names[0] = "Si-Native";

  // Create silicon
  silicon.reset( new MonteCarlo::AdjointElectronMaterial( 0,
                                                          -1.0,
                                                          adjoint_electroatom_map,
                                                          atom_fractions,
                                                          atom_names ) );

  num_density = silicon->getNumberDensity();

  // Initialize the collision handler
  collision_handler.reset( new MonteCarlo::AdjointElectronCollisionHandler );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}


UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAdjointElectronCollisionHandler.cpp
//---------------------------------------------------------------------------//
