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
#include "MonteCarlo_WeightWindowMesh.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "Utility_StructuredHexMesh.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ParticleBank.hpp"

// Weight window mesh pointer
std::shared_ptr<MonteCarlo::WeightWindowMesh> weight_window_mesh;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//

FRENSIE_UNIT_TEST( WeightWindowMesh, placeholder )
{

  MonteCarlo::ParticleBank particle_bank;
  MonteCarlo::PhotonState photon(0);

}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{

  std::vector<double> x_planes = {0, 1, 2};
  std::vector<double> y_planes = {0, 1, 2};
  std::vector<double> z_planes = {0, 1, 2};

  std::shared_ptr<Utility::StructuredHexMesh> mesh = std::make_shared<Utility::StructuredHexMesh>(x_planes, y_planes, z_planes);
  weight_window_mesh = std::make_shared<MonteCarlo::WeightWindowMesh>();
  weight_window_mesh->setMesh(mesh);
  
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstDefaultPopulationController.cpp
//---------------------------------------------------------------------------//
