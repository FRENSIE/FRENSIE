//---------------------------------------------------------------------------//
//!
//! \file   tstElectronCollisionHandler.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Electron collision handler class unit tests
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
#include "MonteCarlo_ElectroatomFactory.hpp"
#include "MonteCarlo_ElectronMaterial.hpp"
#include "MonteCarlo_ElectronCollisionHandler.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<const MonteCarlo::ElectronMaterial> lead;
std::shared_ptr<MonteCarlo::ElectronCollisionHandler> collision_handler;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that materials can be added to the collision handler
TEUCHOS_UNIT_TEST( ElectronCollisionHandler, addMaterial )
{
  TEST_ASSERT( collision_handler->isCellVoid( 1 ) );
  TEST_ASSERT( collision_handler->isCellVoid( 2 ) );
  TEST_ASSERT( collision_handler->isCellVoid( 3 ) );

  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>
    cells_containing_material( 3 );
  cells_containing_material[0] = 1;
  cells_containing_material[1] = 2;
  cells_containing_material[2] = 3;

  collision_handler->addMaterial( lead, cells_containing_material );

  TEST_ASSERT( !collision_handler->isCellVoid( 1 ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 2 ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 3 ) );
}

//---------------------------------------------------------------------------//
// Check that a material contained in a cell can be retrieved
TEUCHOS_UNIT_TEST( ElectronCollisionHandler, getMaterial )
{
  Teuchos::RCP<const MonteCarlo::ElectronMaterial> cell_material =
    collision_handler->getMaterial( 1 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 0 );
  TEST_EQUALITY_CONST( cell_material, lead );

  cell_material = collision_handler->getMaterial( 2 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 0 );
  TEST_EQUALITY_CONST( cell_material, lead );

  cell_material = collision_handler->getMaterial( 3 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 0 );
  TEST_EQUALITY_CONST( cell_material, lead );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total cross section in a cell can be retrieved
TEUCHOS_UNIT_TEST( ElectronCollisionHandler, getMacroscopicTotalCrossSection )
{
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.00000e-05 );
  electron.setCell( 1 );

  double cross_section =
    collision_handler->getMacroscopicTotalCrossSection( electron );

  TEST_FLOATING_EQUALITY( cross_section,
                          7.641204418336E+06,
                          1e-12 );

  electron.setEnergy( 1.00000e+05 );

  cross_section =
    collision_handler->getMacroscopicTotalCrossSection( electron );

  TEST_FLOATING_EQUALITY( cross_section,
                          8.269992326372E+03,
                          1e-12 );

  electron.setCell( 2 );
  electron.setEnergy( 1.00000e-05 );

  cross_section =
    collision_handler->getMacroscopicTotalCrossSection( electron );

  TEST_FLOATING_EQUALITY( cross_section,
                          7.641204418336E+06,
                          1e-12 );

  electron.setEnergy( 1.00000e+05 );

  cross_section =
    collision_handler->getMacroscopicTotalCrossSection( electron );

  TEST_FLOATING_EQUALITY( cross_section,
                          8.269992326372E+03,
                          1e-12 );

  electron.setCell( 3 );
  electron.setEnergy( 1.00000e-05 );

  cross_section =
    collision_handler->getMacroscopicTotalCrossSection( electron );

  TEST_FLOATING_EQUALITY( cross_section,
                          7.641204418336E+06,
                          1e-12 );

  electron.setEnergy( 1.00000e+05 );

  cross_section =
    collision_handler->getMacroscopicTotalCrossSection( electron );

  TEST_FLOATING_EQUALITY( cross_section,
                          8.269992326372E+03,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total forward cross section in a cell can be
// retrieved
TEUCHOS_UNIT_TEST( ElectronCollisionHandler,
                   getMacroscopicTotalForwardCrossSection )
{
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.00000e-05 );
  electron.setCell( 1 );

  double cross_section =
    collision_handler->getMacroscopicTotalForwardCrossSection( electron );

  TEST_FLOATING_EQUALITY( cross_section,
                          7.641204418336E+06,
                          1e-12 );

  electron.setEnergy( 1.00000e+05 );

  cross_section =
    collision_handler->getMacroscopicTotalForwardCrossSection( electron );

  TEST_FLOATING_EQUALITY( cross_section,
                          8.269992326372E+03,
                          1e-12 );

  electron.setCell( 2 );
  electron.setEnergy( 1.00000e-05 );

  cross_section =
    collision_handler->getMacroscopicTotalForwardCrossSection( electron );

  TEST_FLOATING_EQUALITY( cross_section,
                          7.641204418336E+06,
                          1e-12 );

  electron.setEnergy( 1.00000e+05 );

  cross_section =
    collision_handler->getMacroscopicTotalForwardCrossSection( electron );

  TEST_FLOATING_EQUALITY( cross_section,
                          8.269992326372E+03,
                          1e-12 );

  electron.setCell( 3 );
  electron.setEnergy( 1.00000e-05 );

  cross_section =
    collision_handler->getMacroscopicTotalForwardCrossSection( electron );

  TEST_FLOATING_EQUALITY( cross_section,
                          7.641204418336E+06,
                          1e-12 );

  electron.setEnergy( 1.00000e+05 );

  cross_section =
    collision_handler->getMacroscopicTotalForwardCrossSection( electron );

  TEST_FLOATING_EQUALITY( cross_section,
                          8.269992326372E+03,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic reaction cross section in a cell can be
// retrieved
TEUCHOS_UNIT_TEST( ElectronCollisionHandler,
                   getMacroscopicReactionCrossSection )
{
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.00000E-05 );
  electron.setCell( 1 );

  double cross_section =
    collision_handler->getMacroscopicReactionCrossSection(
				 electron,
				 MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.545329003693E+04, 1e-12 );
  
  electron.setEnergy( 1.00000E+05 );
  
  cross_section =
    collision_handler->getMacroscopicReactionCrossSection(
				 electron,
				 MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 4.588134602166E+03, 1e-12 );
  
  electron.setEnergy( 1.00000E-05 );
  
  cross_section =
    collision_handler->getMacroscopicReactionCrossSection(
				   electron,
				   MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.415377951846E+01, 1e-12 );
  
  electron.setEnergy( 1.00000E+05 );

  cross_section =
    collision_handler->getMacroscopicReactionCrossSection(
				   electron,
				   MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 5.679677054824E+00, 1e-12 );
  
  electron.setEnergy( 1.00000E-05 );
  
  cross_section =
    collision_handler->getMacroscopicReactionCrossSection(
		   electron,
		   MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );
  
  electron.setEnergy( 1.00000E+05 );
  
  cross_section =
    collision_handler->getMacroscopicReactionCrossSection(
		   electron,
		   MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.060615028974E-01, 1e-12 );
  
  electron.setEnergy( 1.00000E-05 );

  cross_section =
    collision_handler->getMacroscopicReactionCrossSection(
		  electron,
		  MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 3.096230095899E+05, 1e-12 );
  
  electron.setEnergy( 1.00000E+05 );

  cross_section =
    collision_handler->getMacroscopicReactionCrossSection(
		  electron,
		  MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 5.296521123591E+02, 1e-12 );
  
  double energy = 1.00000e-05;

  electron.setEnergy( energy );

  cross_section =
     collision_handler->getMacroscopicReactionCrossSection(
		  electron,
		  MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          7.234825686582E+06,
                          1e-12 );


  energy = 1.00000e+05;
  
  electron.setEnergy( energy );
  
  cross_section =
    collision_handler->getMacroscopicReactionCrossSection(
		  electron,
		  MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.566534386946E-04,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that an electron can collide with the material in a cell
//! \details This unit test is dependent on the version of boost being used.
TEUCHOS_UNIT_TEST( ElectronCollisionHandler,
                   collideWithCellMaterial_analogue )
{
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );
  electron.setWeight( 1.0 );
  electron.setCell( 1 );

  MonteCarlo::ParticleBank bank;

  // Set up the random number stream
  std::vector<double> fake_electron_stream( 3 );
  fake_electron_stream[0] = 0.5; // select the pb atom
  if( BOOST_VERSION < 106000 )
    fake_electron_stream[1] = 0.36; // select the elastic reaction (for boost below version 1.60)
  else
    fake_electron_stream[1] = 0.61; // select the elastic reaction (for boost above version 1.60)
  fake_electron_stream[2] = 0.5; // sample mu = 0.9874366113907

  Utility::RandomNumberGenerator::setFakeStream( fake_electron_stream );

  collision_handler->collideWithCellMaterial( electron, bank );

  //! \todo Double check the distribution type (Histogram)
  TEST_EQUALITY_CONST( electron.getEnergy(), 1e-3 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(),
			  0.9874366113907,
			  1e-12 );
  TEST_FLOATING_EQUALITY( electron.getWeight(), 1.0, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that an electron can collide with the material in a cell
TEUCHOS_UNIT_TEST( ElectronCollisionHandler,
                   collideWithCellMaterial_survival_bias )
{
  // Reset the collision handler
  collision_handler.reset( new MonteCarlo::ElectronCollisionHandler( false ) );

  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>
    cells_containing_material( 3 );
  cells_containing_material[0] = 1;
  cells_containing_material[1] = 2;
  cells_containing_material[2] = 3;
  
  collision_handler->addMaterial( lead, cells_containing_material );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 20.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );
  electron.setWeight( 1.0 );
  electron.setCell( 1 );

  MonteCarlo::ParticleBank bank;

  collision_handler->collideWithCellMaterial( electron, bank );
  
  TEST_FLOATING_EQUALITY( electron.getWeight(), 1.0, 1e-12 );
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
  atom_aliases.insert( "Pb" );
  
  Teuchos::Array<double> atom_fractions( 1 );
  Teuchos::Array<std::string> atom_names( 1 );
  
  atom_fractions[0] = -1.0; // weight fraction
  atom_names[0] = "Pb";

  // Create the atomic relaxation factory
  Teuchos::RCP<MonteCarlo::AtomicRelaxationModelFactory>
    atomic_relaxation_model_factory(
                                new MonteCarlo::AtomicRelaxationModelFactory );

  // Create the electroatom factory
  MonteCarlo::SimulationProperties properties;
  properties.setBremsstrahlungAngularDistributionFunction( MonteCarlo::TWOBS_DISTRIBUTION );
  properties.setElasticCutoffAngleCosine( 1.0 );
  properties.setAtomicRelaxationModeOn( MonteCarlo::ELECTRON );
  properties.setNumberOfElectronHashGridBins( 1000 );
  
  MonteCarlo::ElectroatomFactory electroatom_factory(
                                             test_cross_sections_xml_directory,
                                             cross_section_table_info,
                                             atom_aliases,
                                             atomic_relaxation_model_factory,
                                             properties );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Electroatom> >
    electroatom_map;

  electroatom_factory.createElectroatomMap( electroatom_map );
  
  // Create lead for electrons
  lead.reset( new MonteCarlo::ElectronMaterial( 0,
                                                -1.0,
                                                electroatom_map,
                                                atom_fractions,
                                                atom_names ) );

  // Initialize the collision handler
  collision_handler.reset( new MonteCarlo::ElectronCollisionHandler );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstElectronCollisionHandler.cpp
//---------------------------------------------------------------------------//
