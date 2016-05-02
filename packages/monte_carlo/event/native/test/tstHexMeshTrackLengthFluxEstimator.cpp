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

  TEST_NOTHROW( hex_estimator.reset( new MonteCarlo::HexMeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier>(2, 2, x_grid_points, y_grid_points, z_grid_points ) ) );

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

}

//---------------------------------------------------------------------------//
//output mesh file (HDF5 file former thing)
TEUCHOS_UNIT_TEST( HexMeshTrackLengthFluxEstimator, exportData )
{

        std::shared_ptr<Utility::HDF5FileHandler>
        hdf5_file( new Utility::HDF5FileHandler );
        hdf5_file->openHDF5FileAndOverwrite( "test_hex_mesh_track_length_flux_estimator.h5" ); 
        MonteCarlo::Estimator::setNumberOfHistories( 1.0 );
        MonteCarlo::Estimator::setEndTime( 1.0 );                    
        hex_estimator->exportData( hdf5_file, true );       


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

