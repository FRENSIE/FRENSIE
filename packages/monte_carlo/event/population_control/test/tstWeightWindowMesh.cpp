//---------------------------------------------------------------------------//
//!
//! \file   tstWeightWindowMesh.cpp
//! \author Philip Britt
//! \brief  WeightWindowMesh test
//!
//---------------------------------------------------------------------------//

// std includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_WeightWindow.hpp"
#include "MonteCarlo_WeightWindowMesh.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "Utility_StructuredHexMesh.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "Utility_RandomNumberGenerator.hpp"

// Weight window mesh pointer
std::shared_ptr<MonteCarlo::WeightWindowMesh> weight_window_mesh;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//

FRENSIE_UNIT_TEST( WeightWindowMesh, getWeightWindow )
{
  MonteCarlo::PhotonState photon(0);

  photon.setEnergy( 1.0 );
  photon.setPosition(0.5, 0.5, 0.5);

  std::shared_ptr<MonteCarlo::WeightWindow> weight_window = weight_window_mesh->getWeightWindow(photon);

  FRENSIE_CHECK_EQUAL(6.0, weight_window->lower_weight);
  FRENSIE_CHECK_EQUAL(7.0, weight_window->upper_weight);
  FRENSIE_CHECK_EQUAL(6.0001, weight_window->survival_weight);
}

FRENSIE_UNIT_TEST( WeightWindowMesh, checkParticleWithPopulationController_split)
{
  // Fake probability stream
  std::vector<double> fake_stream = {0.1, 0.0001};
  Utility::RandomNumberGenerator::setFakeStream(fake_stream);
  {
    MonteCarlo::PhotonState photon(0);

    photon.setEnergy( 1.0);
    photon.setPosition(0.5, 0.5, 0.5);
    photon.setWeight(14.2);

    MonteCarlo::ParticleBank particle_bank;

    weight_window_mesh->checkParticleWithPopulationController(photon, particle_bank);

    FRENSIE_CHECK_EQUAL(particle_bank.size(), 2);
    FRENSIE_CHECK_CLOSE(14.2/3, photon.getWeight(), 1e-14);
    FRENSIE_CHECK_CLOSE(14.2/3, particle_bank.top().getWeight(),1e-14);
  }
  {
    MonteCarlo::PhotonState photon(0);

    photon.setEnergy( 1.0);
    photon.setPosition(0.5, 0.5, 0.5);
    photon.setWeight(14.2);

    MonteCarlo::ParticleBank particle_bank;

    weight_window_mesh->checkParticleWithPopulationController(photon, particle_bank);

    FRENSIE_CHECK_EQUAL(particle_bank.size(), 1);
    FRENSIE_CHECK_CLOSE(14.2/2, photon.getWeight(),1e-14);
    FRENSIE_CHECK_CLOSE(14.2/2, particle_bank.top().getWeight(),1e-14);
  }
  Utility::RandomNumberGenerator::unsetFakeStream();
}

FRENSIE_UNIT_TEST(WeightWindowMesh, checkParticleWithPopulationController_terminate)
{
    // Fake probability stream
  std::vector<double> fake_stream = {0.6, 0.4};
  Utility::RandomNumberGenerator::setFakeStream(fake_stream);
  {
    MonteCarlo::PhotonState photon(0);

    photon.setEnergy( 1.0);
    photon.setPosition(0.5, 0.5, 0.5);
    photon.setWeight(3.0);

    MonteCarlo::ParticleBank particle_bank;

    weight_window_mesh->checkParticleWithPopulationController(photon, particle_bank);

    // Check particle weight against the survival weight. Should still exist.
    FRENSIE_CHECK(!photon.isGone());
    FRENSIE_CHECK_CLOSE(photon.getWeight(), 6.0001, 1e-13);
  }
  {
    MonteCarlo::PhotonState photon(0);

    photon.setEnergy( 1.0);
    photon.setPosition(0.5, 0.5, 0.5);
    photon.setWeight(3.0);

    MonteCarlo::ParticleBank particle_bank;

    weight_window_mesh->checkParticleWithPopulationController(photon, particle_bank);

    // Check particle weight against the survival weight. Should still exist.
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
  weight_window_mesh = std::make_shared<MonteCarlo::WeightWindowMesh>();
  weight_window_mesh->setMesh(mesh);
  
  std::vector<double> energy_bin_boundaries( 3 );
  energy_bin_boundaries[0] = 0.0;
  energy_bin_boundaries[1] = 1e-1;
  energy_bin_boundaries[2] = 20.0;

  weight_window_mesh->setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>(energy_bin_boundaries);

  std::unordered_map<Utility::Mesh::ElementHandle, std::vector<std::shared_ptr<MonteCarlo::WeightWindow>>> weight_window_mesh_map;

  std::vector<std::shared_ptr<MonteCarlo::WeightWindow>> weight_window_vector_1;

  // Need 4 weight windows in total, 2 in each element
  std::shared_ptr<MonteCarlo::WeightWindow> weight_window_1 = std::make_shared<MonteCarlo::WeightWindow>();
  
  weight_window_1->lower_weight = 0.2;
  weight_window_1->upper_weight = 20.0;
  weight_window_1->survival_weight = 8.0;

  weight_window_vector_1.push_back(weight_window_1);

  std::shared_ptr<MonteCarlo::WeightWindow> weight_window_2 = std::make_shared<MonteCarlo::WeightWindow>();
  
  weight_window_2->lower_weight = 6.0;
  weight_window_2->upper_weight = 7.0;
  weight_window_2->survival_weight = 6.0001;

  weight_window_vector_1.push_back(weight_window_2);

  weight_window_mesh_map.emplace(0, weight_window_vector_1);

  std::vector<std::shared_ptr<MonteCarlo::WeightWindow>> weight_window_vector_2;

  std::shared_ptr<MonteCarlo::WeightWindow> weight_window_3 = std::make_shared<MonteCarlo::WeightWindow>();
  
  weight_window_3->lower_weight = 1e-6;
  weight_window_3->upper_weight = 0.5;
  weight_window_3->survival_weight = 0.49;

  weight_window_vector_2.push_back(weight_window_3);

  std::shared_ptr<MonteCarlo::WeightWindow> weight_window_4 = std::make_shared<MonteCarlo::WeightWindow>();
  
  weight_window_4->lower_weight = 0.5;
  weight_window_4->upper_weight = 0.6;
  weight_window_4->survival_weight = 0.55;

  weight_window_vector_2.push_back(weight_window_4);

  weight_window_mesh_map.emplace(1, weight_window_vector_2);

  weight_window_mesh->setWeightWindowMap(weight_window_mesh_map);

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();

}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstDefaultPopulationController.cpp
//---------------------------------------------------------------------------//
