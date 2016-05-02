//---------------------------------------------------------------------------//
//!
//! \file   tstTetMeshTrackLengthFluxEstimator.cpp
//! \author Philip Britt
//! \brief  TetMeshTrackLengthFluxEstimator class unit tests
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
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_HexMeshTrackLengthFluxEstimator.hpp"
#include "MonteCarlo_EstimatorContributionMultiplierPolicy.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<MonteCarlo::HexMeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier>> hex_estimator;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( HexMeshTrackLengthFluxEstimator, constructor )
{
  // Set up a basic mesh
  Teuchos::Array<double> x_grid_points, y_grid_points, z_grid_points;
  x_grid_points.push_back(0);
  x_grid_points.push_back(1);
  x_grid_points.push_back(2);
  y_grid_points.push_back(0);
  y_grid_points.push_back(1);
  y_grid_points.push_back(2);
  z_grid_points.push_back(0);
  z_grid_points.push_back(1);
  z_grid_points.push_back(2);

  TEST_NOTHROW( hex_estimator.reset( new MonteCarlo::HexMeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier>(0, 2, x_grid_points, y_grid_points, z_grid_points ) ) );

}

TEUCHOS_UNIT_TEST( HexMeshTrackLengthFluxEstimator, isPointInMesh)
{
  double outside_point_1[3] = { 0.5, 0.5, 0.5 };
  double outside_point_2[3] = { 0.5, 0.5, 1.5 };
  double outside_point_3[3] = { 0.5, 0.5, 0.5 };
  double outside_point_4[3] = { 0.5, 1.5, 0.5 };
  double outside_point_5[3] = { 0.5, 0.5, 0.5 };
  double outside_point_6[3] = { 1.5, 0.5, 0.5 };

  TEST_ASSERT( !hex_estimator->isPointInMesh( outside_point_1 ) );
  TEST_ASSERT( !hex_estimator->isPointInMesh( outside_point_2 ) );
  TEST_ASSERT( !hex_estimator->isPointInMesh( outside_point_3 ) );
  TEST_ASSERT( !hex_estimator->isPointInMesh( outside_point_4 ) );
  TEST_ASSERT( !hex_estimator->isPointInMesh( outside_point_5 ) );
  TEST_ASSERT( !hex_estimator->isPointInMesh( outside_point_6 ) );

  double inside_point_1[3] = { 0.5, 0.5, 0.5 };
  double inside_point_2[3] = { 0.0, 0.0, 0.5 };
  double inside_point_3[3] = { 0.0, 0.5, 0.0 };
  double inside_point_4[3] = { 0.5, 0.0, 0.0 };
  double inside_point_5[3] = { 0.0, 0.5, 0.5 };
  double inside_point_6[3] = { 0.5, 0.0, 0.5 };
  double inside_point_7[3] = { 0.5, 0.5, 0.0 };

  TEST_ASSERT( hex_estimator->isPointInMesh( inside_point_1 ) );
  TEST_ASSERT( hex_estimator->isPointInMesh( inside_point_2 ) );
  TEST_ASSERT( hex_estimator->isPointInMesh( inside_point_3 ) );
  TEST_ASSERT( hex_estimator->isPointInMesh( inside_point_4 ) );
  TEST_ASSERT( hex_estimator->isPointInMesh( inside_point_5 ) );
  TEST_ASSERT( hex_estimator->isPointInMesh( inside_point_6 ) );
  TEST_ASSERT( hex_estimator->isPointInMesh( inside_point_7 ) );
}


TEUCHOS_UNIT_TEST( HexMeshTrackLengthFluxEstimator, updateFromGlobalParticleSubtrackEndingEvent)
{
  // Set the particle types
  Teuchos::Array<MonteCarlo::ParticleType> particle_types( 1 );
  particle_types[0] = MonteCarlo::NEUTRON;

  hex_estimator->setParticleTypes( particles_types );

  double start_point_1[3] = { 0.5, 0.5, 0.0 };
  double end_point_1[3] = { 0.5, 0.5, 2.0 };

  double start_point_2[3] = { 0.5, 1.5, 0.0 };
  double end_point_2[3] = { 0.5, 1.5, 2.0 };

  double start_point_3[3] = { 1.5, 0.5, 0.0 };
  double end_point_3[3] = { 1.5, 0.5, 2.0 };

  double start_point_4[3] = { 1.5, 1.5, 0.0 };
  double end_point_4[3] = { 1.5, 1.5, 2.0 };

  MonteCarlo::NeutronState particle( 0ull );
  particle.setWeight( 1.0 );
  particle.setEnergy( 14.0 );
  particle.setDirection( 0, 0, 1 );

  // Make sure the mesh estimator has no contributions yet
  TEST_ASSERT( !hex_estimator->hasUncommittedHistoryContribution() );

  // Update the mesh estimator
  hex_estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1,
                                                              end_point_1 );
  hex_estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2,
                                                              end_point_2 );
  hex_estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3,
                                                              end_point_3 );
  hex_estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4,
                                                              end_point_4 );

  // Commit the contributions to the mesh estimator
  hex_estimator->commitHistoryContributions();

  TEST_ASSERT( !hex_estimator->hasUncommittedHistoryContributions() );

  // Initialize the HDF5 file
  std::shared_ptr<Utility::HDF5FileHandler>
    hdf5_file( new Utility::HDF5FileHandler );
  hdf5_file->openHDF5FileAndOverwrite( "test_hex_mesh_track_length_flux_estimator.h5" );

  hex_estimator->exportData( hdf5_file, true );

  // Create an estimator hdf5 file handler
  MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( hdf5_file );

  // Get the hex entity handles for use in data retrieval
  const moab::Range all_hex_elements = hex_estimator->getAllHexElements();

  // Retrieve the raw bin data for each hex
  moab::Range::const_iterator hex = all_hex_elements.begin();

  Teuchos::Array<Utility::Pair<double,double> >
    raw_bin_data( 1, Utility::Pair<double,double>( 1.0, 1.0 ) );
  raw_bin_data_copy;

  hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
                                                 0u, *hex, raw_bin_data_copy );

  out << *hex;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
                                        raw_bin_data_copy,
                                        1e-12 );

  ++hex;

  hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
                                                 0u, *hex, raw_bin_data_copy );

  out << *hex;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
                                        raw_bin_data_copy,
                                        1e-12 );

  ++hex;

  hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
                                                 0u, *hex, raw_bin_data_copy );

  out << *hex;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
                                        raw_bin_data_copy,
                                        1e-12 );

  ++hex;

  hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
                                                 0u, *hex, raw_bin_data_copy );

  out << *hex;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
                                        raw_bin_data_copy,
                                        1e-12 );

  ++hex;

  hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
                                                 0u, *hex, raw_bin_data_copy );

  out << *hex;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
                                        raw_bin_data_copy,
                                        1e-12 );

  ++hex;

  hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
                                                 0u, *hex, raw_bin_data_copy );

  out << *hex;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
                                        raw_bin_data_copy,
                                        1e-12 );

  ++hex;

  hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
                                                 0u, *hex, raw_bin_data_copy );

  out << *hex;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
                                        raw_bin_data_copy,
                                        1e-12 );

  ++hex;

  hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
                                                 0u, *hex, raw_bin_data_copy );

  out << *hex;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
                                        raw_bin_data_copy,
                                        1e-12 );

  ++hex;
}

//---------------------------------------------------------------------------//
// Custom Main
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();
    Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

    /*clp.setOption( "test_input_mesh_file_name",
		 &test_input_mesh_file_name,
		 "Test input mesh file name" );*/

  
  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  
  const bool success = Teuchos::UnitTestRepository::runUnitTests(*out);

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

