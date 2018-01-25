//---------------------------------------------------------------------------//
//!
//! \file   tstPositronCollisionHandler.cpp
//! \author Luke Kersting
//! \brief  Positron collision handler class unit tests
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
#include "MonteCarlo_PositronatomFactory.hpp"
#include "MonteCarlo_PositronMaterial.hpp"
#include "MonteCarlo_PositronCollisionHandler.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<const MonteCarlo::PositronMaterial> lead;
std::shared_ptr<MonteCarlo::PositronCollisionHandler> collision_handler;

// //---------------------------------------------------------------------------//
// // Tests.
// //---------------------------------------------------------------------------//
// // Check that materials can be added to the collision handler
// TEUCHOS_UNIT_TEST( PositronCollisionHandler, addMaterial )
// {
//   TEST_ASSERT( collision_handler->isCellVoid( 1 ) );
//   TEST_ASSERT( collision_handler->isCellVoid( 2 ) );
//   TEST_ASSERT( collision_handler->isCellVoid( 3 ) );

//   Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>
//     cells_containing_material( 3 );
//   cells_containing_material[0] = 1;
//   cells_containing_material[1] = 2;
//   cells_containing_material[2] = 3;

//   collision_handler->addMaterial( lead, cells_containing_material );

//   TEST_ASSERT( !collision_handler->isCellVoid( 1 ) );
//   TEST_ASSERT( !collision_handler->isCellVoid( 2 ) );
//   TEST_ASSERT( !collision_handler->isCellVoid( 3 ) );
// }

// //---------------------------------------------------------------------------//
// // Check that a material contained in a cell can be retrieved
// TEUCHOS_UNIT_TEST( PositronCollisionHandler, getMaterial )
// {
//   Teuchos::RCP<const MonteCarlo::PositronMaterial> cell_material =
//     collision_handler->getMaterial( 1 );

//   TEST_ASSERT( !cell_material.is_null() );
//   TEST_EQUALITY_CONST( cell_material->getId(), 0 );
//   TEST_EQUALITY_CONST( cell_material, lead );

//   cell_material = collision_handler->getMaterial( 2 );

//   TEST_ASSERT( !cell_material.is_null() );
//   TEST_EQUALITY_CONST( cell_material->getId(), 0 );
//   TEST_EQUALITY_CONST( cell_material, lead );

//   cell_material = collision_handler->getMaterial( 3 );

//   TEST_ASSERT( !cell_material.is_null() );
//   TEST_EQUALITY_CONST( cell_material->getId(), 0 );
//   TEST_EQUALITY_CONST( cell_material, lead );
// }

// //---------------------------------------------------------------------------//
// // Check that the macroscopic total cross section in a cell can be retrieved
// TEUCHOS_UNIT_TEST( PositronCollisionHandler, getMacroscopicTotalCrossSection )
// {
//   MonteCarlo::PositronState positron( 0 );
//   positron.setEnergy( 1e-5 );
//   positron.setCell( 1 );

//   double cross_section =
//     collision_handler->getMacroscopicTotalCrossSection( positron );

//   TEST_FLOATING_EQUALITY( cross_section,
//                           7.641204418336E+06,
//                           1e-12 );

//   positron.setEnergy( 1e5 );

//   cross_section =
//     collision_handler->getMacroscopicTotalCrossSection( positron );

//   TEST_FLOATING_EQUALITY( cross_section,
//                           8.269992326372E+03,
//                           1e-12 );

//   positron.setCell( 2 );
//   positron.setEnergy( 1e-5 );

//   cross_section =
//     collision_handler->getMacroscopicTotalCrossSection( positron );

//   TEST_FLOATING_EQUALITY( cross_section,
//                           7.641204418336E+06,
//                           1e-12 );

//   positron.setEnergy( 1e5 );

//   cross_section =
//     collision_handler->getMacroscopicTotalCrossSection( positron );

//   TEST_FLOATING_EQUALITY( cross_section,
//                           8.269992326372E+03,
//                           1e-12 );

//   positron.setCell( 3 );
//   positron.setEnergy( 1e-5 );

//   cross_section =
//     collision_handler->getMacroscopicTotalCrossSection( positron );

//   TEST_FLOATING_EQUALITY( cross_section,
//                           7.641204418336E+06,
//                           1e-12 );

//   positron.setEnergy( 1e5 );

//   cross_section =
//     collision_handler->getMacroscopicTotalCrossSection( positron );

//   TEST_FLOATING_EQUALITY( cross_section,
//                           8.269992326372E+03,
//                           1e-12 );
// }

// //---------------------------------------------------------------------------//
// // Check that the macroscopic total forward cross section in a cell can be
// // retrieved
// TEUCHOS_UNIT_TEST( PositronCollisionHandler,
//                    getMacroscopicTotalForwardCrossSection )
// {
//   MonteCarlo::PositronState positron( 0 );
//   positron.setEnergy( 1e-5 );
//   positron.setCell( 1 );

//   double cross_section =
//     collision_handler->getMacroscopicTotalForwardCrossSection( positron );

//   TEST_FLOATING_EQUALITY( cross_section,
//                           7.641204418336E+06,
//                           1e-12 );

//   positron.setEnergy( 1e5 );

//   cross_section =
//     collision_handler->getMacroscopicTotalForwardCrossSection( positron );

//   TEST_FLOATING_EQUALITY( cross_section,
//                           8.269992326372E+03,
//                           1e-12 );

//   positron.setCell( 2 );
//   positron.setEnergy( 1e-5 );

//   cross_section =
//     collision_handler->getMacroscopicTotalForwardCrossSection( positron );

//   TEST_FLOATING_EQUALITY( cross_section,
//                           7.641204418336E+06,
//                           1e-12 );

//   positron.setEnergy( 1e5 );

//   cross_section =
//     collision_handler->getMacroscopicTotalForwardCrossSection( positron );

//   TEST_FLOATING_EQUALITY( cross_section,
//                           8.269992326372E+03,
//                           1e-12 );

//   positron.setCell( 3 );
//   positron.setEnergy( 1e-5 );

//   cross_section =
//     collision_handler->getMacroscopicTotalForwardCrossSection( positron );

//   TEST_FLOATING_EQUALITY( cross_section,
//                           7.641204418336E+06,
//                           1e-12 );

//   positron.setEnergy( 1e5 );

//   cross_section =
//     collision_handler->getMacroscopicTotalForwardCrossSection( positron );

//   TEST_FLOATING_EQUALITY( cross_section,
//                           8.269992326372E+03,
//                           1e-12 );
// }

// //---------------------------------------------------------------------------//
// // Check that the macroscopic reaction cross section in a cell can be
// // retrieved
// TEUCHOS_UNIT_TEST( PositronCollisionHandler,
//                    getMacroscopicReactionCrossSection )
// {
//   MonteCarlo::PositronState positron( 0 );
//   positron.setEnergy( 1e-5 );
//   positron.setCell( 1 );

//   double cross_section =
//     collision_handler->getMacroscopicReactionCrossSection(
// 				 positron,
// 				 MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION );

//   TEST_FLOATING_EQUALITY( cross_section, 2.545329003693E+04, 1e-12 );

//   positron.setEnergy( 1e5 );

//   cross_section =
//     collision_handler->getMacroscopicReactionCrossSection(
// 				 positron,
// 				 MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION );

//   TEST_FLOATING_EQUALITY( cross_section, 4.588134602166E+03, 1e-12 );

//   positron.setEnergy( 1e-5 );

//   cross_section =
//     collision_handler->getMacroscopicReactionCrossSection(
// 				   positron,
// 				   MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION );

//   TEST_FLOATING_EQUALITY( cross_section, 1.415377951846E+01, 1e-12 );

//   positron.setEnergy( 1e5 );

//   cross_section =
//     collision_handler->getMacroscopicReactionCrossSection(
// 				   positron,
// 				   MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION );

//   TEST_FLOATING_EQUALITY( cross_section, 5.679677054824E+00, 1e-12 );

//   positron.setEnergy( 1e-5 );

//   cross_section =
//     collision_handler->getMacroscopicReactionCrossSection(
// 		   positron,
// 		   MonteCarlo::K_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

//   TEST_EQUALITY_CONST( cross_section, 0.0 );

//   positron.setEnergy( 1e5 );

//   cross_section =
//     collision_handler->getMacroscopicReactionCrossSection(
// 		   positron,
// 		   MonteCarlo::K_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

//   TEST_FLOATING_EQUALITY( cross_section, 1.060615028974E-01, 1e-12 );

//   positron.setEnergy( 1e-5 );

//   cross_section =
//     collision_handler->getMacroscopicReactionCrossSection(
// 		  positron,
// 		  MonteCarlo::P3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

//   TEST_FLOATING_EQUALITY( cross_section, 3.096230095899E+05, 1e-12 );

//   positron.setEnergy( 1e5 );

//   cross_section =
//     collision_handler->getMacroscopicReactionCrossSection(
// 		  positron,
// 		  MonteCarlo::P3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

//   TEST_FLOATING_EQUALITY( cross_section, 5.296521123591E+02, 1e-12 );

//   positron.setEnergy( 1e-5 );

//   cross_section =
//      collision_handler->getMacroscopicReactionCrossSection(
// 		  positron,
// 		  MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION );

//   TEST_FLOATING_EQUALITY( cross_section,
//                           7.234825686582E+06,
//                           1e-12 );

//   positron.setEnergy( 1e5 );

//   cross_section =
//     collision_handler->getMacroscopicReactionCrossSection(
// 		  positron,
// 		  MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION );

//   TEST_FLOATING_EQUALITY( cross_section,
//                           2.566534386946E-04,
//                           1e-12 );
// }

// //---------------------------------------------------------------------------//
// // Check that an positron can collide with the material in a cell
// //! \details This unit test is dependent on the version of boost being used.
// TEUCHOS_UNIT_TEST( PositronCollisionHandler,
//                    collideWithCellMaterial_analogue )
// {
//   MonteCarlo::PositronState positron( 0 );
//   positron.setEnergy( 1e-3 );
//   positron.setDirection( 0.0, 0.0, 1.0 );
//   positron.setWeight( 1.0 );
//   positron.setCell( 1 );

//   MonteCarlo::ParticleBank bank;

//   // Set up the random number stream
//   std::vector<double> fake_positron_stream( 3 );
//   fake_positron_stream[0] = 0.5; // select the pb atom
//   if( BOOST_VERSION < 106000 )
//     fake_positron_stream[1] = 0.36; // select the elastic reaction (for boost below version 1.60)
//   else
//     fake_positron_stream[1] = 0.61; // select the elastic reaction (for boost above version 1.60)
//   fake_positron_stream[2] = 0.5; // sample mu = 0.9874366113907

//   Utility::RandomNumberGenerator::setFakeStream( fake_positron_stream );

//   collision_handler->collideWithCellMaterial( positron, bank );

//   //! \todo Double check the distribution type (Histogram)
//   TEST_EQUALITY_CONST( positron.getEnergy(), 1e-3 );
//   TEST_FLOATING_EQUALITY( positron.getZDirection(),
// 			  0.9874366113907,
// 			  1e-12 );
//   TEST_FLOATING_EQUALITY( positron.getWeight(), 1.0, 1e-15 );

//   Utility::RandomNumberGenerator::unsetFakeStream();
// }

// //---------------------------------------------------------------------------//
// // Check that an positron can collide with the material in a cell
// TEUCHOS_UNIT_TEST( PositronCollisionHandler,
//                    collideWithCellMaterial_survival_bias )
// {
//   // Reset the collision handler
//   collision_handler.reset( new MonteCarlo::PositronCollisionHandler( false ) );

//   Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>
//     cells_containing_material( 3 );
//   cells_containing_material[0] = 1;
//   cells_containing_material[1] = 2;
//   cells_containing_material[2] = 3;

//   collision_handler->addMaterial( lead, cells_containing_material );

//   MonteCarlo::PositronState positron( 0 );
//   positron.setEnergy( 20.0 );
//   positron.setDirection( 0.0, 0.0, 1.0 );
//   positron.setWeight( 1.0 );
//   positron.setCell( 1 );

//   MonteCarlo::ParticleBank bank;

//   collision_handler->collideWithCellMaterial( positron, bank );

//   TEST_FLOATING_EQUALITY( positron.getWeight(), 1.0, 1e-12 );
// }

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

  // Create the positron-atom factory
  MonteCarlo::SimulationProperties properties;
  properties.setBremsstrahlungAngularDistributionFunction( MonteCarlo::TWOBS_DISTRIBUTION );
  properties.setElasticCutoffAngleCosine( 1.0 );
  properties.setAtomicRelaxationModeOn( MonteCarlo::ELECTRON );
  properties.setNumberOfElectronHashGridBins( 1000 );

  MonteCarlo::PositronatomFactory positronatom_factory(
                                             test_cross_sections_xml_directory,
                                             cross_section_table_info,
                                             atom_aliases,
                                             atomic_relaxation_model_factory,
                                             properties );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Positronatom> >
    positronatom_map;

  positronatom_factory.createPositronatomMap( positronatom_map );

  // Create lead for positrons
  lead.reset( new MonteCarlo::PositronMaterial( 0,
                                                -1.0,
                                                positronatom_map,
                                                atom_fractions,
                                                atom_names ) );

  // Initialize the collision handler
  collision_handler.reset( new MonteCarlo::PositronCollisionHandler );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstPositronCollisionHandler.cpp
//---------------------------------------------------------------------------//
