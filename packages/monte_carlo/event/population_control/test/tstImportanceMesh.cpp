//---------------------------------------------------------------------------//
//!
//! \file   tstImportanceMesh.cpp
//! \author Philip Britt
//! \brief  ImportanceMesh test
//!
//---------------------------------------------------------------------------//
#include <iostream>
// std includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_Importance.hpp"
#include "MonteCarlo_ImportanceMesh.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "Utility_StructuredHexMesh.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "Utility_RandomNumberGenerator.hpp"

// Weight window mesh pointer
std::shared_ptr<MonteCarlo::ImportanceMesh> importance_mesh;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//

FRENSIE_UNIT_TEST( ImportanceMesh, getImportance )
{
  MonteCarlo::PhotonState photon(0);

  photon.setEnergy( 1.0 );
  photon.setPosition(0.5, 0.5, 0.5);

  double importance = importance_mesh->getImportance(photon);

  FRENSIE_CHECK_EQUAL(2.0, importance);
}

FRENSIE_UNIT_TEST( ImportanceMesh, checkParticleWithPopulationController_split)
{
  // 25% probability of 1 particle emerging, 75% probability of 2 with threshold at 0.25
  std::vector<double> fake_stream = {0.249, 0.251};
  Utility::RandomNumberGenerator::setFakeStream(fake_stream);
  {
    MonteCarlo::PhotonState photon(0);
    MonteCarlo::ParticleBank particle_bank;
    photon.setEnergy( 1.0);
    photon.setPosition(0.5, 0.5, 0.5);
    photon.setWeight(14.2);

    importance_mesh->checkParticleWithPopulationController(photon, particle_bank);

    FRENSIE_CHECK_EQUAL(photon.getWeight(), 14.2);
    FRENSIE_CHECK_EQUAL(photon.getImportancePair().first, 2.0);
    FRENSIE_CHECK_EQUAL(photon.getCollisionNumber(), 0);

    photon.setEnergy(1e-2);
    photon.setPosition(1.5, 0.5, 0.5);
    photon.incrementCollisionNumber();

    importance_mesh->checkParticleWithPopulationController(photon, particle_bank);

    double updated_weight = 14.2*(2.0/3.5);

    FRENSIE_CHECK_CLOSE(photon.getWeight(), updated_weight, 1e-14);
    FRENSIE_CHECK_EQUAL(photon.getImportancePair().second, 3.5);
    FRENSIE_CHECK(particle_bank.isEmpty());
    FRENSIE_CHECK_EQUAL(photon.getCollisionNumber(), 1);
  }

  {
    MonteCarlo::PhotonState photon(0);
    MonteCarlo::ParticleBank particle_bank;

    photon.setEnergy( 1.0);
    photon.setPosition(0.5, 0.5, 0.5);
    photon.setWeight(14.2);

    importance_mesh->checkParticleWithPopulationController(photon, particle_bank);

    FRENSIE_CHECK_EQUAL(photon.getWeight(), 14.2);
    FRENSIE_CHECK_EQUAL(photon.getImportancePair().first, 2.0);
    FRENSIE_CHECK_EQUAL(photon.getCollisionNumber(), 0);

    photon.setEnergy(1e-2);
    photon.setPosition(1.5, 0.5, 0.5);
    photon.incrementCollisionNumber();

    importance_mesh->checkParticleWithPopulationController(photon, particle_bank);

    double updated_weight = 14.2*(2.0/3.5);

    FRENSIE_CHECK_CLOSE(photon.getWeight(), updated_weight, 1e-14);
    FRENSIE_CHECK_CLOSE(particle_bank.top().getWeight(), updated_weight, 1e-14);
    FRENSIE_CHECK_EQUAL(photon.getImportancePair().second, 3.5);
    FRENSIE_CHECK_EQUAL(particle_bank.size(), 1);
    FRENSIE_CHECK_EQUAL(photon.getCollisionNumber(), 1);
  }
  
  Utility::RandomNumberGenerator::unsetFakeStream(); 
}

FRENSIE_UNIT_TEST(ImportanceMesh, checkParticleWithPopulationController_terminate)
{
  
  // Fake probability stream
  std::vector<double> fake_stream = {0.44, 0.42};
  Utility::RandomNumberGenerator::setFakeStream(fake_stream);
  {
    MonteCarlo::PhotonState photon(0);
    MonteCarlo::ParticleBank particle_bank;
    photon.setEnergy( 1e-2);
    photon.setPosition(1.5, 0.5, 0.5);
    photon.setWeight(3.0);

    importance_mesh->checkParticleWithPopulationController(photon, particle_bank);

    photon.setEnergy( 1.0);
    photon.setPosition(0.5, 0.5, 0.5);
    photon.incrementCollisionNumber();
    FRENSIE_CHECK_EQUAL(photon.getImportancePair().first, 3.5);
 
    importance_mesh->checkParticleWithPopulationController(photon, particle_bank);

    FRENSIE_CHECK(!photon.isGone());
    FRENSIE_CHECK_CLOSE(photon.getWeight(), 3.0*(3.5/2.0), 1e-14);

  }

  {
    MonteCarlo::PhotonState photon(0);
    MonteCarlo::ParticleBank particle_bank;

    photon.setEnergy( 1e-2);
    photon.setPosition(1.5, 0.5, 0.5);
    photon.setWeight(3.0);

    importance_mesh->checkParticleWithPopulationController(photon, particle_bank);

    photon.setEnergy( 1.0);
    photon.setPosition(0.5, 0.5, 0.5);
    photon.incrementCollisionNumber();
 
    importance_mesh->checkParticleWithPopulationController(photon, particle_bank);

    FRENSIE_CHECK(photon.isGone());
  }

  
  Utility::RandomNumberGenerator::unsetFakeStream();
  
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{

  std::vector<double> x_planes = {0, 1, 2};
  std::vector<double> y_planes = {0, 1};
  std::vector<double> z_planes = {0, 1};

  std::shared_ptr<Utility::StructuredHexMesh> mesh = std::make_shared<Utility::StructuredHexMesh>(x_planes, y_planes, z_planes);
  importance_mesh = std::make_shared<MonteCarlo::ImportanceMesh>();
  importance_mesh->setMesh(mesh);
  
  std::vector<double> energy_bin_boundaries( 3 );
  energy_bin_boundaries[0] = 0.0;
  energy_bin_boundaries[1] = 1e-1;
  energy_bin_boundaries[2] = 20.0;

  importance_mesh->setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>(energy_bin_boundaries);

  std::unordered_map<Utility::Mesh::ElementHandle, std::vector<double>> importance_mesh_map;

  std::vector<double> importance_vector_1;

  importance_vector_1.push_back(1.0);
  importance_vector_1.push_back(2.0);

  importance_mesh_map.emplace(0, importance_vector_1);

  std::vector<double> importance_vector_2;

  importance_vector_2.push_back(3.5);
  importance_vector_2.push_back(4.2);

  importance_mesh_map.emplace(1, importance_vector_2);

  importance_mesh->setImportanceMap(importance_mesh_map);

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();

}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstDefaultPopulationController.cpp
//---------------------------------------------------------------------------//
