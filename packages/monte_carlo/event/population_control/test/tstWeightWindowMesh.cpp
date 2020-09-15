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
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

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

  MonteCarlo::WeightWindow weight_window = weight_window_mesh->getWeightWindow(photon);

  FRENSIE_CHECK_EQUAL(weight_window.lower_weight, 6.0);
  FRENSIE_CHECK_EQUAL(weight_window.upper_weight, 7.0);
  FRENSIE_CHECK_EQUAL(weight_window.survival_weight, 6.0001);
}

FRENSIE_UNIT_TEST( WeightWindowMesh, checkParticleWithPopulationController_split)
{
  MonteCarlo::PhotonState photon(0);

  photon.setEnergy( 1.0);
  photon.setPosition(0.5, 0.5, 0.5);
  photon.setWeight(14.2);

  MonteCarlo::ParticleBank particle_bank;

  weight_window_mesh->checkParticleWithPopulationController(photon, particle_bank);

  double split_weight = 14.2/3;
  FRENSIE_CHECK_EQUAL(particle_bank.size(), 2);
  FRENSIE_CHECK_CLOSE(photon.getWeight(), split_weight,  1e-15);
  FRENSIE_CHECK_CLOSE(particle_bank.top().getWeight(), split_weight, 1e-15);
  particle_bank.pop();
  FRENSIE_CHECK_CLOSE(particle_bank.top().getWeight(), split_weight, 1e-15);  
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
    FRENSIE_CHECK_CLOSE(photon.getWeight(), 6.0001, 1e-15);
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
// Check that an estimator can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( WeightWindowMesh,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_weight_window_mesh" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<MonteCarlo::WeightWindowMesh> mesh_archive_test;
    std::shared_ptr<MonteCarlo::WeightWindowBase> base_archive_test;

    { 
      mesh_archive_test = std::make_shared<MonteCarlo::WeightWindowMesh>();
      base_archive_test = mesh_archive_test;
      // Set up spatial plane vectors
      std::vector<double> x_planes = {0.0, 1.0};
      std::vector<double> y_planes = {0.0, 0.5, 1.0};
      std::vector<double> z_planes = {0.0, 1.0};

      // Set up hex mesh
      std::shared_ptr<Utility::StructuredHexMesh> mesh = std::make_shared<Utility::StructuredHexMesh>(x_planes, y_planes, z_planes);
      mesh_archive_test->setMesh(mesh);

      // Set up discretization
      std::vector<double> energy_bin_boundaries( 3 );
      energy_bin_boundaries[0] = 0.0;
      energy_bin_boundaries[1] = 1.0;
      energy_bin_boundaries[2] = 2.0;

      base_archive_test->setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>(energy_bin_boundaries);

      std::unordered_map<Utility::Mesh::ElementHandle, std::vector<MonteCarlo::WeightWindow>> weight_window_mesh_map;

      for(int spatial_element = 0; spatial_element < 2; ++spatial_element)
      {
        std::vector<MonteCarlo::WeightWindow> weight_window_vector;
        for(int energy_element = 0; energy_element < 2; ++energy_element)
        {
          MonteCarlo::WeightWindow weight_window = MonteCarlo::WeightWindow();
          weight_window.lower_weight = static_cast<double>(2*spatial_element + energy_element) + spatial_element + 1.0;
          weight_window.survival_weight = static_cast<double>(2*spatial_element + energy_element) + spatial_element + 2.0;   
          weight_window.upper_weight = static_cast<double>(2*spatial_element + energy_element) + spatial_element + 3.0;
 

          weight_window_vector.push_back(weight_window);
        }
        weight_window_mesh_map.emplace(spatial_element, weight_window_vector);
      }

      mesh_archive_test->setWeightWindowMap(weight_window_mesh_map);


    }

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( mesh_archive_test ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( base_archive_test ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<MonteCarlo::WeightWindowMesh> mesh_archive_test;
  std::shared_ptr<MonteCarlo::WeightWindowBase> base_archive_test;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( mesh_archive_test ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( base_archive_test ) );

  iarchive.reset();
  {
    FRENSIE_CHECK( mesh_archive_test.get() == base_archive_test.get() );

    std::shared_ptr<const Utility::StructuredHexMesh> underlying_mesh = std::dynamic_pointer_cast<const Utility::StructuredHexMesh>(mesh_archive_test->getMesh());

    FRENSIE_CHECK_EQUAL(underlying_mesh->getNumberOfElements(), 2);

    FRENSIE_CHECK_EQUAL(underlying_mesh->getXPlaneLocation(0), 0.0);
    FRENSIE_CHECK_EQUAL(underlying_mesh->getXPlaneLocation(1), 1.0);

    FRENSIE_CHECK_EQUAL(underlying_mesh->getYPlaneLocation(0), 0.0);
    FRENSIE_CHECK_EQUAL(underlying_mesh->getYPlaneLocation(1), 0.5);
    FRENSIE_CHECK_EQUAL(underlying_mesh->getYPlaneLocation(2), 1.0);

    FRENSIE_CHECK_EQUAL(underlying_mesh->getXPlaneLocation(0), 0.0);
    FRENSIE_CHECK_EQUAL(underlying_mesh->getXPlaneLocation(1), 1.0);

    std::vector<MonteCarlo::ObserverPhaseSpaceDimension> dimensions_discretized;
    base_archive_test->getDiscretizedDimensions(dimensions_discretized);


    FRENSIE_CHECK_EQUAL(dimensions_discretized.size(), 1);
    FRENSIE_CHECK_EQUAL(dimensions_discretized[0], MonteCarlo::ObserverPhaseSpaceDimension::OBSERVER_ENERGY_DIMENSION);

    std::vector<double> energy_discretization_bounds;

    base_archive_test->getDiscretization<MonteCarlo::ObserverPhaseSpaceDimension::OBSERVER_ENERGY_DIMENSION>(energy_discretization_bounds);

    FRENSIE_CHECK_EQUAL(energy_discretization_bounds[0], 0.0);
    FRENSIE_CHECK_EQUAL(energy_discretization_bounds[1], 1.0);
    FRENSIE_CHECK_EQUAL(energy_discretization_bounds[2], 2.0);
    const std::unordered_map<Utility::Mesh::ElementHandle, std::vector<MonteCarlo::WeightWindow>>& weight_window_map = mesh_archive_test->getWeightWindowMap();
    
    for(int spatial_element = 0; spatial_element < 2; ++spatial_element)
    {
      for(int energy_element = 0; energy_element < 2; ++energy_element)
      {
        MonteCarlo::WeightWindow weight_window = weight_window_map.at(spatial_element)[energy_element];
        FRENSIE_CHECK_EQUAL(weight_window.lower_weight , static_cast<double>(2*spatial_element + energy_element) + spatial_element + 1.0);
        FRENSIE_CHECK_EQUAL(weight_window.survival_weight , static_cast<double>(2*spatial_element + energy_element) + spatial_element + 2.0);   
        FRENSIE_CHECK_EQUAL(weight_window.upper_weight , static_cast<double>(2*spatial_element + energy_element) + spatial_element + 3.0);
      }
    }

  }

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

  std::unordered_map<Utility::Mesh::ElementHandle, std::vector<MonteCarlo::WeightWindow>> weight_window_mesh_map;

  std::vector<MonteCarlo::WeightWindow> weight_window_vector_1;

  // Need 4 weight windows in total, 2 in each element
  MonteCarlo::WeightWindow weight_window_1 = MonteCarlo::WeightWindow();
  
  weight_window_1.lower_weight = 0.2;
  weight_window_1.upper_weight = 20.0;
  weight_window_1.survival_weight = 8.0;

  weight_window_vector_1.push_back(weight_window_1);

  MonteCarlo::WeightWindow weight_window_2 = MonteCarlo::WeightWindow();
  
  weight_window_2.lower_weight = 6.0;
  weight_window_2.upper_weight = 7.0;
  weight_window_2.survival_weight = 6.0001;

  weight_window_vector_1.push_back(weight_window_2);

  weight_window_mesh_map.emplace(0, weight_window_vector_1);

  std::vector<MonteCarlo::WeightWindow> weight_window_vector_2;

  MonteCarlo::WeightWindow weight_window_3 = MonteCarlo::WeightWindow();
  
  weight_window_3.lower_weight = 1e-6;
  weight_window_3.upper_weight = 0.5;
  weight_window_3.survival_weight = 0.49;

  weight_window_vector_2.push_back(weight_window_3);

  MonteCarlo::WeightWindow weight_window_4 = MonteCarlo::WeightWindow();
  
  weight_window_4.lower_weight = 0.5;
  weight_window_4.upper_weight = 0.6;
  weight_window_4.survival_weight = 0.55;

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
