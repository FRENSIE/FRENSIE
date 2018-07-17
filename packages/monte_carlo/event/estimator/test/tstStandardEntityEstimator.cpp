//---------------------------------------------------------------------------//
//!
//! \file   tstEstimator.cpp
//! \author Alex Robinson
//! \brief  Standard entity estimator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_StandardEntityEstimator.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Utility_OpenMPProperties.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestStandardEntityEstimator : public MonteCarlo::StandardEntityEstimator
{
public:
  TestStandardEntityEstimator( const unsigned long long id,
			       const double multiplier,
			       const std::vector<uint64_t>& entity_ids,
			       const std::vector<double>& entity_norm_constants )
    : MonteCarlo::StandardEntityEstimator( id,
                                           multiplier,
                                           entity_ids,
                                           entity_norm_constants )
  { /* ... */ }

  ~TestStandardEntityEstimator()
  { /* ... */ }

  void printSummary( std::ostream& os ) const final override
  { this->printImplementation( os, "Surface" ); }

  // Allow public access to the standard entity estimator protected mem. funcs.
  using MonteCarlo::StandardEntityEstimator::addPartialHistoryPointContribution;
  using MonteCarlo::StandardEntityEstimator::addPartialHistoryRangeContribution;
  using MonteCarlo::StandardEntityEstimator::assignDiscretization;
};

//---------------------------------------------------------------------------//
// Testing Functions
//---------------------------------------------------------------------------//
// Set the standard entity estimator bins (and response functions)
void setEstimatorBins( TestStandardEntityEstimator& estimator,
                       const bool ranged_time_bins )
{
  // Set the energy bins
  std::vector<double> energy_bin_boundaries( 3 );
  energy_bin_boundaries[0] = 0.0;
  energy_bin_boundaries[1] = 1e-1;
  energy_bin_boundaries[2] = 1.0;

  estimator.setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>(energy_bin_boundaries);

  // Set the cosine bins
  std::vector<double> cosine_bin_boundaries( 3 );
  cosine_bin_boundaries[0] = -1.0;
  cosine_bin_boundaries[1] = 0.0;
  cosine_bin_boundaries[2] = 1.0;

  estimator.setDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION>(cosine_bin_boundaries);

  // Set the time bins
  std::vector<double> time_bin_boundaries( 3 );
  time_bin_boundaries[0] = 0.0;
  time_bin_boundaries[1] = 1e3;
  time_bin_boundaries[2] = 1e5;

  std::shared_ptr<const MonteCarlo::ObserverPhaseSpaceDimensionDiscretization>
    time_discretization( new MonteCarlo::DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION>( time_bin_boundaries ) );

  estimator.assignDiscretization( time_discretization, ranged_time_bins );

  // Set the collision number bins
  std::vector<unsigned> collision_number_bins( 3 );
  collision_number_bins[0] = 0u;
  collision_number_bins[1] = 1u;
  collision_number_bins[2] = std::numeric_limits<unsigned>::max();

  estimator.setDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION>(
						       collision_number_bins );

  // Set the response functions
  std::vector<std::shared_ptr<const MonteCarlo::ParticleResponse> >
    response_functions( 1 );
  response_functions[0] = MonteCarlo::ParticleResponse::getDefault();
  
  estimator.setResponseFunctions( response_functions );
}

// Initialize the standard entity estimator (int)
void initializeStandardEntityEstimator( std::shared_ptr<TestStandardEntityEstimator>& estimator,
                                        const bool ranged_time_bins = false )
{
  // Set the entity ids
  std::vector<uint64_t> entity_ids( 2 );
  entity_ids[0] = 0;
  entity_ids[1] = 1;

  // Set the entity normalization constants
  std::vector<double> entity_norm_constants( 2 );
  entity_norm_constants[0] = 1.0;
  entity_norm_constants[1] = 2.0;

  // Set the estimator multiplier
  double estimator_multiplier = 10.0;

  estimator.reset( new TestStandardEntityEstimator( 0ull,
                                                    estimator_multiplier,
                                                    entity_ids,
                                                    entity_norm_constants ) );

  std::vector<MonteCarlo::ParticleType> particle_types( 1 );
  particle_types[0] = MonteCarlo::PHOTON;
  
  estimator->setParticleTypes( particle_types );

  setEstimatorBins( *estimator, ranged_time_bins );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the number of bins can be returned
FRENSIE_UNIT_TEST( StandardEntityEstimator, getNumberOfBins )
{
  std::shared_ptr<TestStandardEntityEstimator> estimator;
  initializeStandardEntityEstimator( estimator );

  FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins(), 24 );
}

// //---------------------------------------------------------------------------//
// // Check that the number of response functions can be returned
// TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( StandardEntityEstimator,
// 				   getNumberOfResponseFunctions,
// 				   EntityId )
// {
//   Teuchos::RCP<TestStandardEntityEstimator<EntityId> > estimator;
//   initializeStandardEntityEstimator( estimator );

//   FRENSIE_CHECK_EQUAL( estimator->getNumberOfResponseFunctions(), 1 );
// }

// UNIT_TEST_INSTANTIATION( StandardEntityEstimator,
// 			 getNumberOfResponseFunctions );

// //---------------------------------------------------------------------------//
// // Check that the raw estimator data can be exported
// TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( StandardEntityEstimator,
// 				   exportData_raw,
// 				   EntityId )
// {
//   Teuchos::RCP<MonteCarlo::Estimator> estimator;

//   std::vector<uint64_t> entity_ids;
//   std::vector<double> entity_norm_constants;

//   {
//     // Set the entities ids
//     entity_ids.resize( 5 );
//     entity_ids[0] = 0;
//     entity_ids[1] = 1;
//     entity_ids[2] = 2;
//     entity_ids[3] = 3;
//     entity_ids[4] = 4;

//     // Set the entity normalization constants
//     entity_norm_constants.resize( 5 );
//     entity_norm_constants[0] = 1.0;
//     entity_norm_constants[1] = 2.0;
//     entity_norm_constants[2] = 3.0;
//     entity_norm_constants[3] = 4.0;
//     entity_norm_constants[4] = 5.0;

//     estimator.reset( new TestStandardEntityEstimator<EntityId>(
// 						     0u,
// 						     5.0,
// 						     entity_ids,
// 						     entity_norm_constants ) );
//   }

//   std::vector<double> energy_bin_boundaries, cosine_bin_boundaries,
//     time_bin_boundaries;
//   std::vector<unsigned> collision_number_bins;

//   {
//     // Set the energy bins
//     energy_bin_boundaries.resize( 3 );
//     energy_bin_boundaries[0] = 0.0;
//     energy_bin_boundaries[1] = 1e-1;
//     energy_bin_boundaries[2] = 1.0;

//     estimator->setDiscretization<MonteCarlo::ENERGY_DIMENSION>(
// 						       energy_bin_boundaries );

//     // Set the cosine bins
//     cosine_bin_boundaries.resize( 3 );
//     cosine_bin_boundaries[0] = -1.0;
//     cosine_bin_boundaries[1] = 0.0;
//     cosine_bin_boundaries[2] = 1.0;

//     estimator->setDiscretization<MonteCarlo::COSINE_DIMENSION>(
// 						       cosine_bin_boundaries );

//     // Set the time bins
//     time_bin_boundaries.resize( 3 );
//     time_bin_boundaries[0] = 0.0;
//     time_bin_boundaries[1] = 1e3;
//     time_bin_boundaries[2] = 1e5;

//     estimator->setDiscretization<MonteCarlo::TIME_DIMENSION>(
// 							 time_bin_boundaries );

//     // Set the collision number bins
//     collision_number_bins.resize( 3 );
//     collision_number_bins[0] = 0u;
//     collision_number_bins[1] = 1u;
//     collision_number_bins[2] = std::numeric_limits<unsigned>::max();

//     estimator->setDiscretization<MonteCarlo::COLLISION_NUMBER_DIMENSION>(
// 						       collision_number_bins );

//     // Set the response functions
//     std::vector<std::shared_ptr<MonteCarlo::ResponseFunction> >
//       response_functions( 1 );
//     response_functions[0] =
//       MonteCarlo::ResponseFunction::default_response_function;

//     estimator->setResponseFunctions( response_functions );
//   }

//   // Initialize the hdf5 file
//   std::shared_ptr<Utility::HDF5FileHandler>
//     hdf5_file( new Utility::HDF5FileHandler );
//   hdf5_file->openHDF5FileAndOverwrite( "test_standard_entity_estimator.h5" );

//   estimator->exportData( hdf5_file, false );

//   // Create an estimator hdf5 file handler
//   MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( hdf5_file );

//   // Make sure that the estimator exists in the hdf5 file
//   TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 0u ) );

//   // Check that the estimator multiplier has been set
//   double multiplier;
//   hdf5_file_handler.getEstimatorMultiplier( 0u, multiplier );

//   FRENSIE_CHECK_EQUAL( multiplier, 5.0 );

//   // Check that the estimator response function ordering has been set
//   std::vector<unsigned> response_function_ordering;
//   hdf5_file_handler.getEstimatorResponseFunctionOrdering(
// 						  0u,
// 						  response_function_ordering );

//   FRENSIE_CHECK_EQUAL( response_function_ordering.size(), 1 );
//   TEST_EQUALITY( response_function_ordering[0],
// 		 std::numeric_limits<unsigned>::max() );

//   // Check that the estimator dimension ordering has been set
//   std::vector<MonteCarlo::PhaseSpaceDimension> dimension_ordering;
//   hdf5_file_handler.getEstimatorDimensionOrdering( 0u, dimension_ordering );

//   FRENSIE_CHECK_EQUAL( dimension_ordering.size(), 4 );
//   FRENSIE_CHECK_EQUAL( dimension_ordering[0], MonteCarlo::ENERGY_DIMENSION );
//   FRENSIE_CHECK_EQUAL( dimension_ordering[1], MonteCarlo::COSINE_DIMENSION );
//   FRENSIE_CHECK_EQUAL( dimension_ordering[2], MonteCarlo::TIME_DIMENSION );
//   FRENSIE_CHECK_EQUAL( dimension_ordering[3],
// 		       MonteCarlo::COLLISION_NUMBER_DIMENSION );

//   // Check that the energy bins have been set
//   std::vector<double> energy_bin_boundaries_copy;
//   hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(
// 						  0u,
// 						  energy_bin_boundaries_copy );

//   TEST_COMPARE_ARRAYS( energy_bin_boundaries, energy_bin_boundaries_copy );

//   // Check that the cosine bins have been set
//   std::vector<double> cosine_bin_boundaries_copy;
//   hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::COSINE_DIMENSION>(
// 						  0u,
// 						  cosine_bin_boundaries_copy );

//   TEST_COMPARE_ARRAYS( cosine_bin_boundaries, cosine_bin_boundaries_copy );

//   // Check that the time bins have been set
//   std::vector<double> time_bin_boundaries_copy;
//   hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::TIME_DIMENSION>(
// 						    0u,
// 						    time_bin_boundaries_copy );

//   TEST_COMPARE_ARRAYS( time_bin_boundaries, time_bin_boundaries_copy );

//   // Check that the collision number bins have been set
//   std::vector<unsigned> collision_number_bins_copy;
//   hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::COLLISION_NUMBER_DIMENSION>(
// 						  0u,
// 						  collision_number_bins_copy );

//   TEST_COMPARE_ARRAYS( collision_number_bins, collision_number_bins_copy );

//   // Check if entities are assigned to the estimator
//   TEST_ASSERT( hdf5_file_handler.isEntityAssignedToEstimator<EntityId>(
// 								    0u, 0u ) );
//   TEST_ASSERT( hdf5_file_handler.isEntityAssignedToEstimator<EntityId>(
// 								    0u, 1u ) );
//   TEST_ASSERT( hdf5_file_handler.isEntityAssignedToEstimator<EntityId>(
// 								    0u, 2u ) );
//   TEST_ASSERT( hdf5_file_handler.isEntityAssignedToEstimator<EntityId>(
// 								    0u, 3u ) );
//   TEST_ASSERT( hdf5_file_handler.isEntityAssignedToEstimator<EntityId>(
// 								    0u, 4u ) );
//   TEST_ASSERT( !hdf5_file_handler.isEntityAssignedToEstimator<EntityId>(
// 								    0u, 5u ) );

//   // Check that the entities and norm constants have been set
//   std::map<EntityId,double> entity_id_norms;
//   hdf5_file_handler.getEstimatorEntities( 0u, entity_id_norms );

//   FRENSIE_CHECK_EQUAL( entity_id_norms.size(), 5 );
//   FRENSIE_CHECK_EQUAL( entity_id_norms[0], 1.0 );
//   FRENSIE_CHECK_EQUAL( entity_id_norms[1], 2.0 );
//   FRENSIE_CHECK_EQUAL( entity_id_norms[2], 3.0 );
//   FRENSIE_CHECK_EQUAL( entity_id_norms[3], 4.0 );
//   FRENSIE_CHECK_EQUAL( entity_id_norms[4], 5.0 );

//   // Check that entity norm constants have been set
//   double entity_norm_constant;
//   hdf5_file_handler.getEntityNormConstant( 0u, 0u, entity_norm_constant );

//   FRENSIE_CHECK_EQUAL( entity_norm_constant, 1.0 );

//   hdf5_file_handler.getEntityNormConstant( 0u, 1u, entity_norm_constant );

//   FRENSIE_CHECK_EQUAL( entity_norm_constant, 2.0 );

//   hdf5_file_handler.getEntityNormConstant( 0u, 2u, entity_norm_constant );

//   FRENSIE_CHECK_EQUAL( entity_norm_constant, 3.0 );

//   hdf5_file_handler.getEntityNormConstant( 0u, 3u, entity_norm_constant );

//   FRENSIE_CHECK_EQUAL( entity_norm_constant, 4.0 );

//   hdf5_file_handler.getEntityNormConstant( 0u, 4u, entity_norm_constant );

//   FRENSIE_CHECK_EQUAL( entity_norm_constant, 5.0 );

//   // Check that the total norm constant has been set
//   double total_norm_constant;
//   hdf5_file_handler.getEstimatorTotalNormConstant( 0u, total_norm_constant );

//   FRENSIE_CHECK_EQUAL( total_norm_constant, 15.0 );

//   // Check that the raw entity bin data has been set
//   std::vector<Utility::Pair<double,double> >
//     raw_bin_data( 24, Utility::Pair<double,double>( 0.0, 0.0 ) ),
//     raw_bin_data_copy;

//   hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 0u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

//   hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 1u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

//   hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 2u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

//   hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 3u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

//   hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 4u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

//   // Check that there is no processed data since it was not requested on export
//   std::vector<Utility::Pair<double,double> >
//     processed_bin_data_copy;

//   TEST_THROW( hdf5_file_handler.getProcessedEstimatorEntityBinData(
// 						     0u,
// 						     0u,
// 						     processed_bin_data_copy ),
// 	      std::runtime_error );
//   TEST_THROW( hdf5_file_handler.getProcessedEstimatorEntityBinData(
// 						     0u,
// 						     1u,
// 						     processed_bin_data_copy ),
// 	      std::runtime_error );
//   TEST_THROW( hdf5_file_handler.getProcessedEstimatorEntityBinData(
// 						     0u,
// 						     2u,
// 						     processed_bin_data_copy ),
// 	      std::runtime_error );
//   TEST_THROW( hdf5_file_handler.getProcessedEstimatorEntityBinData(
// 						     0u,
// 						     3u,
// 						     processed_bin_data_copy ),
// 	      std::runtime_error );
//   TEST_THROW( hdf5_file_handler.getProcessedEstimatorEntityBinData(
// 						     0u,
// 						     4u,
// 						     processed_bin_data_copy ),
// 	      std::runtime_error );

//   // Check that the raw total bin data has been set
//   std::vector<Utility::Pair<double,double> >
//     raw_total_bin_data( 24, Utility::Pair<double,double>( 0.0, 0.0 ) ),
//     raw_total_bin_data_copy;

//   hdf5_file_handler.getRawEstimatorTotalBinData( 0u, raw_total_bin_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_total_bin_data, raw_total_bin_data_copy );

//   // Check that the processed total bin data has not been set
//   std::vector<Utility::Pair<double,double> >
//     processed_total_bin_data;

//   TEST_THROW( hdf5_file_handler.getProcessedEstimatorTotalBinData(
// 						0u, processed_total_bin_data ),
// 	      std::runtime_error );

//   Utility::Quad<double,double,double,double> empty_quad( 0.0, 0.0, 0.0, 0.0 );

//   // Check that the raw total entity data has been set
//   std::vector<Utility::Quad<double,double,double,double> >
//     raw_total_entity_data( 1, empty_quad ),
//     raw_total_entity_data_copy;

//   hdf5_file_handler.getRawEstimatorEntityTotalData<EntityId>(
// 					  0u, 0u, raw_total_entity_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_total_entity_data,
// 			       raw_total_entity_data_copy );

//   hdf5_file_handler.getRawEstimatorEntityTotalData<EntityId>(
// 					  0u, 1u, raw_total_entity_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_total_entity_data,
// 			       raw_total_entity_data_copy );

//   hdf5_file_handler.getRawEstimatorEntityTotalData<EntityId>(
// 					  0u, 2u, raw_total_entity_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_total_entity_data,
// 			       raw_total_entity_data_copy );

//   hdf5_file_handler.getRawEstimatorEntityTotalData<EntityId>(
// 					  0u, 3u, raw_total_entity_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_total_entity_data,
// 			       raw_total_entity_data_copy );

//   hdf5_file_handler.getRawEstimatorEntityTotalData<EntityId>(
// 					  0u, 4u, raw_total_entity_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_total_entity_data,
// 			       raw_total_entity_data_copy );

//   // Check that the processed total entity data has not been set
//   std::vector<Utility::Quad<double,double,double,double> >
//     processed_total_entity_data;

//   TEST_THROW( hdf5_file_handler.getProcessedEstimatorEntityTotalData<EntityId>(
// 					 0u, 0u, processed_total_entity_data ),
// 	      std::runtime_error );
//   TEST_THROW( hdf5_file_handler.getProcessedEstimatorEntityTotalData<EntityId>(
// 					 0u, 1u, processed_total_entity_data ),
// 	      std::runtime_error );
//   TEST_THROW( hdf5_file_handler.getProcessedEstimatorEntityTotalData<EntityId>(
// 					 0u, 2u, processed_total_entity_data ),
// 	      std::runtime_error );
//   TEST_THROW( hdf5_file_handler.getProcessedEstimatorEntityTotalData<EntityId>(
// 					 0u, 3u, processed_total_entity_data ),
// 	      std::runtime_error );
//   TEST_THROW( hdf5_file_handler.getProcessedEstimatorEntityTotalData<EntityId>(
// 					 0u, 4u, processed_total_entity_data ),
// 	      std::runtime_error );

//   // Check that the raw total data has been set
//   std::vector<Utility::Quad<double,double,double,double> >
//     raw_total_data( 1, empty_quad ),
//     raw_total_data_copy;

//   hdf5_file_handler.getRawEstimatorTotalData( 0u, raw_total_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_total_data, raw_total_data_copy );

//   // Check that the processed total data has been set
//   std::vector<Utility::Quad<double,double,double,double> >
//     processed_total_data;

//   TEST_THROW( hdf5_file_handler.getProcessedEstimatorTotalData(
// 						    0u, processed_total_data ),
// 	      std::runtime_error );
// }

// UNIT_TEST_INSTANTIATION( StandardEntityEstimator,
// 			 exportData_raw );

// //---------------------------------------------------------------------------//
// // Check that the processed estimator data can be exported
// TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( StandardEntityEstimator,
// 				   exportData_process,
// 				   EntityId )
// {
//   Teuchos::RCP<MonteCarlo::Estimator> estimator;

//   std::vector<uint64_t> entity_ids;
//   std::vector<double> entity_norm_constants;

//   {
//     // Set the entities ids
//     entity_ids.resize( 5 );
//     entity_ids[0] = 0;
//     entity_ids[1] = 1;
//     entity_ids[2] = 2;
//     entity_ids[3] = 3;
//     entity_ids[4] = 4;

//     // Set the entity normalization constants
//     entity_norm_constants.resize( 5 );
//     entity_norm_constants[0] = 1.0;
//     entity_norm_constants[1] = 2.0;
//     entity_norm_constants[2] = 3.0;
//     entity_norm_constants[3] = 4.0;
//     entity_norm_constants[4] = 5.0;

//     estimator.reset( new TestStandardEntityEstimator<EntityId>(
// 						     0u,
// 						     5.0,
// 						     entity_ids,
// 						     entity_norm_constants ) );
//   }

//   std::vector<double> energy_bin_boundaries, cosine_bin_boundaries,
//     time_bin_boundaries;
//   std::vector<unsigned> collision_number_bins;

//   {
//     // Set the energy bins
//     energy_bin_boundaries.resize( 3 );
//     energy_bin_boundaries[0] = 0.0;
//     energy_bin_boundaries[1] = 1e-1;
//     energy_bin_boundaries[2] = 1.0;

//     estimator->setDiscretization<MonteCarlo::ENERGY_DIMENSION>(
// 						       energy_bin_boundaries );

//     // Set the cosine bins
//     cosine_bin_boundaries.resize( 3 );
//     cosine_bin_boundaries[0] = -1.0;
//     cosine_bin_boundaries[1] = 0.0;
//     cosine_bin_boundaries[2] = 1.0;

//     estimator->setDiscretization<MonteCarlo::COSINE_DIMENSION>(
// 						       cosine_bin_boundaries );

//     // Set the time bins
//     time_bin_boundaries.resize( 3 );
//     time_bin_boundaries[0] = 0.0;
//     time_bin_boundaries[1] = 1e3;
//     time_bin_boundaries[2] = 1e5;

//     estimator->setDiscretization<MonteCarlo::TIME_DIMENSION>(
// 							 time_bin_boundaries );

//     // Set the collision number bins
//     collision_number_bins.resize( 3 );
//     collision_number_bins[0] = 0u;
//     collision_number_bins[1] = 1u;
//     collision_number_bins[2] = std::numeric_limits<unsigned>::max();

//     estimator->setDiscretization<MonteCarlo::COLLISION_NUMBER_DIMENSION>(
// 						       collision_number_bins );

//     // Set the response functions
//     std::vector<std::shared_ptr<MonteCarlo::ResponseFunction> >
//       response_functions( 1 );
//     response_functions[0] =
//       MonteCarlo::ResponseFunction::default_response_function;

//     estimator->setResponseFunctions( response_functions );
//   }

//   // Initialize the hdf5 file
//   std::shared_ptr<Utility::HDF5FileHandler>
//     hdf5_file( new Utility::HDF5FileHandler );
//   hdf5_file->openHDF5FileAndOverwrite( "test_standard_entity_estimator.h5" );

//   MonteCarlo::ParticleHistoryObserver::setStartTime( 0.0 );
//   MonteCarlo::ParticleHistoryObserver::setEndTime( 1.0 );
//   MonteCarlo::ParticleHistoryObserver::setNumberOfHistories( 1 );

//   estimator->exportData( hdf5_file, true );

//   // Create an estimator hdf5 file handler
//   MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( hdf5_file );

//   // Make sure that the estimator exists in the hdf5 file
//   TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 0u ) );

//   // Check that the estimator multiplier has been set
//   double multiplier;
//   hdf5_file_handler.getEstimatorMultiplier( 0u, multiplier );

//   FRENSIE_CHECK_EQUAL( multiplier, 5.0 );

//   // Check that the estimator response function ordering has been set
//   std::vector<unsigned> response_function_ordering;
//   hdf5_file_handler.getEstimatorResponseFunctionOrdering(
// 						  0u,
// 						  response_function_ordering );

//   FRENSIE_CHECK_EQUAL( response_function_ordering.size(), 1 );
//   TEST_EQUALITY( response_function_ordering[0],
// 		 std::numeric_limits<unsigned>::max() );

//   // Check that the estimator dimension ordering has been set
//   std::vector<MonteCarlo::PhaseSpaceDimension> dimension_ordering;
//   hdf5_file_handler.getEstimatorDimensionOrdering( 0u, dimension_ordering );

//   FRENSIE_CHECK_EQUAL( dimension_ordering.size(), 4 );
//   FRENSIE_CHECK_EQUAL( dimension_ordering[0], MonteCarlo::ENERGY_DIMENSION );
//   FRENSIE_CHECK_EQUAL( dimension_ordering[1], MonteCarlo::COSINE_DIMENSION );
//   FRENSIE_CHECK_EQUAL( dimension_ordering[2], MonteCarlo::TIME_DIMENSION );
//   FRENSIE_CHECK_EQUAL( dimension_ordering[3],
// 		       MonteCarlo::COLLISION_NUMBER_DIMENSION );

//   // Check that the energy bins have been set
//   std::vector<double> energy_bin_boundaries_copy;
//   hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(
// 						  0u,
// 						  energy_bin_boundaries_copy );

//   TEST_COMPARE_ARRAYS( energy_bin_boundaries, energy_bin_boundaries_copy );

//   // Check that the cosine bins have been set
//   std::vector<double> cosine_bin_boundaries_copy;
//   hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::COSINE_DIMENSION>(
// 						  0u,
// 						  cosine_bin_boundaries_copy );

//   TEST_COMPARE_ARRAYS( cosine_bin_boundaries, cosine_bin_boundaries_copy );

//   // Check that the time bins have been set
//   std::vector<double> time_bin_boundaries_copy;
//   hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::TIME_DIMENSION>(
// 						    0u,
// 						    time_bin_boundaries_copy );

//   TEST_COMPARE_ARRAYS( time_bin_boundaries, time_bin_boundaries_copy );

//   // Check that the collision number bins have been set
//   std::vector<unsigned> collision_number_bins_copy;
//   hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::COLLISION_NUMBER_DIMENSION>(
// 						  0u,
// 						  collision_number_bins_copy );

//   TEST_COMPARE_ARRAYS( collision_number_bins, collision_number_bins_copy );

//   // Check if entities are assigned to the estimator
//   TEST_ASSERT( hdf5_file_handler.isEntityAssignedToEstimator<EntityId>(
// 								    0u, 0u ) );
//   TEST_ASSERT( hdf5_file_handler.isEntityAssignedToEstimator<EntityId>(
// 								    0u, 1u ) );
//   TEST_ASSERT( hdf5_file_handler.isEntityAssignedToEstimator<EntityId>(
// 								    0u, 2u ) );
//   TEST_ASSERT( hdf5_file_handler.isEntityAssignedToEstimator<EntityId>(
// 								    0u, 3u ) );
//   TEST_ASSERT( hdf5_file_handler.isEntityAssignedToEstimator<EntityId>(
// 								    0u, 4u ) );
//   TEST_ASSERT( !hdf5_file_handler.isEntityAssignedToEstimator<EntityId>(
// 								    0u, 5u ) );

//   // Check that the entities and norm constants have been set
//   std::map<EntityId,double> entity_id_norms;
//   hdf5_file_handler.getEstimatorEntities( 0u, entity_id_norms );

//   FRENSIE_CHECK_EQUAL( entity_id_norms.size(), 5 );
//   FRENSIE_CHECK_EQUAL( entity_id_norms[0], 1.0 );
//   FRENSIE_CHECK_EQUAL( entity_id_norms[1], 2.0 );
//   FRENSIE_CHECK_EQUAL( entity_id_norms[2], 3.0 );
//   FRENSIE_CHECK_EQUAL( entity_id_norms[3], 4.0 );
//   FRENSIE_CHECK_EQUAL( entity_id_norms[4], 5.0 );

//   // Check that entity norm constants have been set
//   double entity_norm_constant;
//   hdf5_file_handler.getEntityNormConstant( 0u, 0u, entity_norm_constant );

//   FRENSIE_CHECK_EQUAL( entity_norm_constant, 1.0 );

//   hdf5_file_handler.getEntityNormConstant( 0u, 1u, entity_norm_constant );

//   FRENSIE_CHECK_EQUAL( entity_norm_constant, 2.0 );

//   hdf5_file_handler.getEntityNormConstant( 0u, 2u, entity_norm_constant );

//   FRENSIE_CHECK_EQUAL( entity_norm_constant, 3.0 );

//   hdf5_file_handler.getEntityNormConstant( 0u, 3u, entity_norm_constant );

//   FRENSIE_CHECK_EQUAL( entity_norm_constant, 4.0 );

//   hdf5_file_handler.getEntityNormConstant( 0u, 4u, entity_norm_constant );

//   FRENSIE_CHECK_EQUAL( entity_norm_constant, 5.0 );

//   // Check that the total norm constant has been set
//   double total_norm_constant;
//   hdf5_file_handler.getEstimatorTotalNormConstant( 0u, total_norm_constant );

//   FRENSIE_CHECK_EQUAL( total_norm_constant, 15.0 );

//   // Check that the raw entity bin data has been set
//   std::vector<Utility::Pair<double,double> >
//     raw_bin_data( 24, Utility::Pair<double,double>( 0.0, 0.0 ) ),
//     raw_bin_data_copy;

//   hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 0u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

//   hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 1u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

//   hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 2u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

//   hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 3u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

//   hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 4u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

//   // Check that there is no processed data since it was not requested on export
//   std::vector<Utility::Pair<double,double> >
//     processed_bin_data( 24, Utility::Pair<double,double>( 0.0, 0.0 ) ),
//     processed_bin_data_copy;

//   hdf5_file_handler.getProcessedEstimatorEntityBinData(
// 						     0u,
// 						     0u,
// 						     processed_bin_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( processed_bin_data, processed_bin_data_copy );

//   hdf5_file_handler.getProcessedEstimatorEntityBinData(
// 						     0u,
// 						     1u,
// 						     processed_bin_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( processed_bin_data, processed_bin_data_copy );

//   hdf5_file_handler.getProcessedEstimatorEntityBinData(
// 						     0u,
// 						     2u,
// 						     processed_bin_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( processed_bin_data, processed_bin_data_copy );

//   hdf5_file_handler.getProcessedEstimatorEntityBinData(
// 						     0u,
// 						     3u,
// 						     processed_bin_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( processed_bin_data, processed_bin_data_copy );

//   hdf5_file_handler.getProcessedEstimatorEntityBinData(
// 						     0u,
// 						     4u,
// 						     processed_bin_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( processed_bin_data, processed_bin_data_copy );

//   // Check that the raw total bin data has been set
//   std::vector<Utility::Pair<double,double> >
//     raw_total_bin_data( 24, Utility::Pair<double,double>( 0.0, 0.0 ) ),
//     raw_total_bin_data_copy;

//   hdf5_file_handler.getRawEstimatorTotalBinData( 0u, raw_total_bin_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_total_bin_data, raw_total_bin_data_copy );

//   // Check that the processed total bin data has not been set
//   std::vector<Utility::Pair<double,double> >
//     processed_total_bin_data( 24, Utility::Pair<double,double>( 0.0, 0.0 ) ),
//     processed_total_bin_data_copy;

//   hdf5_file_handler.getProcessedEstimatorTotalBinData(
// 					   0u, processed_total_bin_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( processed_total_bin_data,
// 			       processed_total_bin_data_copy );

//   Utility::Quad<double,double,double,double> empty_quad( 0.0, 0.0, 0.0, 0.0 );

//   // Check that the raw total entity data has been set
//   std::vector<Utility::Quad<double,double,double,double> >
//     raw_total_entity_data( 1, empty_quad ),
//     raw_total_entity_data_copy;

//   hdf5_file_handler.getRawEstimatorEntityTotalData<EntityId>(
// 					  0u, 0u, raw_total_entity_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_total_entity_data,
// 			       raw_total_entity_data_copy );

//   hdf5_file_handler.getRawEstimatorEntityTotalData<EntityId>(
// 					  0u, 1u, raw_total_entity_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_total_entity_data,
// 			       raw_total_entity_data_copy );

//   hdf5_file_handler.getRawEstimatorEntityTotalData<EntityId>(
// 					  0u, 2u, raw_total_entity_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_total_entity_data,
// 			       raw_total_entity_data_copy );

//   hdf5_file_handler.getRawEstimatorEntityTotalData<EntityId>(
// 					  0u, 3u, raw_total_entity_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_total_entity_data,
// 			       raw_total_entity_data_copy );

//   hdf5_file_handler.getRawEstimatorEntityTotalData<EntityId>(
// 					  0u, 4u, raw_total_entity_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_total_entity_data,
// 			       raw_total_entity_data_copy );

//   // Check that the processed total entity data has not been set
//   std::vector<Utility::Quad<double,double,double,double> >
//     processed_total_entity_data( 1, empty_quad ),
//     processed_total_entity_data_copy;

//   hdf5_file_handler.getProcessedEstimatorEntityTotalData<EntityId>(
// 				    0u, 0u, processed_total_entity_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( processed_total_entity_data,
// 			       processed_total_entity_data_copy );

//   hdf5_file_handler.getProcessedEstimatorEntityTotalData<EntityId>(
// 				    0u, 1u, processed_total_entity_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( processed_total_entity_data,
// 			       processed_total_entity_data_copy );

//   hdf5_file_handler.getProcessedEstimatorEntityTotalData<EntityId>(
// 				    0u, 2u, processed_total_entity_data_copy );

//   hdf5_file_handler.getProcessedEstimatorEntityTotalData<EntityId>(
// 				    0u, 3u, processed_total_entity_data_copy );

//   hdf5_file_handler.getProcessedEstimatorEntityTotalData<EntityId>(
// 				    0u, 4u, processed_total_entity_data_copy );

//   // Check that the raw total data has been set
//   std::vector<Utility::Quad<double,double,double,double> >
//     raw_total_data( 1, empty_quad ),
//     raw_total_data_copy;

//   hdf5_file_handler.getRawEstimatorTotalData( 0u, raw_total_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_total_data, raw_total_data_copy );

//   // Check that the processed total data has been set
//   std::vector<Utility::Quad<double,double,double,double> >
//     processed_total_data( 1, empty_quad ),
//     processed_total_data_copy;

//   hdf5_file_handler.getProcessedEstimatorTotalData(
// 					       0u, processed_total_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( processed_total_data,
// 			       processed_total_data_copy );
// }

// UNIT_TEST_INSTANTIATION( StandardEntityEstimator,
// 			 exportData_process );

// //---------------------------------------------------------------------------//
// // Check that a partial history contribution can be added to the estimator
// TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( StandardEntityEstimator,
// 				   addPartialHistoryContribution,
// 				   EntityId )
// {
//   Teuchos::RCP<MonteCarlo::Estimator> estimator_base;
//   Teuchos::RCP<TestStandardEntityEstimator<EntityId> > estimator;

//   {
//     // Set the entity ids
//     std::vector<uint64_t> entity_ids( 2 );
//     entity_ids[0] = 0;
//     entity_ids[1] = 1;

//     // Set the entity norm constants
//     std::vector<double> entity_norm_consts( 2 );
//     entity_norm_consts[0] = 1.0;
//     entity_norm_consts[1] = 2.0;

//     estimator.reset(
// 	     new TestStandardEntityEstimator<EntityId>( 0u,
// 							10.0,
// 							entity_ids,
// 							entity_norm_consts ) );

//     estimator_base = estimator;

//     // Set the energy bins
//     std::vector<double> energy_bin_boundaries( 3 );
//     energy_bin_boundaries[0] = 0.0;
//     energy_bin_boundaries[1] = 0.1;
//     energy_bin_boundaries[2] = 1.0;

//     estimator_base->setDiscretization<MonteCarlo::ENERGY_DIMENSION>(
// 						       energy_bin_boundaries );

//     // Set the cosine bins
//     std::vector<double> cosine_bin_boundaries( 3 );
//     cosine_bin_boundaries[0] = -1.0;
//     cosine_bin_boundaries[1] = 0.0;
//     cosine_bin_boundaries[2] = 1.0;

//     estimator_base->setDiscretization<MonteCarlo::COSINE_DIMENSION>(
// 						       cosine_bin_boundaries );

//     // Set the time bins
//     std::vector<double> time_bin_boundaries( 3 );
//     time_bin_boundaries[0] = 0.0;
//     time_bin_boundaries[1] = 1.0;
//     time_bin_boundaries[2] = 2.0;

//     estimator_base->setDiscretization<MonteCarlo::TIME_DIMENSION>(
// 							 time_bin_boundaries );

//     // Set collision number bins
//     std::vector<unsigned> collision_number_bins( 2 );
//     collision_number_bins[0] = 0u;
//     collision_number_bins[1] = 1u;

//     estimator_base->setDiscretization<MonteCarlo::COLLISION_NUMBER_DIMENSION>(
// 						       collision_number_bins );

//     // Set the particle types
//     std::vector<MonteCarlo::ParticleType> particle_types( 1 );
//     particle_types[0] = MonteCarlo::PHOTON;

//     estimator_base->setParticleTypes( particle_types );
//   }

//   TEST_ASSERT( !estimator_base->hasUncommittedHistoryContribution() );

//   // bin 0
//   MonteCarlo::PhotonState particle( 0ull );
//   particle.setEnergy( 1.0 );
//   particle.setTime( 2.0 );

//   MonteCarlo::EstimatorParticleStateWrapper particle_wrapper( particle );
//   particle_wrapper.setAngleCosine( 1.0 );

//   estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//   estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//   TEST_ASSERT( estimator_base->hasUncommittedHistoryContribution() );

//   // bin 1
//   particle.setEnergy( 0.1 );

//   estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//   estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//   // bin 2
//   particle.setEnergy( 1.0 );

//   particle_wrapper.setAngleCosine( 0.0 );

//   estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//   estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//   // bin 3
//   particle.setEnergy( 0.1 );

//   estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//   estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//   // bin 4
//   particle.setTime( 1.0 );
//   particle.setEnergy( 1.0 );

//   particle_wrapper.setAngleCosine( 1.0 );

//   estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//   estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//   // bin 5
//   particle.setEnergy( 0.1 );

//   estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//   estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//   // bin 6
//   particle.setEnergy( 1.0 );

//   particle_wrapper.setAngleCosine( 0.0 );

//   estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//   estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//   // bin 7
//   particle.setEnergy( 0.1 );

//   estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//   estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//   // bin 8
//   particle.incrementCollisionNumber();
//   particle.setTime( 2.0 );
//   particle.setEnergy( 1.0 );

//   particle_wrapper.setAngleCosine( 1.0 );

//   estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//   estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//   // bin 9
//   particle.setEnergy( 0.1 );

//   estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//   estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//   // bin 10
//   particle.setEnergy( 1.0 );

//   particle_wrapper.setAngleCosine( 0.0 );

//   estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//   estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//   // bin 11
//   particle.setEnergy( 0.1 );

//   estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//   estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//   // bin 12
//   particle.setTime( 1.0 );
//   particle.setEnergy( 1.0 );

//   particle_wrapper.setAngleCosine( 1.0 );

//   estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//   estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//   // bin 13
//   particle.setEnergy( 0.1 );

//   estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//   estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//   // bin 14
//   particle.setEnergy( 1.0 );

//   particle_wrapper.setAngleCosine( 0.0 );

//   estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//   estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//   // bin 15
//   particle.setEnergy( 0.1 );

//   estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//   estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//   // Commit the contributions
//   estimator_base->commitHistoryContribution();

//   TEST_ASSERT( !estimator_base->hasUncommittedHistoryContribution() );

//   MonteCarlo::ParticleHistoryObserver::setNumberOfHistories( 1.0 );
//   MonteCarlo::ParticleHistoryObserver::setEndTime( 1.0 );

//   // Initialize the HDF5 file
//   std::shared_ptr<Utility::HDF5FileHandler>
//     hdf5_file( new Utility::HDF5FileHandler );
//   hdf5_file->openHDF5FileAndOverwrite( "test_standard_entity_estimator2.h5" );

//   estimator_base->exportData( hdf5_file, true );

//   // Create an estimator hdf5 file handler
//   MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( hdf5_file );

//   // Retrieve the raw bin data for each entity
//   std::vector<Utility::Pair<double,double> >
//     raw_bin_data( 16, Utility::Pair<double,double>( 1.0, 1.0 ) ),
//     raw_bin_data_copy;

//   hdf5_file_handler.getRawEstimatorEntityBinData<EntityId>(
// 						   0u, 0u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

//   hdf5_file_handler.getRawEstimatorEntityBinData<EntityId>(
// 						   0u, 1u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

//   // Retrieve the processed bin data for each entity
//   std::vector<Utility::Pair<double,double> >
//     processed_bin_data( 16, Utility::Pair<double,double>( 10.0, 0.0 ) ),
//     processed_bin_data_copy;

//   hdf5_file_handler.getProcessedEstimatorEntityBinData<EntityId>(
// 					     0u, 0u, processed_bin_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( processed_bin_data, processed_bin_data_copy );

//   processed_bin_data.clear();
//   processed_bin_data.resize( 16, Utility::Pair<double,double>( 5.0, 0.0 ) );

//   hdf5_file_handler.getProcessedEstimatorEntityBinData<EntityId>(
// 					     0u, 1u, processed_bin_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( processed_bin_data, processed_bin_data_copy );

//   // Retrieve the raw total bin data
//   std::vector<Utility::Pair<double,double> >
//     raw_total_bin_data( 16, Utility::Pair<double,double>( 2.0, 4.0 ) ),
//     raw_total_bin_data_copy;

//   hdf5_file_handler.getRawEstimatorTotalBinData( 0u, raw_total_bin_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_total_bin_data, raw_total_bin_data_copy );

//   // Retrieve the processed total bin data
//   std::vector<Utility::Pair<double,double> >
//     processed_total_bin_data( 16, Utility::Pair<double,double>( 20.0/3, 0.0 )),
//     processed_total_bin_data_copy;

//   hdf5_file_handler.getProcessedEstimatorTotalBinData(
// 					   0u, processed_total_bin_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( processed_total_bin_data,
// 			       processed_total_bin_data_copy );

//   // Retrieve the raw estimator total data for each entity
//   Utility::Quad<double,double,double,double>
//     raw_moments( 16.0, 256.0, 4096.0, 65536.0 );

//   std::vector<Utility::Quad<double,double,double,double> >
//     raw_total_data( 1, raw_moments ),
//     raw_total_data_copy;

//   hdf5_file_handler.getRawEstimatorEntityTotalData<EntityId>(
// 						 0u, 0u, raw_total_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_total_data, raw_total_data_copy );

//   hdf5_file_handler.getRawEstimatorEntityTotalData<EntityId>(
// 						 0u, 1u, raw_total_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_total_data, raw_total_data_copy );

//   // Retrieve the processed estimator total data for each entity
//   Utility::Quad<double,double,double,double>
//     processed_moments( 160.0, 0.0, 0.0, 0.0 );

//   std::vector<Utility::Quad<double,double,double,double> >
//     processed_total_data( 1, processed_moments ),
//     processed_total_data_copy;

//   hdf5_file_handler.getProcessedEstimatorEntityTotalData<EntityId>(
// 					   0u, 0u, processed_total_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( processed_total_data,
// 			       processed_total_data_copy );

//   processed_total_data[0]( 80.0, 0.0, 0.0, 0.0 );

//   hdf5_file_handler.getProcessedEstimatorEntityTotalData<EntityId>(
// 					   0u, 1u, processed_total_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( processed_total_data,
// 			       processed_total_data_copy );

//   // Retrieve the raw total data
//   raw_total_data[0]( 32.0, 1024.0, 32768.0, 1048576.0 );

//   hdf5_file_handler.getRawEstimatorTotalData( 0u, raw_total_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_total_data, raw_total_data_copy );

//   // Retrieve the processed total data
//   processed_total_data[0]( 320.0/3, 0.0, 0.0, 0.0 );

//   hdf5_file_handler.getProcessedEstimatorTotalData(
// 					       0u, processed_total_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( processed_total_data,
// 			       processed_total_data_copy );
// }

// UNIT_TEST_INSTANTIATION( StandardEntityEstimator,
// 			 addPartialHistoryContribution );

// //---------------------------------------------------------------------------//
// // Check that a partial history contribution can be added to the estimator
// // in a thread safe way
// TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( StandardEntityEstimator,
// 				   addPartialHistoryContribution_thread_safe,
// 				   EntityId )
// {
//   Teuchos::RCP<MonteCarlo::Estimator> estimator_base;
//   Teuchos::RCP<TestStandardEntityEstimator<EntityId> > estimator;

//   {
//     // Set the entity ids
//     std::vector<uint64_t> entity_ids( 2 );
//     entity_ids[0] = 0;
//     entity_ids[1] = 1;

//     // Set the entity norm constants
//     std::vector<double> entity_norm_consts( 2 );
//     entity_norm_consts[0] = 1.0;
//     entity_norm_consts[1] = 2.0;

//     estimator.reset(
// 	     new TestStandardEntityEstimator<EntityId>( 0u,
// 							10.0,
// 							entity_ids,
// 							entity_norm_consts ) );

//     estimator_base = estimator;

//     // Set the energy bins
//     std::vector<double> energy_bin_boundaries( 3 );
//     energy_bin_boundaries[0] = 0.0;
//     energy_bin_boundaries[1] = 0.1;
//     energy_bin_boundaries[2] = 1.0;

//     estimator_base->setDiscretization<MonteCarlo::ENERGY_DIMENSION>(
// 						       energy_bin_boundaries );

//     // Set the cosine bins
//     std::vector<double> cosine_bin_boundaries( 3 );
//     cosine_bin_boundaries[0] = -1.0;
//     cosine_bin_boundaries[1] = 0.0;
//     cosine_bin_boundaries[2] = 1.0;

//     estimator_base->setDiscretization<MonteCarlo::COSINE_DIMENSION>(
// 						       cosine_bin_boundaries );

//     // Set the time bins
//     std::vector<double> time_bin_boundaries( 3 );
//     time_bin_boundaries[0] = 0.0;
//     time_bin_boundaries[1] = 1.0;
//     time_bin_boundaries[2] = 2.0;

//     estimator_base->setDiscretization<MonteCarlo::TIME_DIMENSION>(
// 							 time_bin_boundaries );

//     // Set collision number bins
//     std::vector<unsigned> collision_number_bins( 2 );
//     collision_number_bins[0] = 0u;
//     collision_number_bins[1] = 1u;

//     estimator_base->setDiscretization<MonteCarlo::COLLISION_NUMBER_DIMENSION>(
// 						       collision_number_bins );

//     // Set the particle types
//     std::vector<MonteCarlo::ParticleType> particle_types( 1 );
//     particle_types[0] = MonteCarlo::PHOTON;

//     estimator_base->setParticleTypes( particle_types );

//     // Enable thread support
//     estimator_base->enableThreadSupport(
// 	         Utility::OpenMPProperties::getRequestedNumberOfThreads() );
//   }

//   unsigned threads =
//     Utility::OpenMPProperties::getRequestedNumberOfThreads();

//   for( unsigned i = 0; i < threads; ++i )
//     TEST_ASSERT( !estimator_base->hasUncommittedHistoryContribution( i ) );

//   #pragma omp parallel num_threads( threads )
//   {
//     // bin 0
//     MonteCarlo::PhotonState particle( 0ull );
//     particle.setEnergy( 1.0 );
//     particle.setTime( 2.0 );

//     MonteCarlo::EstimatorParticleStateWrapper particle_wrapper( particle );
//     particle_wrapper.setAngleCosine( 1.0 );

//     estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//     estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//     // bin 1
//     particle.setEnergy( 0.1 );

//     estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//     estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//     // bin 2
//     particle.setEnergy( 1.0 );

//     particle_wrapper.setAngleCosine( 0.0 );

//     estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//     estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//     // bin 3
//     particle.setEnergy( 0.1 );

//     estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//     estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//     // bin 4
//     particle.setTime( 1.0 );
//     particle.setEnergy( 1.0 );

//     particle_wrapper.setAngleCosine( 1.0 );

//     estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//     estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//     // bin 5
//     particle.setEnergy( 0.1 );

//     estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//     estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//     // bin 6
//     particle.setEnergy( 1.0 );

//     particle_wrapper.setAngleCosine( 0.0 );

//     estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//     estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//     // bin 7
//     particle.setEnergy( 0.1 );

//     estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//     estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//     // bin 8
//     particle.incrementCollisionNumber();
//     particle.setTime( 2.0 );
//     particle.setEnergy( 1.0 );

//     particle_wrapper.setAngleCosine( 1.0 );

//     estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//     estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//     // bin 9
//     particle.setEnergy( 0.1 );

//     estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//     estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//     // bin 10
//     particle.setEnergy( 1.0 );

//     particle_wrapper.setAngleCosine( 0.0 );

//     estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//     estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//     // bin 11
//     particle.setEnergy( 0.1 );

//     estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//     estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//     // bin 12
//     particle.setTime( 1.0 );
//     particle.setEnergy( 1.0 );

//     particle_wrapper.setAngleCosine( 1.0 );

//     estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//     estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//     // bin 13
//     particle.setEnergy( 0.1 );

//     estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//     estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//     // bin 14
//     particle.setEnergy( 1.0 );

//     particle_wrapper.setAngleCosine( 0.0 );

//     estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//     estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//     // bin 15
//     particle.setEnergy( 0.1 );

//     estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//     estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//     // Commit the contributions
//     estimator_base->commitHistoryContribution();
//   }

//   for( unsigned i = 0; i < threads; ++i )
//     TEST_ASSERT( !estimator_base->hasUncommittedHistoryContribution( i ) );

//   MonteCarlo::ParticleHistoryObserver::setNumberOfHistories( threads );
//   MonteCarlo::ParticleHistoryObserver::setEndTime( 1.0 );

//   // Initialize the HDF5 file
//   std::shared_ptr<Utility::HDF5FileHandler>
//     hdf5_file( new Utility::HDF5FileHandler );
//   hdf5_file->openHDF5FileAndOverwrite( "test_standard_entity_estimator2.h5" );

//   estimator_base->exportData( hdf5_file, true );

//   // Create an estimator hdf5 file handler
//   MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( hdf5_file );

//   // Retrieve the raw bin data for each entity
//   std::vector<Utility::Pair<double,double> >
//     raw_bin_data( 16, Utility::Pair<double,double>( threads, threads ) ),
//     raw_bin_data_copy;

//   hdf5_file_handler.getRawEstimatorEntityBinData<EntityId>(
// 						   0u, 0u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

//   hdf5_file_handler.getRawEstimatorEntityBinData<EntityId>(
// 						   0u, 1u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

//   // Retrieve the processed bin data for each entity
//   std::vector<Utility::Pair<double,double> >
//     processed_bin_data( 16, Utility::Pair<double,double>( 10.0, 0.0 ) ),
//     processed_bin_data_copy;

//   hdf5_file_handler.getProcessedEstimatorEntityBinData<EntityId>(
// 					     0u, 0u, processed_bin_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( processed_bin_data, processed_bin_data_copy );

//   processed_bin_data.clear();
//   processed_bin_data.resize( 16, Utility::Pair<double,double>( 5.0, 0.0 ) );

//   hdf5_file_handler.getProcessedEstimatorEntityBinData<EntityId>(
// 					     0u, 1u, processed_bin_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( processed_bin_data, processed_bin_data_copy );

//   // Retrieve the raw total bin data
//   std::vector<Utility::Pair<double,double> >
//     raw_total_bin_data( 16,
// 			Utility::Pair<double,double>(2.0*threads,4.0*threads)),
//     raw_total_bin_data_copy;

//   hdf5_file_handler.getRawEstimatorTotalBinData( 0u, raw_total_bin_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_total_bin_data, raw_total_bin_data_copy );

//   // Retrieve the processed total bin data
//   std::vector<Utility::Pair<double,double> >
//     processed_total_bin_data( 16, Utility::Pair<double,double>( 20.0/3, 0.0 )),
//     processed_total_bin_data_copy;

//   hdf5_file_handler.getProcessedEstimatorTotalBinData(
// 					   0u, processed_total_bin_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( processed_total_bin_data,
// 			       processed_total_bin_data_copy );

//   // Retrieve the raw estimator total data for each entity
//   Utility::Quad<double,double,double,double>
//     raw_moments( 16.0*threads, 256.0*threads, 4096.0*threads, 65536.0*threads);

//   std::vector<Utility::Quad<double,double,double,double> >
//     raw_total_data( 1, raw_moments ),
//     raw_total_data_copy;

//   hdf5_file_handler.getRawEstimatorEntityTotalData<EntityId>(
// 						 0u, 0u, raw_total_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_total_data, raw_total_data_copy );

//   hdf5_file_handler.getRawEstimatorEntityTotalData<EntityId>(
// 						 0u, 1u, raw_total_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_total_data, raw_total_data_copy );

//   // Retrieve the processed estimator total data for each entity
//   Utility::Quad<double,double,double,double>
//     processed_moments( 160.0, 0.0, 0.0, 0.0 );

//   std::vector<Utility::Quad<double,double,double,double> >
//     processed_total_data( 1, processed_moments ),
//     processed_total_data_copy;

//   hdf5_file_handler.getProcessedEstimatorEntityTotalData<EntityId>(
// 					   0u, 0u, processed_total_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( processed_total_data,
// 			       processed_total_data_copy );

//   processed_total_data[0]( 80.0, 0.0, 0.0, 0.0 );

//   hdf5_file_handler.getProcessedEstimatorEntityTotalData<EntityId>(
// 					   0u, 1u, processed_total_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( processed_total_data,
// 			       processed_total_data_copy );

//   // Retrieve the raw total data
//   raw_total_data[0]( 32.0*threads,
// 		     1024.0*threads,
// 		     32768.0*threads,
// 		     1048576.0*threads );

//   hdf5_file_handler.getRawEstimatorTotalData( 0u, raw_total_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( raw_total_data, raw_total_data_copy );

//   // Retrieve the processed total data
//   processed_total_data[0]( 320.0/3, 0.0, 0.0, 0.0 );

//   hdf5_file_handler.getProcessedEstimatorTotalData(
// 					       0u, processed_total_data_copy );

//   UTILITY_TEST_COMPARE_ARRAYS( processed_total_data,
// 			       processed_total_data_copy );
// }

// UNIT_TEST_INSTANTIATION( StandardEntityEstimator,
// 			 addPartialHistoryContribution_thread_safe );

// //---------------------------------------------------------------------------//
// // Check that a partial history contribution can be added to the estimator
// TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( StandardEntityEstimator,
//                                    resetData,
// 				   EntityId )
// {
//   Teuchos::RCP<MonteCarlo::Estimator> estimator_base;
//   Teuchos::RCP<TestStandardEntityEstimator<EntityId> > estimator;

//   {
//     // Set the entity ids
//     std::vector<uint64_t> entity_ids( 2 );
//     entity_ids[0] = 0;
//     entity_ids[1] = 1;

//     // Set the entity norm constants
//     std::vector<double> entity_norm_consts( 2 );
//     entity_norm_consts[0] = 1.0;
//     entity_norm_consts[1] = 2.0;

//     estimator.reset(
// 	     new TestStandardEntityEstimator<EntityId>( 0u,
// 							10.0,
// 							entity_ids,
// 							entity_norm_consts ) );

//     estimator_base = estimator;

//     // Set the energy bins
//     std::vector<double> energy_bin_boundaries( 3 );
//     energy_bin_boundaries[0] = 0.0;
//     energy_bin_boundaries[1] = 0.1;
//     energy_bin_boundaries[2] = 1.0;

//     estimator_base->setDiscretization<MonteCarlo::ENERGY_DIMENSION>(
// 						       energy_bin_boundaries );

//     // Set the cosine bins
//     std::vector<double> cosine_bin_boundaries( 3 );
//     cosine_bin_boundaries[0] = -1.0;
//     cosine_bin_boundaries[1] = 0.0;
//     cosine_bin_boundaries[2] = 1.0;

//     estimator_base->setDiscretization<MonteCarlo::COSINE_DIMENSION>(
// 						       cosine_bin_boundaries );

//     // Set the time bins
//     std::vector<double> time_bin_boundaries( 3 );
//     time_bin_boundaries[0] = 0.0;
//     time_bin_boundaries[1] = 1.0;
//     time_bin_boundaries[2] = 2.0;

//     estimator_base->setDiscretization<MonteCarlo::TIME_DIMENSION>(
// 							 time_bin_boundaries );

//     // Set collision number bins
//     std::vector<unsigned> collision_number_bins( 2 );
//     collision_number_bins[0] = 0u;
//     collision_number_bins[1] = 1u;

//     estimator_base->setDiscretization<MonteCarlo::COLLISION_NUMBER_DIMENSION>(
// 						       collision_number_bins );

//     // Set the particle types
//     std::vector<MonteCarlo::ParticleType> particle_types( 1 );
//     particle_types[0] = MonteCarlo::PHOTON;

//     estimator_base->setParticleTypes( particle_types );
//   }

//   TEST_ASSERT( !estimator_base->hasUncommittedHistoryContribution() );

//   // bin 0
//   MonteCarlo::PhotonState particle( 0ull );
//   particle.setEnergy( 1.0 );
//   particle.setTime( 2.0 );

//   MonteCarlo::EstimatorParticleStateWrapper particle_wrapper( particle );
//   particle_wrapper.setAngleCosine( 1.0 );

//   estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//   estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//   TEST_ASSERT( estimator_base->hasUncommittedHistoryContribution() );

//   // bin 1
//   particle.setEnergy( 0.1 );

//   estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//   estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//   // bin 2
//   particle.setEnergy( 1.0 );

//   particle_wrapper.setAngleCosine( 0.0 );

//   estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//   estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//   // bin 3
//   particle.setEnergy( 0.1 );

//   estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//   estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//   // bin 4
//   particle.setTime( 1.0 );
//   particle.setEnergy( 1.0 );

//   particle_wrapper.setAngleCosine( 1.0 );

//   estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//   estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//   // bin 5
//   particle.setEnergy( 0.1 );

//   estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//   estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//   // bin 6
//   particle.setEnergy( 1.0 );

//   particle_wrapper.setAngleCosine( 0.0 );

//   estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//   estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//   // bin 7
//   particle.setEnergy( 0.1 );

//   estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//   estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//   // bin 8
//   particle.incrementCollisionNumber();
//   particle.setTime( 2.0 );
//   particle.setEnergy( 1.0 );

//   particle_wrapper.setAngleCosine( 1.0 );

//   estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//   estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//   // bin 9
//   particle.setEnergy( 0.1 );

//   estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//   estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//   // bin 10
//   particle.setEnergy( 1.0 );

//   particle_wrapper.setAngleCosine( 0.0 );

//   estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//   estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//   // bin 11
//   particle.setEnergy( 0.1 );

//   estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//   estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//   // bin 12
//   particle.setTime( 1.0 );
//   particle.setEnergy( 1.0 );

//   particle_wrapper.setAngleCosine( 1.0 );

//   estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//   estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//   // bin 13
//   particle.setEnergy( 0.1 );

//   estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//   estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//   // bin 14
//   particle.setEnergy( 1.0 );

//   particle_wrapper.setAngleCosine( 0.0 );

//   estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//   estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//   // bin 15
//   particle.setEnergy( 0.1 );

//   estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//   estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//   // Commit the contributions
//   estimator_base->commitHistoryContribution();

//   TEST_ASSERT( !estimator_base->hasUncommittedHistoryContribution() );

//   // Start a new history
//   particle.setEnergy( 1.0 );
//   particle.setTime( 2.0 );

//   particle_wrapper.setAngleCosine( 1.0 );

//   estimator->addPartialHistoryContribution( 0, particle_wrapper, 1.0 );
//   estimator->addPartialHistoryContribution( 1, particle_wrapper, 1.0 );

//   TEST_ASSERT( estimator_base->hasUncommittedHistoryContribution() );

//   // Reset the estimator data
//   estimator_base->resetData();

//   // Make sure all partial contributions have been deleted
//   TEST_ASSERT( !estimator_base->hasUncommittedHistoryContribution() );

//   // Make sure the bins have not been changed
//   FRENSIE_CHECK_EQUAL(
// 	     estimator_base->getNumberOfBins( MonteCarlo::ENERGY_DIMENSION ),
// 	     2 );
//   FRENSIE_CHECK_EQUAL(
// 	     estimator_base->getNumberOfBins( MonteCarlo::TIME_DIMENSION ),
// 	     2 );
//   FRENSIE_CHECK_EQUAL(
// 	     estimator_base->getNumberOfBins( MonteCarlo::COSINE_DIMENSION ),
// 	     2 );
//   FRENSIE_CHECK_EQUAL(
//    estimator_base->getNumberOfBins( MonteCarlo::COLLISION_NUMBER_DIMENSION ),
//    2 );
//   FRENSIE_CHECK_EQUAL( estimator_base->getNumberOfBins(), 16 );

//   // Make sure the response functions have not changed
//   FRENSIE_CHECK_EQUAL( estimator_base->getNumberOfResponseFunctions(), 1 );

//   // Initialize the HDF5 file
//   std::shared_ptr<Utility::HDF5FileHandler>
//     hdf5_file( new Utility::HDF5FileHandler );
//   hdf5_file->openHDF5FileAndOverwrite( "test_standard_entity_estimator3.h5" );

//   estimator_base->exportData( hdf5_file, false );

//   // Create and estimator hdf5 file handler
//   MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( hdf5_file );

//   // Retrieve the raw bin data for each entity
//   std::vector<Utility::Pair<double,double> >
//     raw_bin_data( 16, Utility::Pair<double,double>( 0.0, 0.0 ) ),
//     raw_bin_data_copy;

//   hdf5_file_handler.getRawEstimatorEntityBinData<EntityId>(
//                                                    0u, 0u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<EntityId>(
//                                                    0u, 1u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
// 					raw_bin_data_copy,
// 					1e-15 );

//   // Retrieve the total raw total bin data
//   hdf5_file_handler.getRawEstimatorTotalBinData( 0u, raw_bin_data );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
// 					raw_bin_data_copy,
// 					1e-15 );

//   // Retrieve the raw total entity data
//   std::vector<Utility::Quad<double,double,double,double> >
//     raw_total_data( 1, Utility::Quad<double,double,double,double>(0, 0, 0, 0)),
//     raw_total_data_copy;

//   hdf5_file_handler.getRawEstimatorEntityTotalData<EntityId>(
//                                                  0u, 0u, raw_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
// 					raw_total_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityTotalData<EntityId>(
//                                                  0u, 1u, raw_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
// 					raw_total_data_copy,
// 					1e-15 );

//   // Retrieve the raw total data
//   hdf5_file_handler.getRawEstimatorTotalData( 0u, raw_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
// 					raw_total_data_copy,
// 					1e-15 );
// }

// UNIT_TEST_INSTANTIATION( StandardEntityEstimator, resetData );

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

int threads;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "threads",
                                        threads, 1,
                                        "Number of threads to use" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Set up the global OpenMP session
  if( Utility::OpenMPProperties::isOpenMPUsed() )
    Utility::OpenMPProperties::setNumberOfThreads( threads );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstStandardEntityEstimator.cpp
//---------------------------------------------------------------------------//


