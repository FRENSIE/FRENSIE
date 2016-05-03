//---------------------------------------------------------------------------//
//!
//! \file   tstTetMeshTrackLengthFluxEstimator.cpp
//! \author Eli Moll
//! \brief  TetMeshTrackLengthFluxEstimator class unit tests
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
#include "MonteCarlo_TetMeshTrackLengthFluxEstimator.hpp"
#include "MonteCarlo_EstimatorContributionMultiplierPolicy.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::Estimator> mesh_estimator;
std::string test_input_mesh_file_name;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Make sure that the tet mesh object can be constructed
TEUCHOS_UNIT_TEST( TetMeshTrackLengthFluxEstimator, constructor )
{
  // No exceptions should be thrown during construction
  TEST_NOTHROW( mesh_estimator.reset(    
	new MonteCarlo::TetMeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier>( 
					       0,
					       1.0,
					       test_input_mesh_file_name ) ) );
}

//---------------------------------------------------------------------------//
// Make sure that a point can be tested as in the mesh
TEUCHOS_UNIT_TEST( TetMeshTrackLengthFluxEstimator, isPointInMesh )
{
  Teuchos::RCP<MonteCarlo::TetMeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier> > estimator( 
 new MonteCarlo::TetMeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier>(
						     0u,
						     1.0,
						     test_input_mesh_file_name,
						     "unit_cube_output.vtk" ));
  
  double surface_point_1[3] = { 0.25, 0.0, 0.75 };
  double surface_point_2[3] = { 0.0, 0.25, 0.75 };
  double surface_point_3[3] = { 0.75, 0.0, 0.25 };
  double surface_point_4[3] = { 0.0, 0.75, 0.25 };
  double surface_point_5[3] = { 0.75, 0.25, 0.0 };
  double surface_point_6[3] = { 0.25, 0.75, 0.0 };
  double surface_point_7[3] = { 0.75, 0.25, 1.0 };
  double surface_point_8[3] = { 0.25, 0.75, 1.0 };
  double surface_point_9[3] = { 1.0, 0.25, 0.75 };
  double surface_point_10[3] = { 0.25, 1.0, 0.75 };
  double surface_point_11[3] = { 1.0, 0.75, 0.25 };
  double surface_point_12[3] = { 0.75, 1.0, 0.25 };
  double surface_point_13[3] = { 0.0, 0.0, 0.0 };
  double surface_point_14[3] = { 1.0, 0.0, 0.0 };
  double surface_point_15[3] = { 0.0, 1.0, 0.0 };
  double surface_point_16[3] = { 0.0, 0.0, 1.0 };
  double surface_point_17[3] = { 0.0, 1.0, 1.0 };
  double surface_point_18[3] = { 1.0, 0.0, 1.0 };
  double surface_point_19[3] = { 1.0, 1.0, 0.0 };
  double surface_point_20[3] = { 1.0, 1.0, 1.0 };

  TEST_ASSERT( estimator->isPointInMesh( surface_point_1 ) );
  TEST_ASSERT( estimator->isPointInMesh( surface_point_2 ) );
  TEST_ASSERT( estimator->isPointInMesh( surface_point_3 ) );
  TEST_ASSERT( estimator->isPointInMesh( surface_point_4 ) );
  TEST_ASSERT( estimator->isPointInMesh( surface_point_5 ) );
  TEST_ASSERT( estimator->isPointInMesh( surface_point_6 ) );
  TEST_ASSERT( estimator->isPointInMesh( surface_point_7 ) );
  TEST_ASSERT( estimator->isPointInMesh( surface_point_8 ) );
  TEST_ASSERT( estimator->isPointInMesh( surface_point_9 ) );
  TEST_ASSERT( estimator->isPointInMesh( surface_point_10 ) );
  TEST_ASSERT( estimator->isPointInMesh( surface_point_11 ) );
  TEST_ASSERT( estimator->isPointInMesh( surface_point_12 ) );
  TEST_ASSERT( estimator->isPointInMesh( surface_point_13 ) );
  TEST_ASSERT( estimator->isPointInMesh( surface_point_14 ) );
  TEST_ASSERT( estimator->isPointInMesh( surface_point_15 ) );
  TEST_ASSERT( estimator->isPointInMesh( surface_point_16 ) );
  TEST_ASSERT( estimator->isPointInMesh( surface_point_17 ) );
  TEST_ASSERT( estimator->isPointInMesh( surface_point_18 ) );
  TEST_ASSERT( estimator->isPointInMesh( surface_point_19 ) );
  TEST_ASSERT( estimator->isPointInMesh( surface_point_20 ) );

  double outside_point_1[3] = { 0.5, 0.5, -0.5 };
  double outside_point_2[3] = { 0.5, 0.5, 1.5 };
  double outside_point_3[3] = { 0.5, -0.5, 0.5 };
  double outside_point_4[3] = { 0.5, 1.5, 0.5 };
  double outside_point_5[3] = { -0.5, 0.5, 0.5 };
  double outside_point_6[3] = { 1.5, 0.5, 0.5 };

  TEST_ASSERT( !estimator->isPointInMesh( outside_point_1 ) );
  TEST_ASSERT( !estimator->isPointInMesh( outside_point_2 ) );
  TEST_ASSERT( !estimator->isPointInMesh( outside_point_3 ) );
  TEST_ASSERT( !estimator->isPointInMesh( outside_point_4 ) );
  TEST_ASSERT( !estimator->isPointInMesh( outside_point_5 ) );
  TEST_ASSERT( !estimator->isPointInMesh( outside_point_6 ) );

  double inside_point_1[3] = { 0.5, 0.5, 0.5 };
  double inside_point_2[3] = { 0.0, 0.0, 0.5 };
  double inside_point_3[3] = { 0.0, 0.5, 0.0 };
  double inside_point_4[3] = { 0.5, 0.0, 0.0 };
  double inside_point_5[3] = { 0.0, 0.5, 0.5 };
  double inside_point_6[3] = { 0.5, 0.0, 0.5 };
  double inside_point_7[3] = { 0.5, 0.5, 0.0 };

  TEST_ASSERT( estimator->isPointInMesh( surface_point_1 ) );
  TEST_ASSERT( estimator->isPointInMesh( surface_point_2 ) );
  TEST_ASSERT( estimator->isPointInMesh( surface_point_3 ) );
  TEST_ASSERT( estimator->isPointInMesh( surface_point_4 ) );
  TEST_ASSERT( estimator->isPointInMesh( surface_point_5 ) );
  TEST_ASSERT( estimator->isPointInMesh( surface_point_6 ) );
  TEST_ASSERT( estimator->isPointInMesh( surface_point_7 ) );
}

//---------------------------------------------------------------------------//
// Make sure that the data is being calculated correctly
TEUCHOS_UNIT_TEST( TetMeshTrackLengthFluxEstimator, data_analysis )
{
  Teuchos::RCP<MonteCarlo::TetMeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier> > estimator;
  Teuchos::RCP<MonteCarlo::Estimator> estimator_base;
  double multiplier = 2.0;
  
  {
    estimator.reset(
    new MonteCarlo::TetMeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier>(
                         0u,
                         multiplier,
                         test_input_mesh_file_name,
                         "unit_cube_output.vtk" ) );
    
    // Assign energy bins
    Teuchos::Array<double> energy_bin_boundaries( 3 );
    energy_bin_boundaries[0] = 0.0;
    energy_bin_boundaries[1] = 0.1;
    energy_bin_boundaries[2] = 1.0;
    
    estimator->setBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(
                             energy_bin_boundaries );     
                             
    // Set the particle types
    Teuchos::Array<MonteCarlo::ParticleType> particle_types ( 1 );
    particle_types[0] = MonteCarlo::PHOTON;
    
    estimator->setParticleTypes( particle_types );
    
    estimator_base = estimator;
  }
  
  // Known contributions and values
  double track_length = 0.6123724356957940;
  double volume = 1.0/6.0;
  double num_tets = 6.0;
  
  // Start and end point on mesh element surfaces
  double start_point_1[3] = { 0.25, 0.0, 0.75 };
  double end_point_1[3] = { 0.75, 0.25, 1.0 };
  double direction_1[3] = { 0.8164965809277261,
			    0.4082482904638631,
			    0.4082482904638631 };
    
  // Start point outside of mesh, end point on mesh element surface
  // start intersection { 0.0, 0.25, 0.75 };
  double start_point_2[3] = { -0.4082482904638631, 
			      -0.5664965809277261,
                              0.3417517095361369 };
  double end_point_2[3] = { 0.25, 0.75, 1.0 };
  double direction_2[3] = { 0.4082482904638631,
			    0.8164965809277261,
			    0.4082482904638631 };
  
  // Start point on mesh element surface, end point outside of surface
  // end intersection { 1.0, 0.25, 0.75 }
  double start_point_3[3] = { 0.75, 0.0, 0.25 };
  double end_point_3[3] = { 1.4082482904638631,
			    0.6582482904638631,
			    1.5664965809277263 };
  double direction_3[3] = { 0.4082482904638631,
			    0.4082482904638631,
			    0.8164965809277261 };
  
  // Start point and end point outside of surface
  // start intersection { 0.0, 0.75, 0.25 }
  // end intersection { 0.25, 1.0, 0.75 }
  double start_point_4[3] = { -0.4082482904638631,
			      0.3417517095361369,
                              -0.5664965809277261 };
  double end_point_4[3] = { 0.6582482904638631,
			    1.4082482904638631,
			    1.5664965809277263 };
  double direction_4[3] = { 0.4082482904638631,
			    0.4082482904638631,
			    0.8164965809277261 };
  
  // Start point outside of mesh, end point inside of mesh element
  // start intersection { 0.75, 0.25, 0.0 }
  double start_point_5_a[3] = { 0.3417517095361369,
			      -0.5664965809277261,
			      -0.4082482904638631 };
  double end_point_5_a[3] = { 0.875, 0.5, 0.125 };
  double direction_5[3] = { 0.4082482904638631,
			    0.8164965809277261,
			    0.4082482904638631 };

  // Start point inside of mesh, end point outside of mesh
  // end intersection { 1.0, 0.75, 0.25 }
  double start_point_5_b[3] = { 0.875, 0.5, 0.125 };
  double end_point_5_b[3] = { 1.4082482904638631,
			      1.5664965809277263,
			      0.6582482904638631 };
  
  // Start point on mesh element surface, end point in mesh element
  // start intersection { 0.25, 0.75, 0.0 }
  double start_point_6_a[3] = { 0.25, 0.75, 0.0 };
  double end_point_6_a[3] = { 0.41666666666666663,
			      0.8333333333333334,
			      0.08333333333333333 };
  double direction_6[3] = { 0.8164965809277261,
			    0.4082482904638631,
			    0.4082482904638631 };
  
  // Start point in mesh element, end point in mesh element
  double start_point_6_b[3] = { 0.41666666666666663,
				0.8333333333333334,
				0.08333333333333333 };
  double end_point_6_b[3] = { 0.5833333333333333,
			      0.9166666666666666,
			      0.16666666666666666 };
  
  // Start point in mesh element, end point on mesh element surface
  // end intersection { 0.75, 1.0, 0.25 }
  double start_point_6_c[3] = { 0.5833333333333333,
				0.9166666666666666,
				0.16666666666666666 };
  double end_point_6_c[3] = { 0.75, 1.0, 0.25 };

  // bin 0
  MonteCarlo::PhotonState particle( 0ull );
  particle.setWeight( 1.0 );
  particle.setEnergy( 1.0 );
  particle.setDirection( direction_1 );

  TEST_ASSERT( !estimator->hasUncommittedHistoryContribution() );
  
  estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                          start_point_1,
                                                          end_point_1 );
                                                          
  particle.setDirection( direction_2 );
  estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                          start_point_2,
                                                          end_point_2 );
               
  particle.setDirection( direction_3 );
  estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                          start_point_3,
                                                          end_point_3 );

  particle.setDirection( direction_4 );
  estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                          start_point_4,
                                                          end_point_4 );
             
  particle.setDirection( direction_5 );
  estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                          start_point_5_a,
                                                          end_point_5_a );
  estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                          start_point_5_b,
                                                          end_point_5_b );
  
               
  particle.setDirection( direction_6 );
  estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                          start_point_6_a,
                                                          end_point_6_a );
  estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                          start_point_6_b,
                                                          end_point_6_b );
  estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                          start_point_6_c,
                                                          end_point_6_c );

  TEST_ASSERT( estimator->hasUncommittedHistoryContribution() );
                                                          
  // bin 1
  particle.setEnergy( 0.1 );
  
  particle.setDirection( direction_1 );
  estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                          start_point_1,
                                                          end_point_1 );
                                   
  particle.setDirection( direction_2 );
  estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                          start_point_2,
                                                          end_point_2 );
                              
  particle.setDirection( direction_3 );
  estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                          start_point_3,
                                                          end_point_3 );

  particle.setDirection( direction_4 );
  estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                          start_point_4,
                                                          end_point_4 );
                                 
  particle.setDirection( direction_5 );
  estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                          start_point_5_a,
                                                          end_point_5_a );
  estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                          start_point_5_b,
                                                          end_point_5_b );
                                    
  particle.setDirection( direction_6 );
  estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                          start_point_6_a,
                                                          end_point_6_a );
  estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                          start_point_6_b,
                                                          end_point_6_b );
  estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                          start_point_6_c,
                                                          end_point_6_c );
  
  // Commit history contributions
  estimator_base->commitHistoryContribution(); 

  TEST_ASSERT( !estimator->hasUncommittedHistoryContribution() );
  
  MonteCarlo::Estimator::setNumberOfHistories( 1.0 );
  MonteCarlo::Estimator::setEndTime( 1.0 );
  
  // Initialize the HDF5 file
  std::shared_ptr<Utility::HDF5FileHandler>
    hdf5_file( new Utility::HDF5FileHandler );
  hdf5_file->openHDF5FileAndOverwrite( "test_tet_mesh_track_length_flux_estimator.h5" ); 
                            
  estimator->exportData( hdf5_file, true );       

  // Create an estimator hdf5 file handler
  MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( hdf5_file );
  
  // Get the tet EntityHandles for use in data retrieval
  const moab::Range all_tet_elements = estimator->getAllTetElements();
  
  // Retrieve the raw bin data for each tet
  moab::Range::const_iterator tet = all_tet_elements.begin();
  
  Teuchos::Array<Utility::Pair<double,double> >
      raw_bin_data( 2, Utility::Pair<double,double>( 
                                            track_length, 
                                            track_length*track_length) ),
      raw_bin_data_copy;

  hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
                             0u, *tet, raw_bin_data_copy );
  out << *tet;
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data, 
                                        raw_bin_data_copy,
                                        1e-12 );
  
  ++tet;
  out << *tet;
  hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
                             0u, *tet, raw_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data, 
                                        raw_bin_data_copy,
                                        1e-12 );
  
  ++tet;
  out << *tet;
  hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
                             0u, *tet, raw_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data, 
                                        raw_bin_data_copy,
                                        1e-12 );
  
  ++tet;
  out << *tet;
  hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
                             0u, *tet, raw_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data, 
                                        raw_bin_data_copy,
                                        1e-12 );
  
  ++tet;
  out << *tet;
  hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
                             0u, *tet, raw_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data, 
                                        raw_bin_data_copy,
                                        1e-12 );
  
  ++tet;
  out << *tet;
  hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
                             0u, *tet, raw_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data, 
                                        raw_bin_data_copy,
                                        1e-12 );
  
  // Retrieve the processed bin data for each entity
  tet = all_tet_elements.begin();
  
  Teuchos::Array<Utility::Pair<double,double> >
    processed_bin_data( 2, Utility::Pair<double,double>(
                                         multiplier*track_length/volume, 0.0 ) ),
    processed_bin_data_copy;
    
  hdf5_file_handler.getProcessedEstimatorEntityBinData<moab::EntityHandle>(
                             0u, *tet, processed_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data, 
                                        processed_bin_data_copy,
                                        1e-12 );
  
  ++tet;

  hdf5_file_handler.getProcessedEstimatorEntityBinData<moab::EntityHandle>(
                             0u, *tet, processed_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data, 
                                        processed_bin_data_copy,
                                        1e-12 );
  
  ++tet;

  hdf5_file_handler.getProcessedEstimatorEntityBinData<moab::EntityHandle>(
                             0u, *tet, processed_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data, 
                                        processed_bin_data_copy,
                                        1e-12 );
  
  ++tet;

  hdf5_file_handler.getProcessedEstimatorEntityBinData<moab::EntityHandle>(
                             0u, *tet, processed_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data, 
                                        processed_bin_data_copy,
                                        1e-12 );
  
  ++tet;

  hdf5_file_handler.getProcessedEstimatorEntityBinData<moab::EntityHandle>(
                             0u, *tet, processed_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data, 
                                        processed_bin_data_copy,
                                        1e-12 );
  
  ++tet;  
  
  hdf5_file_handler.getProcessedEstimatorEntityBinData<moab::EntityHandle>(
                             0u, *tet, processed_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data, 
                                        processed_bin_data_copy,
                                        1e-12 );
                                          
  // Retrieve the raw total bin data
  tet = all_tet_elements.begin();
  
  Teuchos::Array<Utility::Pair<double,double> >
    raw_total_bin_data( 2, Utility::Pair<double,double>(
                         num_tets*track_length,
                         num_tets*num_tets*track_length*track_length ) ),
    raw_total_bin_data_copy;
  
  hdf5_file_handler.getRawEstimatorTotalBinData(
                             0u, raw_total_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_bin_data,
                                        raw_total_bin_data_copy,
                                        1e-12 );
  
  ++tet;

  hdf5_file_handler.getRawEstimatorTotalBinData(
                             0u, raw_total_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_bin_data,
                                        raw_total_bin_data_copy,
                                        1e-12 );
  
  ++tet;

  hdf5_file_handler.getRawEstimatorTotalBinData(
                             0u, raw_total_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_bin_data,
                                        raw_total_bin_data_copy,
                                        1e-12 );
  
  ++tet;

  hdf5_file_handler.getRawEstimatorTotalBinData(
                             0u, raw_total_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_bin_data,
                                        raw_total_bin_data_copy,
                                        1e-12 );
  
  ++tet;

  hdf5_file_handler.getRawEstimatorTotalBinData(
                             0u, raw_total_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_bin_data,
                                        raw_total_bin_data_copy,
                                        1e-12 );
  
  ++tet;

  hdf5_file_handler.getRawEstimatorTotalBinData(
                             0u, raw_total_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_bin_data,
                                        raw_total_bin_data_copy,
                                        1e-12 );
  
  // Retrieve the processed total bin data
  tet = all_tet_elements.begin();
  
  Teuchos::Array<Utility::Pair<double,double> >
    processed_total_bin_data( 2, Utility::Pair<double,double>(
                         2.0*num_tets*track_length,
                         0.0 ) ),
    processed_total_bin_data_copy; 

  hdf5_file_handler.getProcessedEstimatorTotalBinData(
                             0u, processed_total_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_bin_data,
                                        processed_total_bin_data_copy,
                                        1e-12 );
  
  ++tet;

  hdf5_file_handler.getProcessedEstimatorTotalBinData(
                             0u, processed_total_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_bin_data,
                                        processed_total_bin_data_copy,
                                        1e-12 );
  
  ++tet;
  
  hdf5_file_handler.getProcessedEstimatorTotalBinData(
                             0u, processed_total_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_bin_data,
                                        processed_total_bin_data_copy,
                                        1e-12 );
  
  ++tet;
  
  hdf5_file_handler.getProcessedEstimatorTotalBinData(
                             0u, processed_total_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_bin_data,
                                        processed_total_bin_data_copy,
                                        1e-12 );
  
  ++tet;
  
  hdf5_file_handler.getProcessedEstimatorTotalBinData(
                             0u, processed_total_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_bin_data,
                                        processed_total_bin_data_copy,
                                        1e-12 );
  
  ++tet;

  hdf5_file_handler.getProcessedEstimatorTotalBinData(
                             0u, processed_total_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_bin_data,
                                        processed_total_bin_data_copy,
                                        1e-12 );

  // Retrieve the raw estimator total data for each entity
  tet = all_tet_elements.begin();
  
  Utility::Quad<double,double,double,double>
    raw_moments( 2.0*track_length,
                 4.0*track_length*track_length,
                 8.0*track_length*track_length*track_length,
                 16.0*track_length*track_length*track_length*track_length );
                
  Teuchos::Array<Utility::Quad<double,double,double,double> >
    raw_total_data( 1, raw_moments ),
    raw_total_data_copy;
    
  hdf5_file_handler.getRawEstimatorEntityTotalData<moab::EntityHandle>(
                             0u, *tet, raw_total_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
                                        raw_total_data_copy,
                                        1e-12 );
                                        
  ++tet;  

  hdf5_file_handler.getRawEstimatorEntityTotalData<moab::EntityHandle>(
                             0u, *tet, raw_total_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
                                        raw_total_data_copy,
                                        1e-12 );
                                        
  ++tet;
  
  hdf5_file_handler.getRawEstimatorEntityTotalData<moab::EntityHandle>(
                             0u, *tet, raw_total_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
                                        raw_total_data_copy,
                                        1e-12 );
                                        
  ++tet;  


  hdf5_file_handler.getRawEstimatorEntityTotalData<moab::EntityHandle>(
                             0u, *tet, raw_total_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
                                        raw_total_data_copy,
                                        1e-12 );
                                        
  ++tet;

  hdf5_file_handler.getRawEstimatorEntityTotalData<moab::EntityHandle>(
                             0u, *tet, raw_total_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
                                        raw_total_data_copy,
                                        1e-12 );
                                        
  ++tet;

  hdf5_file_handler.getRawEstimatorEntityTotalData<moab::EntityHandle>(
                             0u, *tet, raw_total_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
                                        raw_total_data_copy,
                                        1e-12 );

  // Retrieve the processed estimator total data for each entity
  tet = all_tet_elements.begin();
  
  Utility::Quad<double,double,double,double>
    processed_moments( 4.0*track_length/volume,
                       0.0,
                       0.0,
                       0.0 );
                
  Teuchos::Array<Utility::Quad<double,double,double,double> >
    processed_total_data( 1, processed_moments ),
    processed_total_data_copy;
    
  hdf5_file_handler.getProcessedEstimatorEntityTotalData<moab::EntityHandle>(
                             0u, *tet, processed_total_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data,
                                        processed_total_data_copy,
                                        1e-12 );
                                        
  ++tet;          

  hdf5_file_handler.getProcessedEstimatorEntityTotalData<moab::EntityHandle>(
                             0u, *tet, processed_total_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data,
                                        processed_total_data_copy,
                                        1e-12 );
                                        
  ++tet; 

  hdf5_file_handler.getProcessedEstimatorEntityTotalData<moab::EntityHandle>(
                             0u, *tet, processed_total_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data,
                                        processed_total_data_copy,
                                        1e-12 );
                                        
  ++tet; 

  hdf5_file_handler.getProcessedEstimatorEntityTotalData<moab::EntityHandle>(
                             0u, *tet, processed_total_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data,
                                        processed_total_data_copy,
                                        1e-12 );
                                        
  ++tet; 

  hdf5_file_handler.getProcessedEstimatorEntityTotalData<moab::EntityHandle>(
                             0u, *tet, processed_total_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data,
                                        processed_total_data_copy,
                                        1e-12 );
                                        
  ++tet; 

  hdf5_file_handler.getProcessedEstimatorEntityTotalData<moab::EntityHandle>(
                             0u, *tet, processed_total_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data,
                                        processed_total_data_copy,
                                        1e-12 );

  // Retrieve the raw estimator total data  
  raw_total_data[0]( num_tets*track_length*2.0,
                     (num_tets*num_tets)*(track_length*track_length)*4.0,
                     (num_tets*num_tets*num_tets)*(track_length*track_length*
                       track_length)*8.0,
                     (num_tets*num_tets*num_tets*num_tets)*(track_length*
                       track_length*track_length*track_length)*16.0 );
                
  hdf5_file_handler.getRawEstimatorTotalData( 0u, raw_total_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data, 
                                        raw_total_data_copy,
                                        1e-12 );

  // Retrieve the processed estimator total data
  processed_total_data[0]( num_tets*track_length*4.0,
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
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_input_mesh_file_name",
		 &test_input_mesh_file_name,
		 "Test input mesh file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();
  
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

//---------------------------------------------------------------------------//
// end tstTetMeshTrackLengthFluxEstimator.cpp
//---------------------------------------------------------------------------//
