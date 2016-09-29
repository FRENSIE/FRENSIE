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
#include <vector>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_DefaultComm.hpp>

// FRENSIE Includes
#include "MonteCarlo_HexMeshTrackLengthFluxEstimator.hpp"
#include "MonteCarlo_EstimatorContributionMultiplierPolicy.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"
#include "Utility_StructuredHexMesh.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<MonteCarlo::HexMeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier>> hex_estimator;
int threads = 1;
//---------------------------------------------------------------------------//
// Test formation of constructor
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( HexMeshTrackLengthFluxEstimator, constructor )
{
  // Set up a basic mesh
  Teuchos::Array<double> x_planes, y_planes, z_planes;
  x_planes.push_back(0);
  x_planes.push_back(1);
  x_planes.push_back(2);
  y_planes.push_back(0);
  y_planes.push_back(1);
  y_planes.push_back(2);
  z_planes.push_back(0);
  z_planes.push_back(1);
  z_planes.push_back(2);

  TEST_NOTHROW( hex_estimator.reset( new MonteCarlo::HexMeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier>(0, 2, x_planes, y_planes, z_planes, "test.vtk" ) ) );
}

//---------------------------------------------------------------------------//
// Test data being formed in estimator
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( HexMeshTrackLengthFluxEstimator, updateFromGlobalParticleSubtrackEndingEvent)
{
  std::shared_ptr<MonteCarlo::Estimator> estimator_base;
  //set planes and multiplier for mesh
  double multiplier = 2;
  std::vector<double> x_planes, y_planes, z_planes;
  x_planes.push_back(-0.5);
  x_planes.push_back(0);
  x_planes.push_back(0.5);

  y_planes.push_back(-0.5);
  y_planes.push_back(0);
  y_planes.push_back(0.5);

  z_planes.push_back(-0.5);
  z_planes.push_back(0);
  z_planes.push_back(0.5);
  
  {
    hex_estimator.reset(
      new MonteCarlo::HexMeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier>(
                                            0, 
                                            multiplier, 
                                            x_planes, 
                                            y_planes, 
                                            z_planes, 
                                            "test.vtk" ) );

    // Assign energy bins
    Teuchos::Array<double> energy_bin_boundaries( 3 );
    energy_bin_boundaries[0] = 0.0;
    energy_bin_boundaries[1] = 5;
    energy_bin_boundaries[2] = 10;
    hex_estimator->setBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(
                             energy_bin_boundaries ); 
    // Set the particle types
    Teuchos::Array<MonteCarlo::ParticleType> particle_types( 1 );
    particle_types[0] = MonteCarlo::NEUTRON;
    hex_estimator->setParticleTypes( particle_types );
     
    estimator_base = hex_estimator;
  }

  hex_estimator->enableThreadSupport( threads );

    // Known contributions and values
    double track_length = 0.25;
    double volume = 0.125;
    double num_hexes = 8.0;
  
    double start_point_1[3] = {-0.5, -0.125, -0.125};
    double end_point_1[3] = {-0.25, -0.125, -0.125};
    double direction_1[3] = {1, 0, 0};
  
    double start_point_2[3] = {0.5, -0.125, -0.125};
    double end_point_2[3] = {0.25, -0.125, -0.125};
    double direction_2[3] = {-1, 0, 0};
  
    double start_point_3[3] = {-0.25, 0.125, -0.25};
    double end_point_3[3] = {-0.25, 0.125, 0.25};
    double direction_3[3] = {0, 0, 1};
  
    double start_point_4[3] = {0.25, 0.125, 0.25};
    double end_point_4[3] = {0.25, 0.125, -0.25};
    double direction_4[3] = {0, 0, -1};
  
    double start_point_5[3] = {-0.25, -0.1, 0.25};
    double end_point_5[3] = {-0.25, -0.35, 0.25};
    double direction_5[3] = {0, -1, 0};
  
    double start_point_6[3] = {0.25, -0.35, 0.25};
    double end_point_6[3] = {0.25, -0.1, 0.25};
    double direction_6[3] = {0, 1, 0};
  

    MonteCarlo::NeutronState particle( 0ull);
    double weight = 0.5;
    particle.setWeight(weight);
  
    // bin 0
    particle.setEnergy( 3.0 );

    TEST_ASSERT( !hex_estimator->hasUncommittedHistoryContribution() );
    #pragma omp parallel num_threads( threads )
    {
      particle.setDirection( direction_1 );  
      hex_estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                                  start_point_1,
                                                                  end_point_1 );

      particle.setDirection( direction_2 );  
      hex_estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                                  start_point_2,
                                                                  end_point_2 );

      particle.setDirection( direction_3 );  
      hex_estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                                  start_point_3,
                                                                  end_point_3 );

      particle.setDirection( direction_4 );  
      hex_estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                                  start_point_4,
                                                                  end_point_4 );

      particle.setDirection( direction_5 );  
      hex_estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                                  start_point_5,
                                                                  end_point_5 );

      particle.setDirection( direction_6 );  
      hex_estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                                  start_point_6,
                                                                  end_point_6 );
    }
    // bin 1
    particle.setEnergy( 7.0 );

    TEST_ASSERT( hex_estimator->hasUncommittedHistoryContribution() );
    #pragma omp parallel num_threads( threads )
    {
      particle.setDirection( direction_1 );  
      hex_estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                                  start_point_1,
                                                                  end_point_1 );

      particle.setDirection( direction_2 );  
      hex_estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                                  start_point_2,
                                                                  end_point_2 );

      particle.setDirection( direction_3 );  
      hex_estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                                  start_point_3,
                                                                  end_point_3 );

      particle.setDirection( direction_4 );  
      hex_estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                                  start_point_4,
                                                                  end_point_4 );

      particle.setDirection( direction_5 );  
      hex_estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                                  start_point_5,
                                                                  end_point_5 );

      particle.setDirection( direction_6 );  
      hex_estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                                  start_point_6,
                                                                  end_point_6 );
    }
    // Commit history contributions
    estimator_base->commitHistoryContribution();

    TEST_ASSERT( !hex_estimator->hasUncommittedHistoryContribution() );

    MonteCarlo::Estimator::setNumberOfHistories( 1.0 );
    MonteCarlo::Estimator::setEndTime( 1.0 );
  
    // Initialize the HDF5 file
    std::shared_ptr<Utility::HDF5FileHandler> 
      hdf5_file( new Utility::HDF5FileHandler );
    hdf5_file->openHDF5FileAndOverwrite( "test_hex_mesh_track_length_flux_estimator.h5" );

    hex_estimator->exportData( hdf5_file, true);
  
    //create an estimator HDF5 file handler
    MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( hdf5_file );
  
    //get start and end iterators for hex elements
    Utility::StructuredHexMesh::HexIDIterator start_hex = hex_estimator->getStartHex();
    Utility::StructuredHexMesh::HexIDIterator end_hex = hex_estimator->getEndHex();
    Utility::StructuredHexMesh::HexIDIterator hex;

    // Retrieve the raw bin data for each hex  
    Teuchos::Array<Utility::Pair<double,double> >
        raw_bin_data( 2, Utility::Pair<double,double>( 
                                   track_length*weight, 
                                   track_length*track_length*weight*weight ) ),
        raw_bin_data_copy;
  
    for(hex = start_hex; hex != end_hex; ++hex)
    {
      hdf5_file_handler.getRawEstimatorEntityBinData<Utility::StructuredHexMesh::HexIndex>(
                             0u, *hex, raw_bin_data_copy );
  
      UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data, 
                                          raw_bin_data_copy,
                                          1e-12 );
    }

    // Retrieve the processed bin data for each hex  
    Teuchos::Array<Utility::Pair<double,double> >
      processed_bin_data( 2, Utility::Pair<double,double>(
                                multiplier*track_length*weight/volume, 0.0 ) ),
      processed_bin_data_copy;
    
    for(hex = start_hex; hex != end_hex; ++hex)
    {
      hdf5_file_handler.getProcessedEstimatorEntityBinData<Utility::StructuredHexMesh::HexIndex>(
                                0u, *hex, processed_bin_data_copy );
  
      UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data, 
                                            processed_bin_data_copy,
                                            1e-12 );
    }

    // Retrieve the raw total bin data
    Teuchos::Array<Utility::Pair<double,double> >
      raw_total_bin_data( 2, Utility::Pair<double,double>(
                          num_hexes*track_length*weight,
                          num_hexes*num_hexes*track_length*track_length*weight*weight ) ),
      raw_total_bin_data_copy;

      hdf5_file_handler.getRawEstimatorTotalBinData(
                              0u, raw_total_bin_data_copy );
  
      UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_bin_data, 
                                            raw_total_bin_data_copy,
                                            1e-12 );

    // Retrieve the processed total bin data
    Teuchos::Array<Utility::Pair<double,double> >
      processed_total_bin_data( 2, Utility::Pair<double,double>(
                          multiplier*num_hexes*track_length*weight,
                          0.0 ) ),
      processed_total_bin_data_copy;

    hdf5_file_handler.getProcessedEstimatorTotalBinData(
                              0u, processed_total_bin_data_copy );
  
    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_bin_data, 
                                          processed_total_bin_data_copy,
                                          1e-12 );

    // Retrieve the raw estimator total data for each entity
    Utility::Quad<double,double,double,double>
      raw_moments( track_length*weight*2.0,
                  track_length*track_length*weight*weight*4.0,
                  track_length*track_length*track_length*weight*weight*weight*8.0,
                  track_length*track_length*track_length*track_length*weight*weight*weight*weight*16.0 );

    Teuchos::Array<Utility::Quad<double,double,double,double> >
      raw_total_data( 1, raw_moments ),
      raw_total_data_copy;

    for(hex = start_hex; hex != end_hex; ++hex)
    {
      hdf5_file_handler.getRawEstimatorEntityTotalData<Utility::StructuredHexMesh::HexIndex>(
                                0u, *hex, raw_total_data_copy );
  
      UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data, 
                                            raw_total_data_copy,
                                            1e-12 );
    }

    // Retrieve the processed estimator total data for each entity
    Utility::Quad<double,double,double,double>
      processed_moments( multiplier*track_length*weight*2.0/volume,
                        0.0,
                        0.0,
                        0.0 );
                
    Teuchos::Array<Utility::Quad<double,double,double,double> >
      processed_total_data( 1, processed_moments ),
      processed_total_data_copy;

    for(hex = start_hex; hex != end_hex; ++hex)
    {
      hdf5_file_handler.getProcessedEstimatorEntityTotalData<Utility::StructuredHexMesh::HexIndex>(
                              0u, *hex, processed_total_data_copy );
  
      UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data, 
                                            processed_total_data_copy,
                                            1e-12 );
    }

    // Retrieve the raw estimator total data  
    raw_total_data[0]( num_hexes*track_length*weight*2.0,
                       num_hexes*num_hexes*track_length*track_length*weight*weight*4.0,
                       num_hexes*num_hexes*num_hexes*track_length*track_length*track_length*weight*weight*weight*8.0,
                       num_hexes*num_hexes*num_hexes*num_hexes*track_length*track_length*track_length*track_length*weight*weight*weight*weight*16.0 );
                
    hdf5_file_handler.getRawEstimatorTotalData( 0u, raw_total_data_copy );
  
    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data, 
                                          raw_total_data_copy,
                                          1e-12 );

    // Retrieve the processed estimator total data
    processed_total_data[0]( num_hexes*track_length*weight*multiplier*2.0,
                             0.0,
                             0.0,
                             0.0 );
                           
    hdf5_file_handler.getProcessedEstimatorTotalData( 0u, 
                                                processed_total_data_copy );
  
    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data, 
                                          processed_total_data_copy,
                                          1e-12 );     
}

//---------------------------------------------------------------------------//
// Custom Main
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();
    Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();
    
  clp.setOption( "threads",
		 &threads,
		 "Number of threads to use" );
		 
  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }
  
  // Set up the global OpenMP session
  if( Utility::GlobalOpenMPSession::isOpenMPUsed() )
    Utility::GlobalOpenMPSession::setNumberOfThreads( threads );
    
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  
  const bool success = Teuchos::UnitTestRepository::runUnitTests(*out);

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

