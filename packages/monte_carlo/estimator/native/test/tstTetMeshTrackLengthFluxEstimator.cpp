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
                         std::string "test_unit_cube_tets-6.vtk",
                         std::string "unit_cube_output.vtk" );
    
    // Assign energy bins
    Teuchos::Array<double> energy_bin_boundaries( 3 );
    energy_bin_boundaries[0] = 0.0;
    energy_bin_boundaries[1] = 0.1;
    energy_bin_boundaries[2] = 1.0;
    
    estimator->assignBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(
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
  
  // Start and end locations
  double start_point_1[3] = { 0.25, 0.0, 0.75 };
  double start_point_2[3] = { 0.0, 0.25, 0.75 };
  double start_point_3[3] = { 0.75, 0.25, 0.25 };
  double start_point_4[3] = { 0.25, 0.75, 0.25 };
  double start_point_5[3] = { 0.75, 0.25, 0.0 };
  double start_point_6[3] = { 0.25, 0.75, 0.0 };
  
  double end_point_1[3] = { 0.75, 0.25, 1.0 };
  double end_point_2[3] = { 0.25, 0.75, 1.0 };
  double end_point_3[3] = { 1.0, 0.25, 0.75 };
  double end_point_4[3] = { 0.25, 1.0, 0.75 };
  double end_point_5[3] = { 1.0, 0.75, 0.25 };
  double end_point_6[3] = { 0.75, 1.0, 0.25 };
  
  // bin 0
  MonteCarlo::PhotonState particle( 0ull );
  particle.setWeight( 1.0 );
  particle.setEnergy( 1.0 );
  
  estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                          start_point_1,
                                                          end_point_1 );
                                                          
  estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                          start_point_2,
                                                          end_point_2 );
                                                        
  estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                          start_point_3,
                                                          end_point_3 );

  estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                          start_point_4,
                                                          end_point_4 );
                                                          
  estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                          start_point_5,
                                                          end_point_5 );
                                                        
  estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                          start_point_6,
                                                          end_point_6 );
                                                          
  // bin 1
  particle.setEnergy( 0.1 );
  
  estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                          start_point_1,
                                                          end_point_1 );
                                                          
  estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                          start_point_2,
                                                          end_point_2 );
                                                        
  estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                          start_point_3,
                                                          end_point_3 );

  estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                          start_point_4,
                                                          end_point_4 );
                                                          
  estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                          start_point_5,
                                                          end_point_5 );
                                                        
  estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                          start_point_6,
                                                          end_point_6 );
  
  // Commit history contributions
  estimator_base->commitHistoryContribution(); 
  
  MonteCarlo::Estimator::setNumberofHistories( 1.0 );
  MonteCarlo::Estimator::setEndTime( 1.0 );
  
  // Initialize the HDF5 file
  MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler(
                            "test_tet_mesh_track_length_flux_estimator.h5" ); 
                            
  estimator->exportData( hdf5_file_handler, true );       
  
  // Get the tet EntityHandles for use in data retrieval
  const moab::Range all_tet_elements;
  estimator->getAllTetElements( all_tet_elements );
  
  // Retrieve the raw bin data for each tet
  const moab::Range::const_iterator tet = all_tet_elements.begin();
  
  Teuchos::Array<Utility::Pair<double,double> >
      raw_bin_data( 2, Utility::Pair<double,double>( 
                                            track_length, 
                                            track_length*track_length) ),
      raw_bin_data_copy;
    
  hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
                             0u, *tet, raw_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data, 
                                        raw_bin_data_copy,
                                        1e-15 );
  
  ++tet;

  hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
                             0u, *tet, raw_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data, 
                                        raw_bin_data_copy,
                                        1e-15 );
  
  ++tet;

  hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
                             0u, *tet, raw_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data, 
                                        raw_bin_data_copy,
                                        1e-15 );
  
  ++tet;

  hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
                             0u, *tet, raw_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data, 
                                        raw_bin_data_copy,
                                        1e-15 );
  
  ++tet;

  hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
                             0u, *tet, raw_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data, 
                                        raw_bin_data_copy,
                                        1e-15 );
  
  ++tet;

  hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
                             0u, *tet, raw_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data, 
                                        raw_bin_data_copy,
                                        1e-15 );
  
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
                                        1e-15 );
  
  ++tet;

  hdf5_file_handler.getProcessedEstimatorEntityBinData<moab::EntityHandle>(
                             0u, *tet, processed_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data, 
                                        processed_bin_data_copy,
                                        1e-15 );
  
  ++tet;

  hdf5_file_handler.getProcessedEstimatorEntityBinData<moab::EntityHandle>(
                             0u, *tet, processed_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data, 
                                        processed_bin_data_copy,
                                        1e-15 );
  
  ++tet;

  hdf5_file_handler.getProcessedEstimatorEntityBinData<moab::EntityHandle>(
                             0u, *tet, processed_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data, 
                                        processed_bin_data_copy,
                                        1e-15 );
  
  ++tet;

  hdf5_file_handler.getProcessedEstimatorEntityBinData<moab::EntityHandle>(
                             0u, *tet, processed_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data, 
                                        processed_bin_data_copy,
                                        1e-15 );
  
  ++tet;  
  
  hdf5_file_handler.getProcessedEstimatorEntityBinData<moab::EntityHandle>(
                             0u, *tet, processed_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data, 
                                        processed_bin_data_copy,
                                        1e-15 );
                                          
  // Retrieve the raw total bin data
  tet = all_tet_elements.begin();
  
  Teuchos::Array<Utility::Pair<double,double> >
    raw_total_bin_data( 2, Utility::Pair<double,double>(
                         num_tets*track_length ,
                         num_tets*num_tets*track_length*track_length ) ),
    raw_total_bin_data_copy;  
  
  hdf5_file_handler.getRawEstimatorTotalBinData<moab::EntityHandle>(
                             0u, *tet, raw_total_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_bin_data,
                                        raw_total_bin_data_copy,
                                        1e-15 );
  
  ++tet;

  hdf5_file_handler.getRawEstimatorTotalBinData<moab::EntityHandle>(
                             0u, *tet, raw_total_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_bin_data,
                                        raw_total_bin_data_copy,
                                        1e-15 );
  
  ++tet;

  hdf5_file_handler.getRawEstimatorTotalBinData<moab::EntityHandle>(
                             0u, *tet, raw_total_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_bin_data,
                                        raw_total_bin_data_copy,
                                        1e-15 );
  
  ++tet;

  hdf5_file_handler.getRawEstimatorTotalBinData<moab::EntityHandle>(
                             0u, *tet, raw_total_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_bin_data,
                                        raw_total_bin_data_copy,
                                        1e-15 );
  
  ++tet;

  hdf5_file_handler.getRawEstimatorTotalBinData<moab::EntityHandle>(
                             0u, *tet, raw_total_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_bin_data,
                                        raw_total_bin_data_copy,
                                        1e-15 );
  
  ++tet;

  hdf5_file_handler.getRawEstimatorTotalBinData<moab::EntityHandle>(
                             0u, *tet, raw_total_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_bin_data,
                                        raw_total_bin_data_copy,
                                        1e-15 );
  
  // Retrieve the processed total bin data
  tet = all_tet_elements.begin();
  
  Teuchos::Array<Utility::Pair<double,double> >
    processed_total_bin_data( 2, Utility::Pair<double,double>(
                         num_tets*track_length/volume ,
                         0.0 ) ),
    processed_total_bin_data_copy; 

  hdf5_file_handler.getProcessedEstimatorTotalBinData<moab::EntityHandle>(
                             0u, *tet, processed_total_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_bin_data,
                                        processed_total_bin_data_copy,
                                        1e-15 );
  
  ++tet;

  hdf5_file_handler.getProcessedEstimatorTotalBinData<moab::EntityHandle>(
                             0u, *tet, processed_total_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_bin_data,
                                        processed_total_bin_data_copy,
                                        1e-15 );
  
  ++tet;
  
  hdf5_file_handler.getProcessedEstimatorTotalBinData<moab::EntityHandle>(
                             0u, *tet, processed_total_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_bin_data,
                                        processed_total_bin_data_copy,
                                        1e-15 );
  
  ++tet;
  
  hdf5_file_handler.getProcessedEstimatorTotalBinData<moab::EntityHandle>(
                             0u, *tet, processed_total_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_bin_data,
                                        processed_total_bin_data_copy,
                                        1e-15 );
  
  ++tet;
  
  hdf5_file_handler.getProcessedEstimatorTotalBinData<moab::EntityHandle>(
                             0u, *tet, processed_total_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_bin_data,
                                        processed_total_bin_data_copy,
                                        1e-15 );
  
  ++tet;

  hdf5_file_handler.getProcessedEstimatorTotalBinData<moab::EntityHandle>(
                             0u, *tet, processed_total_bin_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_bin_data,
                                        processed_total_bin_data_copy,
                                        1e-15 );

  // Retrieve the raw estimator total data for each entity
  tet = all_tet_elements.begin();
  
  Utility::Quad<double,double,double,double>
    raw_moments( 2.0*track_length,
                 4.0*track_length*track_length,
                 8.0*track_length*track_length*track_length;
                 16.0*track_length*track_length*track_length*track_length );
                
  Teuchos::Array<Utility::Quad<double,double,double,double> >
    raw_total_data( 1, raw_moments ),
    raw_total_data_copy;
    
  hdf5_file_handler.getRawEstimatorEntityTotalData<moab::EntityHandle>(
                             0u, *tet, raw_total_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
                                        raw_total_data_copy,
                                        1e-15 );
                                        
  ++tet;  

  hdf5_file_handler.getRawEstimatorEntityTotalData<moab::EntityHandle>(
                             0u, *tet, raw_total_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
                                        raw_total_data_copy,
                                        1e-15 );
                                        
  ++tet;
  
  hdf5_file_handler.getRawEstimatorEntityTotalData<moab::EntityHandle>(
                             0u, *tet, raw_total_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
                                        raw_total_data_copy,
                                        1e-15 );
                                        
  ++tet;  


  hdf5_file_handler.getRawEstimatorEntityTotalData<moab::EntityHandle>(
                             0u, *tet, raw_total_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
                                        raw_total_data_copy,
                                        1e-15 );
                                        
  ++tet;

  hdf5_file_handler.getRawEstimatorEntityTotalData<moab::EntityHandle>(
                             0u, *tet, raw_total_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
                                        raw_total_data_copy,
                                        1e-15 );
                                        
  ++tet;

  hdf5_file_handler.getRawEstimatorEntityTotalData<moab::EntityHandle>(
                             0u, *tet, raw_total_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
                                        raw_total_data_copy,
                                        1e-15 );

  // Retrieve the processed estimator total data for each entity
  tet = all_tet_elements.begin();
  
  Utility::Quad<double,double,double,double>
    processed_moments( 2.0*track_length/volume,
                       0.0,
                       0.0,
                       0.0 );
                
  Teuchos::Array<Utility::Quad<double,double,double,double> >
    raw_total_data( 1, raw_moments ),
    raw_total_data_copy;
    
  hdf5_file_handler.getProcessedEstimatorEntityTotalData<moab::EntityHandle>(
                             0u, *tet, processed_total_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data,
                                        processed_total_data_copy,
                                        1e-15 );
                                        
  ++tet;          

  hdf5_file_handler.getProcessedEstimatorEntityTotalData<moab::EntityHandle>(
                             0u, *tet, processed_total_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data,
                                        processed_total_data_copy,
                                        1e-15 );
                                        
  ++tet; 

  hdf5_file_handler.getProcessedEstimatorEntityTotalData<moab::EntityHandle>(
                             0u, *tet, processed_total_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data,
                                        processed_total_data_copy,
                                        1e-15 );
                                        
  ++tet; 

  hdf5_file_handler.getProcessedEstimatorEntityTotalData<moab::EntityHandle>(
                             0u, *tet, processed_total_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data,
                                        processed_total_data_copy,
                                        1e-15 );
                                        
  ++tet; 

  hdf5_file_handler.getProcessedEstimatorEntityTotalData<moab::EntityHandle>(
                             0u, *tet, processed_total_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data,
                                        processed_total_data_copy,
                                        1e-15 );
                                        
  ++tet; 

  hdf5_file_handler.getProcessedEstimatorEntityTotalData<moab::EntityHandle>(
                             0u, *tet, processed_total_data_copy );
                           
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data,
                                        processed_total_data_copy,
                                        1e-15 );

  // Retrieve the raw estimator total data  
  raw_total_data[0]( num_tets*track_length*2.0,
                     (num_tets*num_tets)*(track_length*track_length)*4.0;
                     (num_tets*num_tets*num_tets)*(track_length*track_length*
                       track_length)*8.0;
                     (num_tets*num_tets*num_tets*num_tets)*(track_length*
                       track_length*track_length*track_length)*16.0 );
                
  hdf5_file_handler.getRawEstimatorTotalData( 0u, raw_total_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data, 
                                        raw_total_data_copy,
                                        1e-15 );

  // Retrieve the processed estimator total data
  processed_total_data[0]( num_tets*track_length*2.0/volume,
                           0.0,
                           0.0,
                           0.0 );
                           
  hdf5_file_handler.getProcessedEstimatorTotalData( 0u, 
                                                processed_total_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data, 
                                        processed_total_data_copy,
                                        1e-15 );                           
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
