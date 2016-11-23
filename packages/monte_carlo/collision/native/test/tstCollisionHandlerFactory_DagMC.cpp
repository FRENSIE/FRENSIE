//---------------------------------------------------------------------------//
//!
//! \file   tstCollisionHandlerFactoryNeutronMode_DagMC.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  Collision handler factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_NuclideFactory.hpp"
#include "MonteCarlo_NeutronMaterial.hpp"
#include "MonteCarlo_CollisionHandlerFactory.hpp"
#include "MonteCarlo_StandardCollisionHandlerFactory_DagMC.hpp"
#include "MonteCarlo_SimulationGeneralProperties.hpp"
#include "Geometry_DagMCInstanceFactory.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
std::string test_cross_sections_xml_directory;
Teuchos::ParameterList cross_section_table_info;
Teuchos::ParameterList forward_material_reps;
Teuchos::ParameterList adjoint_material_reps;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the collision handler can be initialize with DagMC
TEUCHOS_UNIT_TEST( CollisionHandlerFactoryDagMC,
                   createHandler_neutron_mode_analogue )
{
  MonteCarlo::SimulationProperties properties;
  
  // Set the particle mode to NEUTRON_MODE
  properties.setParticleMode( MonteCarlo::NEUTRON_MODE );

  // Set the collision type to analogue
  properties.setAnalogueCaptureModeOn();

  std::shared_ptr<MonteCarlo::CollisionHandler> collision_handler =
    MonteCarlo::getCollisionHandlerFactoryInstance<Geometry::DagMC>( &out )->createHandler(
                                           forward_material_reps,
					   cross_section_table_info,
                                           properties,
					   test_cross_sections_xml_directory );

  std::shared_ptr<MonteCarlo::NeutronCollisionHandler>
    neutron_collision_handler = std::dynamic_pointer_cast<MonteCarlo::NeutronCollisionHandler>( collision_handler );
  
  TEST_ASSERT( !collision_handler->isCellVoid( 1, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( neutron_collision_handler->getMaterial( 1 )->getId(),
                       1 );
  
  TEST_ASSERT( !collision_handler->isCellVoid( 3, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( neutron_collision_handler->getMaterial( 3 )->getId(),
                       2 );
  
  TEST_ASSERT( !collision_handler->isCellVoid( 5, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( neutron_collision_handler->getMaterial( 5 )->getId(),
                       3 );
  
  TEST_ASSERT( !collision_handler->isCellVoid( 7, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( neutron_collision_handler->getMaterial( 7 )->getId(),
                       2 );
  
  TEST_ASSERT( !collision_handler->isCellVoid( 9, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( neutron_collision_handler->getMaterial( 9 )->getId(),
                       4 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::ELECTRON ) );

  // Verify that collisions are analogue
  MonteCarlo::NeutronState neutron( 0ull );
  neutron.setCell( 1 );
  neutron.setDirection( 0.0, 0.0, 1.0 );
  neutron.setEnergy( 1.0 );
  neutron.setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  collision_handler->collideWithCellMaterial( neutron, bank );

  TEST_EQUALITY_CONST( neutron.getWeight(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the collision handler can be initialize with DagMC
TEUCHOS_UNIT_TEST( CollisionHandlerFactoryDagMC,
                   createHandler_neutron_mode_implicit_capture )
{
  MonteCarlo::SimulationProperties properties;
  
  // Set the particle mode to NEUTRON_MODE
  properties.setParticleMode( MonteCarlo::NEUTRON_MODE );

  // Set the collision type to analogue
  properties.setImplicitCaptureModeOn();

  std::shared_ptr<MonteCarlo::CollisionHandler> collision_handler =
    MonteCarlo::getCollisionHandlerFactoryInstance<Geometry::DagMC>( &out )->createHandler(
                                           forward_material_reps,
					   cross_section_table_info,
                                           properties,
					   test_cross_sections_xml_directory );

  std::shared_ptr<MonteCarlo::NeutronCollisionHandler>
    neutron_collision_handler = std::dynamic_pointer_cast<MonteCarlo::NeutronCollisionHandler>( collision_handler );
  
  TEST_ASSERT( !collision_handler->isCellVoid( 1, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( neutron_collision_handler->getMaterial( 1 )->getId(),
                       1 );
  
  TEST_ASSERT( !collision_handler->isCellVoid( 3, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( neutron_collision_handler->getMaterial( 3 )->getId(),
                       2 );
  
  TEST_ASSERT( !collision_handler->isCellVoid( 5, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( neutron_collision_handler->getMaterial( 5 )->getId(),
                       3 );
  
  TEST_ASSERT( !collision_handler->isCellVoid( 7, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( neutron_collision_handler->getMaterial( 7 )->getId(),
                       2 );
  
  TEST_ASSERT( !collision_handler->isCellVoid( 9, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( neutron_collision_handler->getMaterial( 9 )->getId(),
                       4 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::ELECTRON ) );

  // Verify that capture is implicit
  MonteCarlo::NeutronState neutron( 0ull );
  neutron.setCell( 1 );
  neutron.setDirection( 0.0, 0.0, 1.0 );
  neutron.setEnergy( 1.0 );
  neutron.setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  collision_handler->collideWithCellMaterial( neutron, bank );

  TEST_ASSERT( neutron.getWeight() < 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the collision handler can be initialize with DagMC
TEUCHOS_UNIT_TEST( CollisionHandlerFactoryDagMC,
                   createHandler_photon_mode_analogue )
{
  MonteCarlo::SimulationProperties properties;
  
  // Set the particle mode to PHOTON_MODE
  properties.setParticleMode( MonteCarlo::PHOTON_MODE );

  // Set the collision type to analogue
  properties.setAnalogueCaptureModeOn();

  std::shared_ptr<MonteCarlo::CollisionHandler> collision_handler =
    MonteCarlo::getCollisionHandlerFactoryInstance<Geometry::DagMC>( &out )->createHandler(
                                           forward_material_reps,
					   cross_section_table_info,
                                           properties,
					   test_cross_sections_xml_directory );

  std::shared_ptr<MonteCarlo::PhotonCollisionHandler>
    photon_collision_handler = std::dynamic_pointer_cast<MonteCarlo::PhotonCollisionHandler>( collision_handler );
  
  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 1, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 1 )->getId(),
                       1 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 3, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 3 )->getId(),
                       2 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 5, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 5 )->getId(),
                       3 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 7, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 7 )->getId(),
                       2 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 9, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 9 )->getId(),
                       4 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::ELECTRON ) );

  // Verify that collisions are analogue
  MonteCarlo::PhotonState photon( 0ull );
  photon.setCell( 1 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  photon.setEnergy( 1.0 );
  photon.setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  collision_handler->collideWithCellMaterial( photon, bank );

  TEST_EQUALITY_CONST( photon.getWeight(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the collision handler can be initialize with DagMC
TEUCHOS_UNIT_TEST( CollisionHandlerFactoryDagMC,
                   createHandler_photon_mode_implicit_capture )
{
  MonteCarlo::SimulationProperties properties;
  
  // Set the particle mode to PHOTON_MODE
  properties.setParticleMode( MonteCarlo::PHOTON_MODE );

  // Set the collision type to analogue
  properties.setImplicitCaptureModeOn();

  std::shared_ptr<MonteCarlo::CollisionHandler> collision_handler =
    MonteCarlo::getCollisionHandlerFactoryInstance<Geometry::DagMC>( &out )->createHandler(
                                           forward_material_reps,
					   cross_section_table_info,
                                           properties,
					   test_cross_sections_xml_directory );

  std::shared_ptr<MonteCarlo::PhotonCollisionHandler>
    photon_collision_handler = std::dynamic_pointer_cast<MonteCarlo::PhotonCollisionHandler>( collision_handler );
  
  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 1, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 1 )->getId(),
                       1 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 3, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 3 )->getId(),
                       2 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 5, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 5 )->getId(),
                       3 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 7, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 7 )->getId(),
                       2 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 9, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 9 )->getId(),
                       4 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::ELECTRON ) );

  // Verify that capture is implicit 
  MonteCarlo::PhotonState photon( 0ull );
  photon.setCell( 1 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  photon.setEnergy( 1.0 );
  photon.setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  collision_handler->collideWithCellMaterial( photon, bank );

  TEST_ASSERT( photon.getWeight() < 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the collision handler can be initialize with DagMC
TEUCHOS_UNIT_TEST( CollisionHandlerFactoryDagMC,
                   createHandler_adjoint_photon_mode_analogue )
{
  MonteCarlo::SimulationProperties properties;
  
  // Set the particle mode to ADJOINT_PHOTON_MODE
  properties.setParticleMode( MonteCarlo::ADJOINT_PHOTON_MODE );

  // Set the collision type to analogue
  properties.setAnalogueCaptureModeOn();

  std::shared_ptr<MonteCarlo::CollisionHandler> collision_handler =
    MonteCarlo::getCollisionHandlerFactoryInstance<Geometry::DagMC>( &out )->createHandler(
                                           adjoint_material_reps,
					   cross_section_table_info,
                                           properties,
					   test_cross_sections_xml_directory );

  std::shared_ptr<MonteCarlo::AdjointPhotonCollisionHandler>
    adjoint_photon_collision_handler = std::dynamic_pointer_cast<MonteCarlo::AdjointPhotonCollisionHandler>( collision_handler );
  
  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 1, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( adjoint_photon_collision_handler->getMaterial( 1 )->getId(),
                       1 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 3, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( adjoint_photon_collision_handler->getMaterial( 3 )->getId(),
                       2 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 5, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( adjoint_photon_collision_handler->getMaterial( 5 )->getId(),
                       3 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 7, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( adjoint_photon_collision_handler->getMaterial( 7 )->getId(),
                       2 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 9, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( adjoint_photon_collision_handler->getMaterial( 9 )->getId(),
                       4 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::ELECTRON ) );

  // Verify that collisions are analogue
  MonteCarlo::AdjointPhotonState adjoint_photon( 0ull );
  adjoint_photon.setCell( 1 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );
  adjoint_photon.setEnergy( 1.0 );
  adjoint_photon.setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  collision_handler->collideWithCellMaterial( adjoint_photon, bank );

  // The adjoint weight factor at 1.0 MeV will cause a weight greater than 1.0
  TEST_ASSERT( adjoint_photon.getWeight() > 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the collision handler can be initialize with DagMC
TEUCHOS_UNIT_TEST( CollisionHandlerFactoryDagMC,
                   createHandler_adjoint_photon_mode_implicit_capture )
{
  MonteCarlo::SimulationProperties properties;
  
  // Set the particle mode to ADJOINT_PHOTON_MODE
  properties.setParticleMode( MonteCarlo::ADJOINT_PHOTON_MODE );

  // Set the collision type to implicit capture
  properties.setImplicitCaptureModeOn();

  std::shared_ptr<MonteCarlo::CollisionHandler> collision_handler =
    MonteCarlo::getCollisionHandlerFactoryInstance<Geometry::DagMC>( &out )->createHandler(
                                           adjoint_material_reps,
					   cross_section_table_info,
                                           properties,
					   test_cross_sections_xml_directory );

  std::shared_ptr<MonteCarlo::AdjointPhotonCollisionHandler>
    adjoint_photon_collision_handler = std::dynamic_pointer_cast<MonteCarlo::AdjointPhotonCollisionHandler>( collision_handler );
  
  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 1, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( adjoint_photon_collision_handler->getMaterial( 1 )->getId(),
                       1 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 3, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( adjoint_photon_collision_handler->getMaterial( 3 )->getId(),
                       2 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 5, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( adjoint_photon_collision_handler->getMaterial( 5 )->getId(),
                       3 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 7, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( adjoint_photon_collision_handler->getMaterial( 7 )->getId(),
                       2 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 9, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( adjoint_photon_collision_handler->getMaterial( 9 )->getId(),
                       4 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::ELECTRON ) );

  // Verify that collisions are analogue
  MonteCarlo::AdjointPhotonState adjoint_photon( 0ull );
  adjoint_photon.setCell( 1 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );
  adjoint_photon.setEnergy( 1.0 );
  adjoint_photon.setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  collision_handler->collideWithCellMaterial( adjoint_photon, bank );

  // The adjoint weight factor at 1.0 MeV will cause a weight greater than 1.0.
  TEST_ASSERT( adjoint_photon.getWeight() > 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the collision handler can be initialize with DagMC
TEUCHOS_UNIT_TEST( CollisionHandlerFactoryDagMC,
                   createHandler_electron_mode_analogue )
{
  MonteCarlo::SimulationProperties properties;
  
  // Set the particle mode to ELECTRON_MODE
  properties.setParticleMode( MonteCarlo::ELECTRON_MODE );

  // Set the collision type to analogue
  properties.setAnalogueCaptureModeOn();

  std::shared_ptr<MonteCarlo::CollisionHandler> collision_handler =
    MonteCarlo::getCollisionHandlerFactoryInstance<Geometry::DagMC>( &out )->createHandler(
                                           forward_material_reps,
					   cross_section_table_info,
                                           properties,
					   test_cross_sections_xml_directory );

  std::shared_ptr<MonteCarlo::ElectronCollisionHandler>
    electron_collision_handler = std::dynamic_pointer_cast<MonteCarlo::ElectronCollisionHandler>( collision_handler );
  
  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( !collision_handler->isCellVoid( 1, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( electron_collision_handler->getMaterial( 1 )->getId(),
                       1 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( !collision_handler->isCellVoid( 3, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( electron_collision_handler->getMaterial( 3 )->getId(),
                       2 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( !collision_handler->isCellVoid( 5, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( electron_collision_handler->getMaterial( 5 )->getId(),
                       3 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( !collision_handler->isCellVoid( 7, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( electron_collision_handler->getMaterial( 7 )->getId(),
                       2 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( !collision_handler->isCellVoid( 9, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( electron_collision_handler->getMaterial( 9 )->getId(),
                       4 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::ELECTRON ) );

  // Verify that collisions are analogue
  MonteCarlo::ElectronState electron( 0ull );
  electron.setCell( 1 );
  electron.setDirection( 0.0, 0.0, 1.0 );
  electron.setEnergy( 1.0 );
  electron.setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  collision_handler->collideWithCellMaterial( electron, bank );

  TEST_EQUALITY_CONST( electron.getWeight(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the collision handler can be initialize with DagMC
TEUCHOS_UNIT_TEST( CollisionHandlerFactoryDagMC,
                   createHandler_electron_mode_implicit_capture )
{
  MonteCarlo::SimulationProperties properties;
  
  // Set the particle mode to ELECTRON_MODE
  properties.setParticleMode( MonteCarlo::ELECTRON_MODE );

  // Set the collision type to analogue
  properties.setImplicitCaptureModeOn();

  std::shared_ptr<MonteCarlo::CollisionHandler> collision_handler =
    MonteCarlo::getCollisionHandlerFactoryInstance<Geometry::DagMC>( &out )->createHandler(
                                           forward_material_reps,
					   cross_section_table_info,
                                           properties,
					   test_cross_sections_xml_directory );

  std::shared_ptr<MonteCarlo::ElectronCollisionHandler>
    electron_collision_handler = std::dynamic_pointer_cast<MonteCarlo::ElectronCollisionHandler>( collision_handler );
  
  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( !collision_handler->isCellVoid( 1, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( electron_collision_handler->getMaterial( 1 )->getId(),
                       1 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( !collision_handler->isCellVoid( 3, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( electron_collision_handler->getMaterial( 3 )->getId(),
                       2 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( !collision_handler->isCellVoid( 5, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( electron_collision_handler->getMaterial( 5 )->getId(),
                       3 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( !collision_handler->isCellVoid( 7, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( electron_collision_handler->getMaterial( 7 )->getId(),
                       2 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( !collision_handler->isCellVoid( 9, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( electron_collision_handler->getMaterial( 9 )->getId(),
                       4 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::ELECTRON ) );

  // Verify that capture is implicit
  MonteCarlo::ElectronState electron( 0ull );
  electron.setCell( 1 );
  electron.setDirection( 0.0, 0.0, 1.0 );
  electron.setEnergy( 1.0 );
  electron.setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  collision_handler->collideWithCellMaterial( electron, bank );

  // There is no absorption reaction with electrons
  TEST_EQUALITY_CONST( electron.getWeight(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the collision handler can be initialize with DagMC
TEUCHOS_UNIT_TEST( CollisionHandlerFactoryDagMC,
                   createHandler_neutron_photon_mode_analogue )
{
  MonteCarlo::SimulationProperties properties;
  
  // Set the particle mode to NEUTRON_PHOTON_MODE
  properties.setParticleMode( MonteCarlo::NEUTRON_PHOTON_MODE );

  // Set the collision type to analogue
  properties.setAnalogueCaptureModeOn();

  std::shared_ptr<MonteCarlo::CollisionHandler> collision_handler;

  // Note: The photon production cross sections for H-1 have multiple
  // interpolation regions, which cannot currently be parsed
  TEST_THROW( collision_handler = MonteCarlo::getCollisionHandlerFactoryInstance<Geometry::DagMC>( &out )->createHandler(
                                           forward_material_reps,
					   cross_section_table_info,
                                           properties,
					   test_cross_sections_xml_directory ),
              std::runtime_error );

  // std::shared_ptr<MonteCarlo::NeutronCollisionHandler>
  //   neutron_collision_handler = std::dynamic_pointer_cast<MonteCarlo::NeutronCollisionHandler>( collision_handler );

  // std::shared_ptr<MonteCarlo::PhotonCollisionHandler>
  //   photon_collision_handler = std::dynamic_pointer_cast<MonteCarlo::PhotonCollisionHandler>( collision_handler );
  
  // TEST_ASSERT( !collision_handler->isCellVoid( 1, MonteCarlo::NEUTRON ) );
  // TEST_ASSERT( !collision_handler->isCellVoid( 1, MonteCarlo::PHOTON ) );
  // TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::ADJOINT_PHOTON ));
  // TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::ELECTRON ) );
  // TEST_EQUALITY_CONST( neutron_collision_handler->getMaterial( 1 )->getId(),
  //                      1 );
  // TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 1 )->getId(),
  //                      1 );
  
  // TEST_ASSERT( !collision_handler->isCellVoid( 3, MonteCarlo::NEUTRON ) );
  // TEST_ASSERT( !collision_handler->isCellVoid( 3, MonteCarlo::PHOTON ) );
  // TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::ADJOINT_PHOTON ));
  // TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::ELECTRON ) );
  // TEST_EQUALITY_CONST( neutron_collision_handler->getMaterial( 3 )->getId(),
  //                      2 );
  // TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 3 )->getId(),
  //                      2 );
  
  // TEST_ASSERT( !collision_handler->isCellVoid( 5, MonteCarlo::NEUTRON ) );
  // TEST_ASSERT( !collision_handler->isCellVoid( 5, MonteCarlo::PHOTON ) );
  // TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::ADJOINT_PHOTON ));
  // TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::ELECTRON ) );
  // TEST_EQUALITY_CONST( neutron_collision_handler->getMaterial( 5 )->getId(),
  //                      3 );
  // TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 5 )->getId(),
  //                      3 );
  
  // TEST_ASSERT( !collision_handler->isCellVoid( 7, MonteCarlo::NEUTRON ) );
  // TEST_ASSERT( !collision_handler->isCellVoid( 7, MonteCarlo::PHOTON ) );
  // TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::ADJOINT_PHOTON ));
  // TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::ELECTRON ) );
  // TEST_EQUALITY_CONST( neutron_collision_handler->getMaterial( 7 )->getId(),
  //                      2 );
  // TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 7 )->getId(),
  //                      2 );
  
  // TEST_ASSERT( !collision_handler->isCellVoid( 9, MonteCarlo::NEUTRON ) );
  // TEST_ASSERT( !collision_handler->isCellVoid( 9, MonteCarlo::PHOTON ) );
  // TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::ADJOINT_PHOTON ));
  // TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::ELECTRON ) );
  // TEST_EQUALITY_CONST( neutron_collision_handler->getMaterial( 9 )->getId(),
  //                      4 );
  // TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 9 )->getId(),
  //                      4 );
  
  // TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::NEUTRON ) );
  // TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::PHOTON ) );
  // TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::ADJOINT_PHOTON ));
  // TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::ELECTRON ) );

  // // Verify that collisions are analogue
  // MonteCarlo::NeutronState neutron( 0ull );
  // neutron.setCell( 1 );
  // neutron.setDirection( 0.0, 0.0, 1.0 );
  // neutron.setEnergy( 1.0 );
  // neutron.setWeight( 1.0 );

  // MonteCarlo::PhotonState photon( 1ull );
  // photon.setCell( 1 );
  // photon.setDirection( 0.0, 0.0, 1.0 );
  // photon.setEnergy( 1.0 );
  // photon.setWeight( 1.0 );

  // MonteCarlo::ParticleBank bank;

  // collision_handler->collideWithCellMaterial( neutron, bank );

  // TEST_EQUALITY_CONST( neutron.getWeight(), 1.0 );

  // collision_handler->collideWithCellMaterial( photon, bank );

  // TEST_EQUALITY_CONST( photon.getWeight(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the collision handler can be initialize with DagMC
TEUCHOS_UNIT_TEST( CollisionHandlerFactoryDagMC,
                   createHandler_neutron_photon_mode_implicit_capture )
{
  MonteCarlo::SimulationProperties properties;
  
  // Set the particle mode to NEUTRON_PHOTON_MODE
  properties.setParticleMode( MonteCarlo::NEUTRON_PHOTON_MODE );

  // Set the collision type to implicit capture
  properties.setImplicitCaptureModeOn();

  std::shared_ptr<MonteCarlo::CollisionHandler> collision_handler;

  // Note: The photon production cross sections for H-1 have multiple
  // interpolation regions, which cannot currently be parsed
  TEST_THROW( collision_handler = MonteCarlo::getCollisionHandlerFactoryInstance<Geometry::DagMC>( &out )->createHandler(
                                           forward_material_reps,
					   cross_section_table_info,
                                           properties,
					   test_cross_sections_xml_directory ),
              std::runtime_error );

  // std::shared_ptr<MonteCarlo::NeutronCollisionHandler>
  //   neutron_collision_handler = std::dynamic_pointer_cast<MonteCarlo::NeutronCollisionHandler>( collision_handler );

  // std::shared_ptr<MonteCarlo::PhotonCollisionHandler>
  //   photon_collision_handler = std::dynamic_pointer_cast<MonteCarlo::PhotonCollisionHandler>( collision_handler );
  
  // TEST_ASSERT( !collision_handler->isCellVoid( 1, MonteCarlo::NEUTRON ) );
  // TEST_ASSERT( !collision_handler->isCellVoid( 1, MonteCarlo::PHOTON ) );
  // TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::ADJOINT_PHOTON ));
  // TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::ELECTRON ) );
  // TEST_EQUALITY_CONST( neutron_collision_handler->getMaterial( 1 )->getId(),
  //                      1 );
  // TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 1 )->getId(),
  //                      1 );
  
  // TEST_ASSERT( !collision_handler->isCellVoid( 3, MonteCarlo::NEUTRON ) );
  // TEST_ASSERT( !collision_handler->isCellVoid( 3, MonteCarlo::PHOTON ) );
  // TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::ADJOINT_PHOTON ));
  // TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::ELECTRON ) );
  // TEST_EQUALITY_CONST( neutron_collision_handler->getMaterial( 3 )->getId(),
  //                      2 );
  // TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 3 )->getId(),
  //                      2 );
  
  // TEST_ASSERT( !collision_handler->isCellVoid( 5, MonteCarlo::NEUTRON ) );
  // TEST_ASSERT( !collision_handler->isCellVoid( 5, MonteCarlo::PHOTON ) );
  // TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::ADJOINT_PHOTON ));
  // TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::ELECTRON ) );
  // TEST_EQUALITY_CONST( neutron_collision_handler->getMaterial( 5 )->getId(),
  //                      3 );
  // TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 5 )->getId(),
  //                      3 );
  
  // TEST_ASSERT( !collision_handler->isCellVoid( 7, MonteCarlo::NEUTRON ) );
  // TEST_ASSERT( !collision_handler->isCellVoid( 7, MonteCarlo::PHOTON ) );
  // TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::ADJOINT_PHOTON ));
  // TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::ELECTRON ) );
  // TEST_EQUALITY_CONST( neutron_collision_handler->getMaterial( 7 )->getId(),
  //                      2 );
  // TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 7 )->getId(),
  //                      2 );
  
  // TEST_ASSERT( !collision_handler->isCellVoid( 9, MonteCarlo::NEUTRON ) );
  // TEST_ASSERT( !collision_handler->isCellVoid( 9, MonteCarlo::PHOTON ) );
  // TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::ADJOINT_PHOTON ));
  // TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::ELECTRON ) );
  // TEST_EQUALITY_CONST( neutron_collision_handler->getMaterial( 9 )->getId(),
  //                      4 );
  // TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 9 )->getId(),
  //                      4 );
  
  // TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::NEUTRON ) );
  // TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::PHOTON ) );
  // TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::ADJOINT_PHOTON ));
  // TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::ELECTRON ) );

  // // Verify that capture is implicit
  // MonteCarlo::NeutronState neutron( 0ull );
  // neutron.setCell( 1 );
  // neutron.setDirection( 0.0, 0.0, 1.0 );
  // neutron.setEnergy( 1.0 );
  // neutron.setWeight( 1.0 );

  // MonteCarlo::PhotonState photon( 1ull );
  // photon.setCell( 1 );
  // photon.setDirection( 0.0, 0.0, 1.0 );
  // photon.setEnergy( 1.0 );
  // photon.setWeight( 1.0 );

  // MonteCarlo::ParticleBank bank;

  // collision_handler->collideWithCellMaterial( neutron, bank );

  // TEST_ASSERT( neutron.getWeight() < 1.0 );

  // collision_handler->collideWithCellMaterial( photon, bank );

  // TEST_ASSERT( photon.getWeight() < 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the collision handler can be initialize with DagMC
TEUCHOS_UNIT_TEST( CollisionHandlerFactoryDagMC,
                   createHandler_photon_electron_mode_analogue )
{
  MonteCarlo::SimulationProperties properties;
  
  // Set the particle mode to PHOTON_ELECTRON_MODE
  properties.setParticleMode( MonteCarlo::PHOTON_ELECTRON_MODE );

  // Set the collision type to analogue
  properties.setAnalogueCaptureModeOn();

  std::shared_ptr<MonteCarlo::CollisionHandler> collision_handler =
    MonteCarlo::getCollisionHandlerFactoryInstance<Geometry::DagMC>( &out )->createHandler(
                                           forward_material_reps,
					   cross_section_table_info,
                                           properties,
					   test_cross_sections_xml_directory );

  std::shared_ptr<MonteCarlo::PhotonCollisionHandler>
    photon_collision_handler = std::dynamic_pointer_cast<MonteCarlo::PhotonCollisionHandler>( collision_handler );

  std::shared_ptr<MonteCarlo::ElectronCollisionHandler>
    electron_collision_handler = std::dynamic_pointer_cast<MonteCarlo::ElectronCollisionHandler>( collision_handler );
  
  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 1, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( !collision_handler->isCellVoid( 1, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 1 )->getId(),
                       1 );
  TEST_EQUALITY_CONST( electron_collision_handler->getMaterial( 1 )->getId(),
                       1 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 3, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( !collision_handler->isCellVoid( 3, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 3 )->getId(),
                       2 );
  TEST_EQUALITY_CONST( electron_collision_handler->getMaterial( 3 )->getId(),
                       2 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 5, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( !collision_handler->isCellVoid( 5, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 5 )->getId(),
                       3 );
  TEST_EQUALITY_CONST( electron_collision_handler->getMaterial( 5 )->getId(),
                       3 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 7, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( !collision_handler->isCellVoid( 7, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 7 )->getId(),
                       2 );
  TEST_EQUALITY_CONST( electron_collision_handler->getMaterial( 7 )->getId(),
                       2 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 9, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( !collision_handler->isCellVoid( 9, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 9 )->getId(),
                       4 );
  TEST_EQUALITY_CONST( electron_collision_handler->getMaterial( 9 )->getId(),
                       4 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::ELECTRON ) );

  // Verify that collisions are analogue
  MonteCarlo::PhotonState photon( 0ull );
  photon.setCell( 1 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  photon.setEnergy( 1.0 );
  photon.setWeight( 1.0 );

  MonteCarlo::ElectronState electron( 1ull );
  electron.setCell( 1 );
  electron.setDirection( 0.0, 0.0, 1.0 );
  electron.setEnergy( 1.0 );
  electron.setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  collision_handler->collideWithCellMaterial( photon, bank );

  TEST_EQUALITY_CONST( photon.getWeight(), 1.0 );

  collision_handler->collideWithCellMaterial( electron, bank );

  TEST_EQUALITY_CONST( electron.getWeight(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the collision handler can be initialize with DagMC
TEUCHOS_UNIT_TEST( CollisionHandlerFactoryDagMC,
                   createHandler_photon_electron_mode_implicit_capture )
{
  MonteCarlo::SimulationProperties properties;
  
  // Set the particle mode to PHOTON_ELECTRON_MODE
  properties.setParticleMode( MonteCarlo::PHOTON_ELECTRON_MODE );

  // Set the collision type to implicit capture
  properties.setImplicitCaptureModeOn();

  std::shared_ptr<MonteCarlo::CollisionHandler> collision_handler =
    MonteCarlo::getCollisionHandlerFactoryInstance<Geometry::DagMC>( &out )->createHandler(
                                           forward_material_reps,
					   cross_section_table_info,
                                           properties,
					   test_cross_sections_xml_directory );

  std::shared_ptr<MonteCarlo::PhotonCollisionHandler>
    photon_collision_handler = std::dynamic_pointer_cast<MonteCarlo::PhotonCollisionHandler>( collision_handler );

  std::shared_ptr<MonteCarlo::ElectronCollisionHandler>
    electron_collision_handler = std::dynamic_pointer_cast<MonteCarlo::ElectronCollisionHandler>( collision_handler );
  
  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 1, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( !collision_handler->isCellVoid( 1, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 1 )->getId(),
                       1 );
  TEST_EQUALITY_CONST( electron_collision_handler->getMaterial( 1 )->getId(),
                       1 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 3, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( !collision_handler->isCellVoid( 3, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 3 )->getId(),
                       2 );
  TEST_EQUALITY_CONST( electron_collision_handler->getMaterial( 3 )->getId(),
                       2 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 5, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( !collision_handler->isCellVoid( 5, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 5 )->getId(),
                       3 );
  TEST_EQUALITY_CONST( electron_collision_handler->getMaterial( 5 )->getId(),
                       3 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 7, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( !collision_handler->isCellVoid( 7, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 7 )->getId(),
                       2 );
  TEST_EQUALITY_CONST( electron_collision_handler->getMaterial( 7 )->getId(),
                       2 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 9, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( !collision_handler->isCellVoid( 9, MonteCarlo::ELECTRON ) );
  TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 9 )->getId(),
                       4 );
  TEST_EQUALITY_CONST( electron_collision_handler->getMaterial( 9 )->getId(),
                       4 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::PHOTON ) );
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::ELECTRON ) );

  // Verify that capture is implicit
  MonteCarlo::PhotonState photon( 0ull );
  photon.setCell( 1 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  photon.setEnergy( 1.0 );
  photon.setWeight( 1.0 );

  MonteCarlo::ElectronState electron( 1ull );
  electron.setCell( 1 );
  electron.setDirection( 0.0, 0.0, 1.0 );
  electron.setEnergy( 1.0 );
  electron.setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  collision_handler->collideWithCellMaterial( photon, bank );

  TEST_ASSERT( photon.getWeight() < 1.0 );

  collision_handler->collideWithCellMaterial( electron, bank );

  TEST_EQUALITY_CONST( electron.getWeight(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the collision handler can be initialize with DagMC
TEUCHOS_UNIT_TEST( CollisionHandlerFactoryDagMC,
                   createHandler_neutron_photon_electron_mode_analogue )
{
  MonteCarlo::SimulationProperties properties;
  
  // Set the particle mode to NEUTRON_PHOTON_ELECTRON_MODE
  properties.setParticleMode( MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE );

  // Set the collision type to analogue
  properties.setAnalogueCaptureModeOn();

  std::shared_ptr<MonteCarlo::CollisionHandler> collision_handler;

  // Note: The photon production cross sections for H-1 have multiple
  // interpolation regions, which cannot currently be parsed
  TEST_THROW( collision_handler = MonteCarlo::getCollisionHandlerFactoryInstance<Geometry::DagMC>( &out )->createHandler(
                                           forward_material_reps,
					   cross_section_table_info,
                                           properties,
					   test_cross_sections_xml_directory ),
              std::runtime_error );

  // std::shared_ptr<MonteCarlo::NeutronCollisionHandler>
  //   neutron_collision_handler = std::dynamic_pointer_cast<MonteCarlo::NeutronCollisionHandler>( collision_handler );

  // std::shared_ptr<MonteCarlo::PhotonCollisionHandler>
  //   photon_collision_handler = std::dynamic_pointer_cast<MonteCarlo::PhotonCollisionHandler>( collision_handler );

  // std::shared_ptr<MonteCarlo::ElectronCollisionHandler>
  //   electron_collision_handler = std::dynamic_pointer_cast<MonteCarlo::ElectronCollisionHandler>( collision_handler );
  
  // TEST_ASSERT( !collision_handler->isCellVoid( 1, MonteCarlo::NEUTRON ) );
  // TEST_ASSERT( !collision_handler->isCellVoid( 1, MonteCarlo::PHOTON ) );
  // TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::ADJOINT_PHOTON ));
  // TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::ELECTRON ) );
  // TEST_EQUALITY_CONST( neutron_collision_handler->getMaterial( 1 )->getId(),
  //                      1 );
  // TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 1 )->getId(),
  //                      1 );
  // TEST_EQUALITY_CONST( electron_collision_handler->getMaterial( 1 )->getId(),
  //                      1 );
  
  // TEST_ASSERT( !collision_handler->isCellVoid( 3, MonteCarlo::NEUTRON ) );
  // TEST_ASSERT( !collision_handler->isCellVoid( 3, MonteCarlo::PHOTON ) );
  // TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::ADJOINT_PHOTON ));
  // TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::ELECTRON ) );
  // TEST_EQUALITY_CONST( neutron_collision_handler->getMaterial( 3 )->getId(),
  //                      2 );
  // TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 3 )->getId(),
  //                      2 );
  // TEST_EQUALITY_CONST( electron_collision_handler->getMaterial( 3 )->getId(),
  //                      2 );
  
  // TEST_ASSERT( !collision_handler->isCellVoid( 5, MonteCarlo::NEUTRON ) );
  // TEST_ASSERT( !collision_handler->isCellVoid( 5, MonteCarlo::PHOTON ) );
  // TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::ADJOINT_PHOTON ));
  // TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::ELECTRON ) );
  // TEST_EQUALITY_CONST( neutron_collision_handler->getMaterial( 5 )->getId(),
  //                      3 );
  // TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 5 )->getId(),
  //                      3 );
  // TEST_EQUALITY_CONST( electron_collision_handler->getMaterial( 5 )->getId(),
  //                      3 );
  
  // TEST_ASSERT( !collision_handler->isCellVoid( 7, MonteCarlo::NEUTRON ) );
  // TEST_ASSERT( !collision_handler->isCellVoid( 7, MonteCarlo::PHOTON ) );
  // TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::ADJOINT_PHOTON ));
  // TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::ELECTRON ) );
  // TEST_EQUALITY_CONST( neutron_collision_handler->getMaterial( 7 )->getId(),
  //                      2 );
  // TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 7 )->getId(),
  //                      2 );
  // TEST_EQUALITY_CONST( electron_collision_handler->getMaterial( 7 )->getId(),
  //                      2 );
  
  // TEST_ASSERT( !collision_handler->isCellVoid( 9, MonteCarlo::NEUTRON ) );
  // TEST_ASSERT( !collision_handler->isCellVoid( 9, MonteCarlo::PHOTON ) );
  // TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::ADJOINT_PHOTON ));
  // TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::ELECTRON ) );
  // TEST_EQUALITY_CONST( neutron_collision_handler->getMaterial( 9 )->getId(),
  //                      4 );
  // TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 9 )->getId(),
  //                      4 );
  // TEST_EQUALITY_CONST( electron_collision_handler->getMaterial( 9 )->getId(),
  //                      4 );
  
  // TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::NEUTRON ) );
  // TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::PHOTON ) );
  // TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::ADJOINT_PHOTON ));
  // TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::ELECTRON ) );

  // // Verify that collisions are analogue
  // MonteCarlo::NeutronState neutron( 0ull );
  // neutron.setCell( 1 );
  // neutron.setDirection( 0.0, 0.0, 1.0 );
  // neutron.setEnergy( 1.0 );
  // neutron.setWeight( 1.0 );

  // MonteCarlo::PhotonState photon( 1ull );
  // photon.setCell( 1 );
  // photon.setDirection( 0.0, 0.0, 1.0 );
  // photon.setEnergy( 1.0 );
  // photon.setWeight( 1.0 );

  // MonteCarlo::ElectronState electron( 2ull );
  // electron.setCell( 1 );
  // electron.setDirection( 0.0, 0.0, 1.0 );
  // electron.setEnergy( 1.0 );
  // electron.setWeight( 1.0 );

  // MonteCarlo::ParticleBank bank;

  // collision_handler->collideWithCellMaterial( neutron, bank );

  // TEST_EQUALITY_CONST( neutron.getWeight(), 1.0 );

  // collision_handler->collideWithCellMaterial( photon, bank );

  // TEST_EQUALITY_CONST( photon.getWeight(), 1.0 );

  // collision_handler->collideWithCellMaterial( electron, bank );

  // TEST_EQUALITY_CONST( electron.getWeight(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the collision handler can be initialize with DagMC
TEUCHOS_UNIT_TEST( CollisionHandlerFactoryDagMC,
                   createHandler_neutron_photon_electron_mode_implicit_capture )
{
  MonteCarlo::SimulationProperties properties;
  
  // Set the particle mode to NEUTRON_PHOTON_ELECTRON_MODE
  properties.setParticleMode( MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE );

  // Set the collision type to analogue
  properties.setImplicitCaptureModeOn();

  std::shared_ptr<MonteCarlo::CollisionHandler> collision_handler;

  // Note: The photon production cross sections for H-1 have multiple
  // interpolation regions, which cannot currently be parsed
  TEST_THROW( collision_handler = MonteCarlo::getCollisionHandlerFactoryInstance<Geometry::DagMC>( &out )->createHandler(
                                           forward_material_reps,
					   cross_section_table_info,
                                           properties,
					   test_cross_sections_xml_directory ),
              std::runtime_error );

  // std::shared_ptr<MonteCarlo::NeutronCollisionHandler>
  //   neutron_collision_handler = std::dynamic_pointer_cast<MonteCarlo::NeutronCollisionHandler>( collision_handler );

  // std::shared_ptr<MonteCarlo::PhotonCollisionHandler>
  //   photon_collision_handler = std::dynamic_pointer_cast<MonteCarlo::PhotonCollisionHandler>( collision_handler );

  // std::shared_ptr<MonteCarlo::ElectronCollisionHandler>
  //   electron_collision_handler = std::dynamic_pointer_cast<MonteCarlo::ElectronCollisionHandler>( collision_handler );
  
  // TEST_ASSERT( !collision_handler->isCellVoid( 1, MonteCarlo::NEUTRON ) );
  // TEST_ASSERT( !collision_handler->isCellVoid( 1, MonteCarlo::PHOTON ) );
  // TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::ADJOINT_PHOTON ));
  // TEST_ASSERT( collision_handler->isCellVoid( 1, MonteCarlo::ELECTRON ) );
  // TEST_EQUALITY_CONST( neutron_collision_handler->getMaterial( 1 )->getId(),
  //                      1 );
  // TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 1 )->getId(),
  //                      1 );
  // TEST_EQUALITY_CONST( electron_collision_handler->getMaterial( 1 )->getId(),
  //                      1 );
  
  // TEST_ASSERT( !collision_handler->isCellVoid( 3, MonteCarlo::NEUTRON ) );
  // TEST_ASSERT( !collision_handler->isCellVoid( 3, MonteCarlo::PHOTON ) );
  // TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::ADJOINT_PHOTON ));
  // TEST_ASSERT( collision_handler->isCellVoid( 3, MonteCarlo::ELECTRON ) );
  // TEST_EQUALITY_CONST( neutron_collision_handler->getMaterial( 3 )->getId(),
  //                      2 );
  // TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 3 )->getId(),
  //                      2 );
  // TEST_EQUALITY_CONST( electron_collision_handler->getMaterial( 3 )->getId(),
  //                      2 );
  
  // TEST_ASSERT( !collision_handler->isCellVoid( 5, MonteCarlo::NEUTRON ) );
  // TEST_ASSERT( !collision_handler->isCellVoid( 5, MonteCarlo::PHOTON ) );
  // TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::ADJOINT_PHOTON ));
  // TEST_ASSERT( collision_handler->isCellVoid( 5, MonteCarlo::ELECTRON ) );
  // TEST_EQUALITY_CONST( neutron_collision_handler->getMaterial( 5 )->getId(),
  //                      3 );
  // TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 5 )->getId(),
  //                      3 );
  // TEST_EQUALITY_CONST( electron_collision_handler->getMaterial( 5 )->getId(),
  //                      3 );
  
  // TEST_ASSERT( !collision_handler->isCellVoid( 7, MonteCarlo::NEUTRON ) );
  // TEST_ASSERT( !collision_handler->isCellVoid( 7, MonteCarlo::PHOTON ) );
  // TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::ADJOINT_PHOTON ));
  // TEST_ASSERT( collision_handler->isCellVoid( 7, MonteCarlo::ELECTRON ) );
  // TEST_EQUALITY_CONST( neutron_collision_handler->getMaterial( 7 )->getId(),
  //                      2 );
  // TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 7 )->getId(),
  //                      2 );
  // TEST_EQUALITY_CONST( electron_collision_handler->getMaterial( 7 )->getId(),
  //                      2 );
  
  // TEST_ASSERT( !collision_handler->isCellVoid( 9, MonteCarlo::NEUTRON ) );
  // TEST_ASSERT( !collision_handler->isCellVoid( 9, MonteCarlo::PHOTON ) );
  // TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::ADJOINT_PHOTON ));
  // TEST_ASSERT( collision_handler->isCellVoid( 9, MonteCarlo::ELECTRON ) );
  // TEST_EQUALITY_CONST( neutron_collision_handler->getMaterial( 9 )->getId(),
  //                      4 );
  // TEST_EQUALITY_CONST( photon_collision_handler->getMaterial( 9 )->getId(),
  //                      4 );
  // TEST_EQUALITY_CONST( electron_collision_handler->getMaterial( 9 )->getId(),
  //                      4 );
  
  // TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::NEUTRON ) );
  // TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::PHOTON ) );
  // TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::ADJOINT_PHOTON ));
  // TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::ELECTRON ) );

  // // Verify that collisions are analogue
  // MonteCarlo::NeutronState neutron( 0ull );
  // neutron.setCell( 1 );
  // neutron.setDirection( 0.0, 0.0, 1.0 );
  // neutron.setEnergy( 1.0 );
  // neutron.setWeight( 1.0 );

  // MonteCarlo::PhotonState photon( 1ull );
  // photon.setCell( 1 );
  // photon.setDirection( 0.0, 0.0, 1.0 );
  // photon.setEnergy( 1.0 );
  // photon.setWeight( 1.0 );

  // MonteCarlo::ElectronState electron( 2ull );
  // electron.setCell( 1 );
  // electron.setDirection( 0.0, 0.0, 1.0 );
  // electron.setEnergy( 1.0 );
  // electron.setWeight( 1.0 );

  // MonteCarlo::ParticleBank bank;

  // collision_handler->collideWithCellMaterial( neutron, bank );

  // TEST_EQUALITY_CONST( neutron.getWeight(), 1.0 );

  // collision_handler->collideWithCellMaterial( photon, bank );

  // TEST_EQUALITY_CONST( photon.getWeight(), 1.0 );

  // collision_handler->collideWithCellMaterial( electron, bank );

  // TEST_EQUALITY_CONST( electron.getWeight(), 1.0 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_forward_material_xml_file_name;
std::string test_adjoint_material_xml_file_name;
std::string test_geom_xml_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_cross_sections_xml_directory",
                   &test_cross_sections_xml_directory,
                   "Test cross_sections.xml file directory name" );

  clp().setOption( "test_forward_mat_xml_file",
                   &test_forward_material_xml_file_name,
                   "Test xml material file name for forward particles" );

  clp().setOption( "test_adjoint_mat_xml_file",
                   &test_adjoint_material_xml_file_name,
                   "Test xml material file name for adjoint particles" );

  clp().setOption( "test_geom_xml_file",
                   &test_geom_xml_file_name,
                   "Test xml geometry file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Assign the name of the cross_sections.xml file with path
  std::string cross_section_xml_file = test_cross_sections_xml_directory;
  cross_section_xml_file += "/cross_sections.xml";

  // Read in the xml file storing the cross section table information
  Teuchos::updateParametersFromXmlFile(
			         cross_section_xml_file,
			         Teuchos::inoutArg(cross_section_table_info) );

  // Read in the xml file storing the material specifications
  Teuchos::updateParametersFromXmlFile( test_forward_material_xml_file_name,
					Teuchos::inoutArg(forward_material_reps) );

  Teuchos::updateParametersFromXmlFile( test_adjoint_material_xml_file_name,
                                        Teuchos::inoutArg(adjoint_material_reps) );

  // Initialize DagMC
  Teuchos::RCP<Teuchos::ParameterList> geom_rep =
    Teuchos::getParametersFromXmlFile( test_geom_xml_file_name );

  Geometry::DagMCInstanceFactory::initializeDagMC( *geom_rep );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstCollisionHandlerFactory_DagMC.cpp
//---------------------------------------------------------------------------//
