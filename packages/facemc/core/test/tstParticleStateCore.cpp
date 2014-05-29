//---------------------------------------------------------------------------//
//!
//! \file   tstParticleStateCore.cpp
//! \author Alex Robinson
//! \brief  Particle state core unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Facemc_ParticleStateCore.hpp"
#include "Utility_HDF5FileHandler.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an array of cores can be written to an HDF5 file
TEUCHOS_UNIT_TEST( ParticleStateCore, writeArrayToDataSet)
{
  Teuchos::Array<Facemc::ParticleStateCore> particle_state_cores( 1 );

  particle_state_cores[0].history_number = 0ull;
  particle_state_cores[0].particle_type = Facemc::NEUTRON;
  particle_state_cores[0].x_position = 1.0;
  particle_state_cores[0].y_position = 1.0;
  particle_state_cores[0].z_position = 1.0;
  particle_state_cores[0].x_direction = 0.0;
  particle_state_cores[0].y_direction = 0.0;
  particle_state_cores[0].z_direction = 1.0;
  particle_state_cores[0].energy = 1.0;
  particle_state_cores[0].time = 0.5;
  particle_state_cores[0].collision_number = 1u;
  particle_state_cores[0].generation_number = 1u;
  particle_state_cores[0].weight = 0.5;

  Utility::HDF5FileHandler hdf5_file_handler;
  
  hdf5_file_handler.openHDF5FileAndOverwrite( "hdf5_particle_cores.h5" );

  hdf5_file_handler.writeArrayToDataSet( particle_state_cores, "/cores" );
  
  Teuchos::Array<Facemc::ParticleStateCore> ref_particle_state_cores;
  
  hdf5_file_handler.readArrayFromDataSet( ref_particle_state_cores, "/cores" );

  TEST_EQUALITY(particle_state_cores.size(), ref_particle_state_cores.size());
  TEST_EQUALITY(particle_state_cores[0].history_number,
		ref_particle_state_cores[0].history_number);
  TEST_EQUALITY(particle_state_cores[0].particle_type,
		ref_particle_state_cores[0].particle_type);
  TEST_EQUALITY(particle_state_cores[0].x_position,
		ref_particle_state_cores[0].x_position);
  TEST_EQUALITY(particle_state_cores[0].y_position,
		ref_particle_state_cores[0].y_position);
  TEST_EQUALITY(particle_state_cores[0].z_position,
		ref_particle_state_cores[0].z_position);
  TEST_EQUALITY(particle_state_cores[0].x_direction,
		ref_particle_state_cores[0].x_direction);
  TEST_EQUALITY(particle_state_cores[0].y_direction,
		ref_particle_state_cores[0].y_direction);
  TEST_EQUALITY(particle_state_cores[0].z_direction,
		ref_particle_state_cores[0].z_direction);
  TEST_EQUALITY(particle_state_cores[0].energy,
		ref_particle_state_cores[0].energy);
  TEST_EQUALITY(particle_state_cores[0].time,
		ref_particle_state_cores[0].time);
  TEST_EQUALITY(particle_state_cores[0].collision_number,
		ref_particle_state_cores[0].collision_number);
  TEST_EQUALITY(particle_state_cores[0].generation_number,
		ref_particle_state_cores[0].generation_number);
  TEST_EQUALITY(particle_state_cores[0].weight,
		ref_particle_state_cores[0].weight);
}

//---------------------------------------------------------------------------//
// end tstParticleStateCore.cpp
//---------------------------------------------------------------------------//
