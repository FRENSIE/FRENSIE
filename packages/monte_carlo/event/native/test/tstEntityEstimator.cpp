//---------------------------------------------------------------------------//
//!
//! \file   tstEntityEstimator.cpp
//! \author Alex Robinson
//! \brief  Entity estimator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_EntityEstimator.hpp"
#include "MonteCarlo_EstimatorHDF5FileHandler.hpp"
#include "Geometry_ModuleTraits.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
typedef Geometry::ModuleTraits::InternalCellHandle CellId;

#define UNIT_TEST_INSTANTIATION( type, name )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, CellId ) \

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
template<typename EntityId>
class TestEntityEstimator : public MonteCarlo::EntityEstimator<EntityId>
{  
public:
  TestEntityEstimator( const unsigned long long id,
		       const double multiplier,
		       const Teuchos::Array<EntityId>& entity_ids,
		       const Teuchos::Array<double>& entity_norm_constants )
    : MonteCarlo::EntityEstimator<EntityId>( id, 
					 multiplier, 
					 entity_ids, 
					 entity_norm_constants )
  { /* ... */ }

  TestEntityEstimator( const unsigned long long id,
		       const double multiplier,
		       const Teuchos::Array<EntityId>& entity_ids )
    : MonteCarlo::EntityEstimator<EntityId>( id, multiplier, entity_ids )
  { /* ... */ }

  ~TestEntityEstimator()
  { /* ... */ }
  
  void printSummary( std::ostream& os ) const
  { this->printImplementation( os, "Surface" ); }

  void commitHistoryContribution()
  { /* ... */ }

  // Allow public access to the entity estimator protected member functions
  using MonteCarlo::EntityEstimator<EntityId>::getEntityNormConstant;
  using MonteCarlo::EntityEstimator<EntityId>::getTotalNormConstant;
  using MonteCarlo::EntityEstimator<EntityId>::commitHistoryContributionToBinOfEntity;
  using MonteCarlo::EntityEstimator<EntityId>::commitHistoryContributionToBinOfTotal;
};

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Set the entity estimator bins (and response functions)
template<typename EntityId>
void setEntityEstimatorBins( 
	       Teuchos::RCP<TestEntityEstimator<EntityId> >& entity_estimator )
{
  // Use a base class pointer to test the virtual functions
  Teuchos::RCP<MonteCarlo::Estimator> base_estimator =
    Teuchos::rcp_dynamic_cast<MonteCarlo::Estimator>( entity_estimator );
  
  // Set the energy bins
  Teuchos::Array<double> energy_bin_boundaries( 3 );
  energy_bin_boundaries[0] = 0.0;
  energy_bin_boundaries[1] = 1e-1;
  energy_bin_boundaries[2] = 1.0;

  base_estimator->setBinBoundaries<MonteCarlo::ENERGY_DIMENSION>( 
						       energy_bin_boundaries );

  // Set the cosine bins
  Teuchos::Array<double> cosine_bin_boundaries( 3 );
  cosine_bin_boundaries[0] = -1.0;
  cosine_bin_boundaries[1] = 0.0;
  cosine_bin_boundaries[2] = 1.0;

  base_estimator->setBinBoundaries<MonteCarlo::COSINE_DIMENSION>( 
						       cosine_bin_boundaries );

  // Set the time bins
  Teuchos::Array<double> time_bin_boundaries( 3 );
  time_bin_boundaries[0] = 0.0;
  time_bin_boundaries[1] = 1e3;
  time_bin_boundaries[2] = 1e5;

  base_estimator->setBinBoundaries<MonteCarlo::TIME_DIMENSION>( 
							 time_bin_boundaries );

  // Set the collision number bins
  Teuchos::Array<unsigned> collision_number_bins( 3 );
  collision_number_bins[0] = 0u;
  collision_number_bins[1] = 1u;
  collision_number_bins[2] = std::numeric_limits<unsigned>::max();

  base_estimator->setBinBoundaries<MonteCarlo::COLLISION_NUMBER_DIMENSION>( 
						       collision_number_bins );

  // Set the response functions
  Teuchos::Array<std::shared_ptr<MonteCarlo::ResponseFunction> > 
    response_functions( 1 );
  response_functions[0] = MonteCarlo::ResponseFunction::default_response_function;

  base_estimator->setResponseFunctions( response_functions );
}

// Initialize the entity estimator (general)
template<typename EntityId>
void initializeEntityEstimator( 
		Teuchos::RCP<TestEntityEstimator<EntityId> >& entity_estimator,
		const bool assign_entity_norm_consts )
{ /* ... */ }

// Initialize the entity estimator (int)
template<>
void 
initializeEntityEstimator<Geometry::ModuleTraits::InternalCellHandle>( 
                     Teuchos::RCP<TestEntityEstimator<Geometry::ModuleTraits::InternalCellHandle> >& entity_estimator,
		     const bool assign_entity_norm_consts )
{  
  // Set the entity ids
  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> 
    entity_ids( 5 );
  entity_ids[0] = 0;
  entity_ids[1] = 1;
  entity_ids[2] = 2;
  entity_ids[3] = 3;
  entity_ids[4] = 4;
  
  // Set the entity normalization constants
  Teuchos::Array<double> entity_norm_constants( 5 );
  entity_norm_constants[0] = 1.0;
  entity_norm_constants[1] = 2.0;
  entity_norm_constants[2] = 3.0;
  entity_norm_constants[3] = 4.0;
  entity_norm_constants[4] = 5.0;

  // Set the estimator multiplier
  double estimator_multiplier = 10.0;

  if( assign_entity_norm_consts )
  {
    entity_estimator.reset( 
     new TestEntityEstimator<Geometry::ModuleTraits::InternalCellHandle>(
						     0ull,
						     estimator_multiplier,
						     entity_ids,
						     entity_norm_constants ) );
  }
  else
  {
    entity_estimator.reset( 
     new TestEntityEstimator<Geometry::ModuleTraits::InternalCellHandle>(
							  0ull,
							  estimator_multiplier,
							  entity_ids ) );
  }

  // Set the entity estimator bins (and response functions)
  setEntityEstimatorBins<Geometry::ModuleTraits::InternalCellHandle>( 
							    entity_estimator );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the number of bins can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( EntityEstimator,
				   getNumberOfBins,
				   EntityId )
{
  Teuchos::RCP<TestEntityEstimator<EntityId> > entity_estimator;
  initializeEntityEstimator( entity_estimator, true );

  TEST_EQUALITY_CONST( entity_estimator->getNumberOfBins(), 24 );
  
  initializeEntityEstimator( entity_estimator, false );

  TEST_EQUALITY_CONST( entity_estimator->getNumberOfBins(), 24 );
}

UNIT_TEST_INSTANTIATION( EntityEstimator, getNumberOfBins );

//---------------------------------------------------------------------------//
// Check that the number of response functions can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( EntityEstimator,
				   getNumberOfResponseFunctions,
				   EntityId )
{
  Teuchos::RCP<TestEntityEstimator<EntityId> > entity_estimator;
  
  initializeEntityEstimator( entity_estimator, true );

  TEST_EQUALITY_CONST( entity_estimator->getNumberOfResponseFunctions(), 1 );

  initializeEntityEstimator( entity_estimator, false );

  TEST_EQUALITY_CONST( entity_estimator->getNumberOfResponseFunctions(), 1 );
}

UNIT_TEST_INSTANTIATION( EntityEstimator, getNumberOfResponseFunctions );

//---------------------------------------------------------------------------//
// Check that the entity ids associated with the estimator can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( EntityEstimator,
				   getEntityIds,
				   EntityId )
{
  Teuchos::RCP<TestEntityEstimator<EntityId> > entity_estimator;
  typename MonteCarlo::EntityEstimator<EntityId>::EntityIdSet entity_ids;

  initializeEntityEstimator( entity_estimator, true );

  entity_estimator->getEntityIds( entity_ids );

  TEST_EQUALITY_CONST( entity_ids.size(), 5 );
}

UNIT_TEST_INSTANTIATION( EntityEstimator, getEntityIds );

//---------------------------------------------------------------------------//
// Check if an entity is assigned to the estimator
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( EntityEstimator,
				   isEntityAssigned,
				   EntityId )
{
  Teuchos::RCP<TestEntityEstimator<EntityId> > entity_estimator;

  initializeEntityEstimator( entity_estimator, true );

  TEST_ASSERT( entity_estimator->isEntityAssigned( 0 ) );
  TEST_ASSERT( entity_estimator->isEntityAssigned( 1 ) );
  TEST_ASSERT( entity_estimator->isEntityAssigned( 2 ) );
  TEST_ASSERT( entity_estimator->isEntityAssigned( 3 ) );
  TEST_ASSERT( entity_estimator->isEntityAssigned( 4 ) );
  TEST_ASSERT( !entity_estimator->isEntityAssigned( 5 ) );
}

UNIT_TEST_INSTANTIATION( EntityEstimator, isEntityAssigned );

//---------------------------------------------------------------------------//
// Check if the entity norm constant can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( EntityEstimator,
				   getEntityNormConstant,
				   EntityId )
{
  Teuchos::RCP<TestEntityEstimator<EntityId> > entity_estimator;

  initializeEntityEstimator( entity_estimator, true );

  TEST_EQUALITY_CONST( entity_estimator->getEntityNormConstant( 0 ), 1.0 );
  TEST_EQUALITY_CONST( entity_estimator->getEntityNormConstant( 1 ), 2.0 );
  TEST_EQUALITY_CONST( entity_estimator->getEntityNormConstant( 2 ), 3.0 );
  TEST_EQUALITY_CONST( entity_estimator->getEntityNormConstant( 3 ), 4.0 );
  TEST_EQUALITY_CONST( entity_estimator->getEntityNormConstant( 4 ), 5.0 );

  initializeEntityEstimator( entity_estimator, false );

  TEST_EQUALITY_CONST( entity_estimator->getEntityNormConstant( 0 ), 1.0 );
  TEST_EQUALITY_CONST( entity_estimator->getEntityNormConstant( 1 ), 1.0 );
  TEST_EQUALITY_CONST( entity_estimator->getEntityNormConstant( 2 ), 1.0 );
  TEST_EQUALITY_CONST( entity_estimator->getEntityNormConstant( 3 ), 1.0 );
  TEST_EQUALITY_CONST( entity_estimator->getEntityNormConstant( 4 ), 1.0 );
}

UNIT_TEST_INSTANTIATION( EntityEstimator, getEntityNormConstant );

//---------------------------------------------------------------------------//
// Check if the total norm constant can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( EntityEstimator,
				   getTotalNormConstant,
				   EntityId )
{
  Teuchos::RCP<TestEntityEstimator<EntityId> > entity_estimator;

  initializeEntityEstimator( entity_estimator, true );

  TEST_EQUALITY_CONST( entity_estimator->getTotalNormConstant(), 15.0 );
  
  initializeEntityEstimator( entity_estimator, false );

  TEST_EQUALITY_CONST( entity_estimator->getTotalNormConstant(), 1.0 );
}

UNIT_TEST_INSTANTIATION( EntityEstimator, getTotalNormConstant );

//---------------------------------------------------------------------------//
// Check if the estimator data can be exported
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( EntityEstimator,
				   exportData_raw,
				   EntityId )
{
  Teuchos::RCP<MonteCarlo::Estimator> estimator;

  Teuchos::Array<EntityId> entity_ids;
  Teuchos::Array<double> entity_norm_constants;

  {
    // Set the entities ids
    entity_ids.resize( 5 );
    entity_ids[0] = 0;
    entity_ids[1] = 1;
    entity_ids[2] = 2;
    entity_ids[3] = 3;
    entity_ids[4] = 4;
    
    // Set the entity normalization constants
    entity_norm_constants.resize( 5 );
    entity_norm_constants[0] = 1.0;
    entity_norm_constants[1] = 2.0;
    entity_norm_constants[2] = 3.0;
    entity_norm_constants[3] = 4.0;
    entity_norm_constants[4] = 5.0;
  }

  estimator.reset( new TestEntityEstimator<EntityId>(0u,
						     5.0,
						     entity_ids,
						     entity_norm_constants ) );

  Teuchos::Array<double> energy_bin_boundaries, cosine_bin_boundaries,
    time_bin_boundaries;
  Teuchos::Array<unsigned> collision_number_bins;
  
  {
    // Set the energy bins
    energy_bin_boundaries.resize( 3 );
    energy_bin_boundaries[0] = 0.0;
    energy_bin_boundaries[1] = 1e-1;
    energy_bin_boundaries[2] = 1.0;

    estimator->setBinBoundaries<MonteCarlo::ENERGY_DIMENSION>( 
						       energy_bin_boundaries );

    // Set the cosine bins
    cosine_bin_boundaries.resize( 3 );
    cosine_bin_boundaries[0] = -1.0;
    cosine_bin_boundaries[1] = 0.0;
    cosine_bin_boundaries[2] = 1.0;

    estimator->setBinBoundaries<MonteCarlo::COSINE_DIMENSION>( 
						       cosine_bin_boundaries );

    // Set the time bins
    time_bin_boundaries.resize( 3 );
    time_bin_boundaries[0] = 0.0;
    time_bin_boundaries[1] = 1e3;
    time_bin_boundaries[2] = 1e5;

    estimator->setBinBoundaries<MonteCarlo::TIME_DIMENSION>( 
							 time_bin_boundaries );

    // Set the collision number bins
    collision_number_bins.resize( 3 );
    collision_number_bins[0] = 0u;
    collision_number_bins[1] = 1u;
    collision_number_bins[2] = std::numeric_limits<unsigned>::max();

    estimator->setBinBoundaries<MonteCarlo::COLLISION_NUMBER_DIMENSION>( 
						       collision_number_bins );

    // Set the response functions
    Teuchos::Array<std::shared_ptr<MonteCarlo::ResponseFunction> > 
      response_functions( 1 );
    response_functions[0] = 
      MonteCarlo::ResponseFunction::default_response_function;

    estimator->setResponseFunctions( response_functions );
  }

  // Initialize the hdf5 file
  std::shared_ptr<Utility::HDF5FileHandler>
    hdf5_file( new Utility::HDF5FileHandler );
  hdf5_file->openHDF5FileAndOverwrite( "test_entity_estimator.h5" );

  estimator->exportData( hdf5_file, false );

  // Create an estimator hdf5 file handler
  MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( hdf5_file );

  // Make sure that the estimator exists in the hdf5 file
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 0u ) );

  // Check that the estimator multiplier has been set
  double multiplier;
  hdf5_file_handler.getEstimatorMultiplier( 0u, multiplier );

  TEST_EQUALITY_CONST( multiplier, 5.0 );

  // Check that the estimator response function ordering has been set
  Teuchos::Array<unsigned> response_function_ordering;
  hdf5_file_handler.getEstimatorResponseFunctionOrdering( 
						  0u,
						  response_function_ordering );
  
  TEST_EQUALITY_CONST( response_function_ordering.size(), 1 );
  TEST_EQUALITY( response_function_ordering[0], 
		 std::numeric_limits<unsigned>::max() );
  
  // Check that the estimator dimension ordering has been set
  Teuchos::Array<MonteCarlo::PhaseSpaceDimension> dimension_ordering;
  hdf5_file_handler.getEstimatorDimensionOrdering( 0u, dimension_ordering );
  
  TEST_EQUALITY_CONST( dimension_ordering.size(), 4 );
  TEST_EQUALITY_CONST( dimension_ordering[0], MonteCarlo::ENERGY_DIMENSION );
  TEST_EQUALITY_CONST( dimension_ordering[1], MonteCarlo::COSINE_DIMENSION );
  TEST_EQUALITY_CONST( dimension_ordering[2], MonteCarlo::TIME_DIMENSION );
  TEST_EQUALITY_CONST( dimension_ordering[3], 
		       MonteCarlo::COLLISION_NUMBER_DIMENSION );

  // Check that the energy bins have been set
  Teuchos::Array<double> energy_bin_boundaries_copy;
  hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::ENERGY_DIMENSION>( 
						  0u,
						  energy_bin_boundaries_copy );

  TEST_COMPARE_ARRAYS( energy_bin_boundaries, energy_bin_boundaries_copy );

  // Check that the cosine bins have been set
  Teuchos::Array<double> cosine_bin_boundaries_copy;
  hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::COSINE_DIMENSION>( 
						  0u, 
						  cosine_bin_boundaries_copy );

  TEST_COMPARE_ARRAYS( cosine_bin_boundaries, cosine_bin_boundaries_copy );

  // Check that the time bins have been set
  Teuchos::Array<double> time_bin_boundaries_copy;
  hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::TIME_DIMENSION>(
						    0u,
						    time_bin_boundaries_copy );

  TEST_COMPARE_ARRAYS( time_bin_boundaries, time_bin_boundaries_copy );

  // Check that the collision number bins have been set
  Teuchos::Array<unsigned> collision_number_bins_copy;
  hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::COLLISION_NUMBER_DIMENSION>(
						  0u,
						  collision_number_bins_copy );

  TEST_COMPARE_ARRAYS( collision_number_bins, collision_number_bins_copy );

  // Check if entities are assigned to the estimator
  TEST_ASSERT( hdf5_file_handler.isEntityAssignedToEstimator<EntityId>(
								    0u, 0u ) );
  TEST_ASSERT( hdf5_file_handler.isEntityAssignedToEstimator<EntityId>(
								    0u, 1u ) );
  TEST_ASSERT( hdf5_file_handler.isEntityAssignedToEstimator<EntityId>(
								    0u, 2u ) );
  TEST_ASSERT( hdf5_file_handler.isEntityAssignedToEstimator<EntityId>(
								    0u, 3u ) );
  TEST_ASSERT( hdf5_file_handler.isEntityAssignedToEstimator<EntityId>(
								    0u, 4u ) );
  TEST_ASSERT( !hdf5_file_handler.isEntityAssignedToEstimator<EntityId>(
								    0u, 5u ) );

  // Check that the entities and norm constants have been set
  std::map<EntityId,double> entity_id_norms;
  hdf5_file_handler.getEstimatorEntities( 0u, entity_id_norms );

  TEST_EQUALITY_CONST( entity_id_norms.size(), 5 );
  TEST_EQUALITY_CONST( entity_id_norms[0], 1.0 );
  TEST_EQUALITY_CONST( entity_id_norms[1], 2.0 );
  TEST_EQUALITY_CONST( entity_id_norms[2], 3.0 );
  TEST_EQUALITY_CONST( entity_id_norms[3], 4.0 );
  TEST_EQUALITY_CONST( entity_id_norms[4], 5.0 );
  
  // Check that entity norm constants have been set
  double entity_norm_constant;
  hdf5_file_handler.getEntityNormConstant( 0u, 0u, entity_norm_constant );

  TEST_EQUALITY_CONST( entity_norm_constant, 1.0 );

  hdf5_file_handler.getEntityNormConstant( 0u, 1u, entity_norm_constant );
  
  TEST_EQUALITY_CONST( entity_norm_constant, 2.0 );

  hdf5_file_handler.getEntityNormConstant( 0u, 2u, entity_norm_constant );
  
  TEST_EQUALITY_CONST( entity_norm_constant, 3.0 );

  hdf5_file_handler.getEntityNormConstant( 0u, 3u, entity_norm_constant );
  
  TEST_EQUALITY_CONST( entity_norm_constant, 4.0 );

  hdf5_file_handler.getEntityNormConstant( 0u, 4u, entity_norm_constant );
  
  TEST_EQUALITY_CONST( entity_norm_constant, 5.0 );

  // Check that the total norm constant has been set
  double total_norm_constant;
  hdf5_file_handler.getEstimatorTotalNormConstant( 0u, total_norm_constant );

  TEST_EQUALITY_CONST( total_norm_constant, 15.0 );

  // Check that the raw entity bin data has been set
  Teuchos::Array<Utility::Pair<double,double> > 
    raw_bin_data( 24, Utility::Pair<double,double>( 0.0, 0.0 ) ),
    raw_bin_data_copy;
  
  hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 0u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

  hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 1u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );
  
  hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 2u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

  hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 3u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

  hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 4u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

  // Check that there is no processed data since it was not requested on export
  Teuchos::Array<Utility::Pair<double,double> > 
    processed_bin_data_copy;
  
  TEST_THROW( hdf5_file_handler.getProcessedEstimatorEntityBinData( 
						     0u, 
						     0u, 
						     processed_bin_data_copy ),
	      std::runtime_error );
  TEST_THROW( hdf5_file_handler.getProcessedEstimatorEntityBinData( 
						     0u, 
						     1u, 
						     processed_bin_data_copy ),
	      std::runtime_error );
  TEST_THROW( hdf5_file_handler.getProcessedEstimatorEntityBinData( 
						     0u, 
						     2u, 
						     processed_bin_data_copy ),
	      std::runtime_error );
  TEST_THROW( hdf5_file_handler.getProcessedEstimatorEntityBinData( 
						     0u, 
						     3u, 
						     processed_bin_data_copy ),
	      std::runtime_error );
  TEST_THROW( hdf5_file_handler.getProcessedEstimatorEntityBinData( 
						     0u, 
						     4u, 
						     processed_bin_data_copy ),
	      std::runtime_error );

  // Check that the raw total bin data has been set
  Teuchos::Array<Utility::Pair<double,double> > 
    raw_total_bin_data( 24, Utility::Pair<double,double>( 0.0, 0.0 ) ),
    raw_total_bin_data_copy;

  hdf5_file_handler.getRawEstimatorTotalBinData( 0u, raw_total_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_total_bin_data, raw_total_bin_data_copy );

  // Check that the processed total bin data has not been set
  Teuchos::Array<Utility::Pair<double,double> > 
    processed_total_bin_data;

  TEST_THROW( hdf5_file_handler.getProcessedEstimatorTotalBinData( 
						0u, processed_total_bin_data ),
	      std::runtime_error );    
}

UNIT_TEST_INSTANTIATION( EntityEstimator, exportData_raw );

//---------------------------------------------------------------------------//
// Check if the estimator data can be processed and exported
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( EntityEstimator,
				   exportData_process,
				   EntityId )
{
  Teuchos::RCP<MonteCarlo::Estimator> estimator;

  Teuchos::Array<EntityId> entity_ids;
  Teuchos::Array<double> entity_norm_constants;

  {
    // Set the entities ids
    entity_ids.resize( 5 );
    entity_ids[0] = 0;
    entity_ids[1] = 1;
    entity_ids[2] = 2;
    entity_ids[3] = 3;
    entity_ids[4] = 4;
    
    // Set the entity normalization constants
    entity_norm_constants.resize( 5 );
    entity_norm_constants[0] = 1.0;
    entity_norm_constants[1] = 2.0;
    entity_norm_constants[2] = 3.0;
    entity_norm_constants[3] = 4.0;
    entity_norm_constants[4] = 5.0;
  }

  estimator.reset( new TestEntityEstimator<EntityId>(0u,
						     5.0,
						     entity_ids,
						     entity_norm_constants ) );

  Teuchos::Array<double> energy_bin_boundaries, cosine_bin_boundaries,
    time_bin_boundaries;
  Teuchos::Array<unsigned> collision_number_bins;
  
  {
    // Set the energy bins
    energy_bin_boundaries.resize( 3 );
    energy_bin_boundaries[0] = 0.0;
    energy_bin_boundaries[1] = 1e-1;
    energy_bin_boundaries[2] = 1.0;

    estimator->setBinBoundaries<MonteCarlo::ENERGY_DIMENSION>( 
						       energy_bin_boundaries );

    // Set the cosine bins
    cosine_bin_boundaries.resize( 3 );
    cosine_bin_boundaries[0] = -1.0;
    cosine_bin_boundaries[1] = 0.0;
    cosine_bin_boundaries[2] = 1.0;

    estimator->setBinBoundaries<MonteCarlo::COSINE_DIMENSION>( 
						       cosine_bin_boundaries );

    // Set the time bins
    time_bin_boundaries.resize( 3 );
    time_bin_boundaries[0] = 0.0;
    time_bin_boundaries[1] = 1e3;
    time_bin_boundaries[2] = 1e5;

    estimator->setBinBoundaries<MonteCarlo::TIME_DIMENSION>( 
							 time_bin_boundaries );

    // Set the collision number bins
    collision_number_bins.resize( 3 );
    collision_number_bins[0] = 0u;
    collision_number_bins[1] = 1u;
    collision_number_bins[2] = std::numeric_limits<unsigned>::max();

    estimator->setBinBoundaries<MonteCarlo::COLLISION_NUMBER_DIMENSION>( 
						       collision_number_bins );

    // Set the response functions
    Teuchos::Array<std::shared_ptr<MonteCarlo::ResponseFunction> > 
      response_functions( 1 );
    response_functions[0] = 
      MonteCarlo::ResponseFunction::default_response_function;

    estimator->setResponseFunctions( response_functions );
  }

  // Initialize the hdf5 file
  std::shared_ptr<Utility::HDF5FileHandler> 
    hdf5_file( new Utility::HDF5FileHandler );
  hdf5_file->openHDF5FileAndOverwrite( "test_entity_estimator.h5" );

  MonteCarlo::ParticleHistoryObserver::setStartTime( 0.0 );
  MonteCarlo::ParticleHistoryObserver::setEndTime( 1.0 );
  MonteCarlo::ParticleHistoryObserver::setNumberOfHistories( 1 );

  estimator->exportData( hdf5_file, true );

  // Create an estimator hdf5 file handler
  MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( hdf5_file );

  // Make sure that the estimator exists in the hdf5 file
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 0u ) );

  // Check that the estimator multiplier has been set
  double multiplier;
  hdf5_file_handler.getEstimatorMultiplier( 0u, multiplier );

  TEST_EQUALITY_CONST( multiplier, 5.0 );

  // Check that the estimator response function ordering has been set
  Teuchos::Array<unsigned> response_function_ordering;
  hdf5_file_handler.getEstimatorResponseFunctionOrdering( 
						  0u,
						  response_function_ordering );
  
  TEST_EQUALITY_CONST( response_function_ordering.size(), 1 );
  TEST_EQUALITY( response_function_ordering[0], 
		 std::numeric_limits<unsigned>::max() );
  
  // Check that the estimator dimension ordering has been set
  Teuchos::Array<MonteCarlo::PhaseSpaceDimension> dimension_ordering;
  hdf5_file_handler.getEstimatorDimensionOrdering( 0u, dimension_ordering );
  
  TEST_EQUALITY_CONST( dimension_ordering.size(), 4 );
  TEST_EQUALITY_CONST( dimension_ordering[0], MonteCarlo::ENERGY_DIMENSION );
  TEST_EQUALITY_CONST( dimension_ordering[1], MonteCarlo::COSINE_DIMENSION );
  TEST_EQUALITY_CONST( dimension_ordering[2], MonteCarlo::TIME_DIMENSION );
  TEST_EQUALITY_CONST( dimension_ordering[3], 
		       MonteCarlo::COLLISION_NUMBER_DIMENSION );

  // Check that the energy bins have been set
  Teuchos::Array<double> energy_bin_boundaries_copy;
  hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::ENERGY_DIMENSION>( 
						  0u,
						  energy_bin_boundaries_copy );

  TEST_COMPARE_ARRAYS( energy_bin_boundaries, energy_bin_boundaries_copy );

  // Check that the cosine bins have been set
  Teuchos::Array<double> cosine_bin_boundaries_copy;
  hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::COSINE_DIMENSION>( 
						  0u, 
						  cosine_bin_boundaries_copy );

  TEST_COMPARE_ARRAYS( cosine_bin_boundaries, cosine_bin_boundaries_copy );

  // Check that the time bins have been set
  Teuchos::Array<double> time_bin_boundaries_copy;
  hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::TIME_DIMENSION>(
						    0u,
						    time_bin_boundaries_copy );

  TEST_COMPARE_ARRAYS( time_bin_boundaries, time_bin_boundaries_copy );

  // Check that the collision number bins have been set
  Teuchos::Array<unsigned> collision_number_bins_copy;
  hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::COLLISION_NUMBER_DIMENSION>(
						  0u,
						  collision_number_bins_copy );

  TEST_COMPARE_ARRAYS( collision_number_bins, collision_number_bins_copy );

  // Check if entities are assigned to the estimator
  TEST_ASSERT( hdf5_file_handler.isEntityAssignedToEstimator<EntityId>(
								    0u, 0u ) );
  TEST_ASSERT( hdf5_file_handler.isEntityAssignedToEstimator<EntityId>(
								    0u, 1u ) );
  TEST_ASSERT( hdf5_file_handler.isEntityAssignedToEstimator<EntityId>(
								    0u, 2u ) );
  TEST_ASSERT( hdf5_file_handler.isEntityAssignedToEstimator<EntityId>(
								    0u, 3u ) );
  TEST_ASSERT( hdf5_file_handler.isEntityAssignedToEstimator<EntityId>(
								    0u, 4u ) );
  TEST_ASSERT( !hdf5_file_handler.isEntityAssignedToEstimator<EntityId>(
								    0u, 5u ) );

  // Check that the entities and norm constants have been set
  std::map<EntityId,double> entity_id_norms;
  hdf5_file_handler.getEstimatorEntities( 0u, entity_id_norms );

  TEST_EQUALITY_CONST( entity_id_norms.size(), 5 );
  TEST_EQUALITY_CONST( entity_id_norms[0], 1.0 );
  TEST_EQUALITY_CONST( entity_id_norms[1], 2.0 );
  TEST_EQUALITY_CONST( entity_id_norms[2], 3.0 );
  TEST_EQUALITY_CONST( entity_id_norms[3], 4.0 );
  TEST_EQUALITY_CONST( entity_id_norms[4], 5.0 );
  
  // Check that entity norm constants have been set
  double entity_norm_constant;
  hdf5_file_handler.getEntityNormConstant( 0u, 0u, entity_norm_constant );

  TEST_EQUALITY_CONST( entity_norm_constant, 1.0 );

  hdf5_file_handler.getEntityNormConstant( 0u, 1u, entity_norm_constant );
  
  TEST_EQUALITY_CONST( entity_norm_constant, 2.0 );

  hdf5_file_handler.getEntityNormConstant( 0u, 2u, entity_norm_constant );
  
  TEST_EQUALITY_CONST( entity_norm_constant, 3.0 );

  hdf5_file_handler.getEntityNormConstant( 0u, 3u, entity_norm_constant );
  
  TEST_EQUALITY_CONST( entity_norm_constant, 4.0 );

  hdf5_file_handler.getEntityNormConstant( 0u, 4u, entity_norm_constant );
  
  TEST_EQUALITY_CONST( entity_norm_constant, 5.0 );

  // Check that the total norm constant has been set
  double total_norm_constant;
  hdf5_file_handler.getEstimatorTotalNormConstant( 0u, total_norm_constant );

  TEST_EQUALITY_CONST( total_norm_constant, 15.0 );

  // Check that the raw entity bin data has been set
  Teuchos::Array<Utility::Pair<double,double> > 
    raw_bin_data( 24, Utility::Pair<double,double>( 0.0, 0.0 ) ),
    raw_bin_data_copy;
  
  hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 0u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

  hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 1u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );
  
  hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 2u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

  hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 3u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

  hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 4u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

  // Check that the processed bin data has been set
  Teuchos::Array<Utility::Pair<double,double> > 
    processed_bin_data( 24, Utility::Pair<double,double>( 0.0, 0.0 ) ),
    processed_bin_data_copy;
  
  hdf5_file_handler.getProcessedEstimatorEntityBinData( 
						     0u, 
						     0u, 
						     processed_bin_data_copy );
  
  UTILITY_TEST_COMPARE_ARRAYS( processed_bin_data, processed_bin_data_copy );
  
  hdf5_file_handler.getProcessedEstimatorEntityBinData( 
						     0u, 
						     1u, 
						     processed_bin_data_copy );
	      
  UTILITY_TEST_COMPARE_ARRAYS( processed_bin_data, processed_bin_data_copy );
  
  hdf5_file_handler.getProcessedEstimatorEntityBinData( 
						     0u, 
						     2u, 
						     processed_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( processed_bin_data, processed_bin_data_copy );
	      
  hdf5_file_handler.getProcessedEstimatorEntityBinData( 
						     0u, 
						     3u, 
						     processed_bin_data_copy );
  
  UTILITY_TEST_COMPARE_ARRAYS( processed_bin_data, processed_bin_data_copy );
  
  hdf5_file_handler.getProcessedEstimatorEntityBinData( 
						     0u, 
						     4u, 
						     processed_bin_data_copy );
  
  UTILITY_TEST_COMPARE_ARRAYS( processed_bin_data, processed_bin_data_copy );

  // Check that the raw total bin data has been set
  Teuchos::Array<Utility::Pair<double,double> > 
    raw_total_bin_data( 24, Utility::Pair<double,double>( 0.0, 0.0 ) ),
    raw_total_bin_data_copy;

  hdf5_file_handler.getRawEstimatorTotalBinData( 0u, raw_total_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_total_bin_data, raw_total_bin_data_copy );

  // Check that the processed total bin data has not been set
  Teuchos::Array<Utility::Pair<double,double> >
    processed_total_bin_data( 24, Utility::Pair<double,double>( 0.0, 0.0 ) ),
    processed_total_bin_data_copy;

  hdf5_file_handler.getProcessedEstimatorTotalBinData( 
					   0u, processed_total_bin_data_copy );
	      
  UTILITY_TEST_COMPARE_ARRAYS( processed_total_bin_data, 
			       processed_total_bin_data_copy );
}

UNIT_TEST_INSTANTIATION( EntityEstimator, exportData_process );

//---------------------------------------------------------------------------//
// Check that a history contribution can be committed to a bin
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( EntityEstimator,
				   commitHistoryContributionToBinOfEntity,
				   EntityId )
{
  Teuchos::RCP<TestEntityEstimator<EntityId> > entity_estimator;

  initializeEntityEstimator( entity_estimator, true );

  unsigned num_estimator_bins = entity_estimator->getNumberOfBins()*
    entity_estimator->getNumberOfResponseFunctions();

  typename MonteCarlo::EntityEstimator<EntityId>::EntityIdSet entity_ids;
  
  entity_estimator->getEntityIds( entity_ids );

  typename MonteCarlo::EntityEstimator<EntityId>::EntityIdSet::const_iterator
    entity_id, end_entity_id;
  entity_id = entity_ids.begin();
  end_entity_id = entity_ids.end();
  
  // Commit one contribution to every bin of the estimator 
  while( entity_id != end_entity_id )
  {
    for( unsigned i = 0u; i < num_estimator_bins; ++i )
    {
      entity_estimator->commitHistoryContributionToBinOfEntity( *entity_id,
								i,
								0.5 );
    }

    ++entity_id;
  }

  MonteCarlo::ParticleHistoryObserver::setNumberOfHistories( 1.0 );
  MonteCarlo::ParticleHistoryObserver::setEndTime( 1.0 );

  // Initialize the hdf5 file
  std::shared_ptr<Utility::HDF5FileHandler>
    hdf5_file( new Utility::HDF5FileHandler );
  hdf5_file->openHDF5FileAndOverwrite( "test_entity_estimator2.h5" );

  // Export the estimator data
  entity_estimator->exportData( hdf5_file, true );

  // Create and estimator hdf5 file handler
  MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( hdf5_file );

  // Retrieve the raw bin data for each entity
  Teuchos::Array<Utility::Pair<double,double> > 
    raw_bin_data( 24, Utility::Pair<double,double>( 0.5, 0.25 ) ),
    raw_bin_data_copy;

  hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 0u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

  hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 1u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

  hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 2u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

  hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 3u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

  hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 4u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

  // Retrieve the processed in data for each entity
  Teuchos::Array<Utility::Pair<double,double> >
    proc_bin_data( 24, Utility::Pair<double,double>( 5.0, 0.0 ) ),
    proc_bin_data_copy;

  hdf5_file_handler.getProcessedEstimatorEntityBinData( 0u, 
							0u, 
							proc_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( proc_bin_data, proc_bin_data_copy );

  proc_bin_data.clear();
  proc_bin_data.resize( 24, Utility::Pair<double,double>( 2.5, 0.0 ) );

  hdf5_file_handler.getProcessedEstimatorEntityBinData( 0u, 
							1u, 
							proc_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( proc_bin_data, proc_bin_data_copy );

  proc_bin_data.clear();
  proc_bin_data.resize( 24, Utility::Pair<double,double>( 5.0/3.0, 0.0 ) );

  hdf5_file_handler.getProcessedEstimatorEntityBinData( 0u, 
							2u, 
							proc_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( proc_bin_data, proc_bin_data_copy );

  proc_bin_data.clear();
  proc_bin_data.resize( 24, Utility::Pair<double,double>( 5.0/4.0, 0.0 ) );

  hdf5_file_handler.getProcessedEstimatorEntityBinData( 0u, 
							3u, 
							proc_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( proc_bin_data, proc_bin_data_copy );

  proc_bin_data.clear();
  proc_bin_data.resize( 24, Utility::Pair<double,double>( 1.0, 0.0 ) );

  hdf5_file_handler.getProcessedEstimatorEntityBinData( 0u, 
							4u, 
							proc_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( proc_bin_data, proc_bin_data_copy );
}

UNIT_TEST_INSTANTIATION( EntityEstimator, 
			 commitHistoryContributionToBinOfEntity );

//---------------------------------------------------------------------------//
// Check that a history contribution can be committed to a bin
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( 
			  EntityEstimator,
			  commitHistoryContributionToBinOfEntity_thread_safe,
			  EntityId )
{
  Teuchos::RCP<TestEntityEstimator<EntityId> > entity_estimator;

  initializeEntityEstimator( entity_estimator, true );

  unsigned num_estimator_bins = entity_estimator->getNumberOfBins()*
    entity_estimator->getNumberOfResponseFunctions();

  typename MonteCarlo::EntityEstimator<EntityId>::EntityIdSet entity_ids;
  
  entity_estimator->getEntityIds( entity_ids );

  typename MonteCarlo::EntityEstimator<EntityId>::EntityIdSet::const_iterator
    entity_id, end_entity_id;
  entity_id = entity_ids.begin();
  end_entity_id = entity_ids.end();
  
  // Commit one contribution to every bin of the estimator 
  while( entity_id != end_entity_id )
  {
    for( unsigned i = 0u; i < num_estimator_bins; ++i )
    {
      #pragma omp parallel num_threads( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() )
      {
	entity_estimator->commitHistoryContributionToBinOfEntity( 
			     *entity_id,
			     i,
			     Utility::GlobalOpenMPSession::getThreadId()+1.0 );
      }
    }

    ++entity_id;
  }

  unsigned histories =
    Utility::GlobalOpenMPSession::getRequestedNumberOfThreads();
  MonteCarlo::ParticleHistoryObserver::setNumberOfHistories( histories );
  MonteCarlo::ParticleHistoryObserver::setEndTime( 1.0 );

  // Initialize the hdf5 file
  std::shared_ptr<Utility::HDF5FileHandler>
    hdf5_file( new Utility::HDF5FileHandler );
  hdf5_file->openHDF5FileAndOverwrite( "test_entity_estimator2.h5" );

  // Export the estimator data
  entity_estimator->exportData( hdf5_file, true );

  // Create an estimator hdf5 file handler
  MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( hdf5_file );

  double moment_1 = histories*(histories+1.0)/2.0;
  
  double moment_2 = histories*(histories+1.0)*(2*histories+1.0)/6.0;

  // Retrieve the raw bin data for each entity
  Teuchos::Array<Utility::Pair<double,double> > 
    raw_bin_data( 24, Utility::Pair<double,double>( moment_1, moment_2 ) ),
    raw_bin_data_copy;

  hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 0u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

  hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 1u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

  hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 2u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

  hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 3u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

  hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 4u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

  double unnorm_mean = moment_1*10.0/histories;
  double rel_err = sqrt( moment_2/(moment_1*moment_1) - 1.0/histories );

  // Retrieve the processed in data for each entity
  double mean = unnorm_mean;
  Teuchos::Array<Utility::Pair<double,double> >
    proc_bin_data( 24, Utility::Pair<double,double>( mean, rel_err ) ),
    proc_bin_data_copy;

  hdf5_file_handler.getProcessedEstimatorEntityBinData( 0u, 
							0u, 
							proc_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( proc_bin_data, proc_bin_data_copy );

  mean = unnorm_mean/2.0;
  proc_bin_data.clear();
  proc_bin_data.resize( 24, Utility::Pair<double,double>( mean, rel_err ) );

  hdf5_file_handler.getProcessedEstimatorEntityBinData( 0u, 
							1u, 
							proc_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( proc_bin_data, proc_bin_data_copy );

  mean = unnorm_mean/3.0;
  proc_bin_data.clear();
  proc_bin_data.resize( 24, Utility::Pair<double,double>( mean, rel_err ) );

  hdf5_file_handler.getProcessedEstimatorEntityBinData( 0u, 
							2u, 
							proc_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( proc_bin_data, proc_bin_data_copy );

  mean = unnorm_mean/4.0;
  proc_bin_data.clear();
  proc_bin_data.resize( 24, Utility::Pair<double,double>( mean, rel_err ) );

  hdf5_file_handler.getProcessedEstimatorEntityBinData( 0u, 
							3u, 
							proc_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( proc_bin_data, proc_bin_data_copy );

  mean = unnorm_mean/5.0;
  proc_bin_data.clear();
  proc_bin_data.resize( 24, Utility::Pair<double,double>( mean, rel_err ) );

  hdf5_file_handler.getProcessedEstimatorEntityBinData( 0u, 
							4u, 
							proc_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( proc_bin_data, proc_bin_data_copy );
}

UNIT_TEST_INSTANTIATION( EntityEstimator, 
			 commitHistoryContributionToBinOfEntity_thread_safe);

//---------------------------------------------------------------------------//
// Check that a history contribution can be committed to a bin of the total
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( EntityEstimator,
				   commitHistoryContributionToBinOfTotal,
				   EntityId )
{
  Teuchos::RCP<TestEntityEstimator<EntityId> > entity_estimator;

  initializeEntityEstimator( entity_estimator, true );

  unsigned num_estimator_bins = entity_estimator->getNumberOfBins()*
    entity_estimator->getNumberOfResponseFunctions();

  // Commit one contribution to every bin of the estimator 
  for( unsigned i = 0u; i < num_estimator_bins; ++i )
  {
    entity_estimator->commitHistoryContributionToBinOfTotal( i, 0.5 );
  }

  MonteCarlo::ParticleHistoryObserver::setNumberOfHistories( 1.0 );
  MonteCarlo::ParticleHistoryObserver::setEndTime( 1.0 );

  // Initialize the hdf5 file
  std::shared_ptr<Utility::HDF5FileHandler>
    hdf5_file( new Utility::HDF5FileHandler );
  hdf5_file->openHDF5FileAndOverwrite( "test_entity_estimator3.h5" );

  // Export the estimator data
  entity_estimator->exportData( hdf5_file, true );

  // Create an estimator hfd5 file handler
  MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( hdf5_file );

  // Retrieve the raw bin data for the total
  Teuchos::Array<Utility::Pair<double,double> > 
    raw_bin_data( 24, Utility::Pair<double,double>( 0.5, 0.25 ) ),
    raw_bin_data_copy;

  hdf5_file_handler.getRawEstimatorTotalBinData( 0u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

  // Retrieve the processed in data for the total
  Teuchos::Array<Utility::Pair<double,double> >
    proc_bin_data( 24, Utility::Pair<double,double>( 5.0/15.0, 0.0 ) ),
    proc_bin_data_copy;

  hdf5_file_handler.getProcessedEstimatorTotalBinData( 0u, 
						       proc_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( proc_bin_data, proc_bin_data_copy );
}

UNIT_TEST_INSTANTIATION( EntityEstimator, 
			 commitHistoryContributionToBinOfTotal );

//---------------------------------------------------------------------------//
// Check that a history contribution can be committed to a bin of the total
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( 
			   EntityEstimator,
			   commitHistoryContributionToBinOfTotal_thread_safe,
			   EntityId )
{
  Teuchos::RCP<TestEntityEstimator<EntityId> > entity_estimator;

  initializeEntityEstimator( entity_estimator, true );

  unsigned num_estimator_bins = entity_estimator->getNumberOfBins()*
    entity_estimator->getNumberOfResponseFunctions();

  // Commit one contribution to every bin of the estimator 
  for( unsigned i = 0u; i < num_estimator_bins; ++i )
  {
    #pragma omp parallel num_threads( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() )
    {
      entity_estimator->commitHistoryContributionToBinOfTotal( 
		        i, Utility::GlobalOpenMPSession::getThreadId() + 1.0 );
    }
  }

  unsigned histories =
    Utility::GlobalOpenMPSession::getRequestedNumberOfThreads();
  
  MonteCarlo::ParticleHistoryObserver::setNumberOfHistories( histories );
  MonteCarlo::ParticleHistoryObserver::setEndTime( 1.0 );

  // Initialize the hdf5 file
  std::shared_ptr<Utility::HDF5FileHandler>
    hdf5_file( new Utility::HDF5FileHandler );
  hdf5_file->openHDF5FileAndOverwrite( "test_entity_estimator3.h5" );

  // Export the estimator data
  entity_estimator->exportData( hdf5_file, true );

  // Create an hdf5 file and overwrite
  MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( hdf5_file );

  double moment_1 = histories*(histories+1.0)/2.0;
  
  double moment_2 = histories*(histories+1.0)*(2*histories+1.0)/6.0;

  // Retrieve the raw bin data for each entity
  Teuchos::Array<Utility::Pair<double,double> > 
    raw_bin_data( 24, Utility::Pair<double,double>( moment_1, moment_2 ) ),
    raw_bin_data_copy;

  hdf5_file_handler.getRawEstimatorTotalBinData( 0u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

  double mean = moment_1*10.0/(histories*15.0);
  double rel_err = sqrt( moment_2/(moment_1*moment_1) - 1.0/histories );

  // Retrieve the processed in data for each entity
  Teuchos::Array<Utility::Pair<double,double> >
    proc_bin_data( 24, Utility::Pair<double,double>( mean, rel_err ) ),
    proc_bin_data_copy;

  hdf5_file_handler.getProcessedEstimatorTotalBinData( 0u, 
						       proc_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( proc_bin_data, proc_bin_data_copy );
}

UNIT_TEST_INSTANTIATION( EntityEstimator, 
			 commitHistoryContributionToBinOfTotal_thread_safe );

//---------------------------------------------------------------------------//
// Check that a history contribution can be committed to a bin of the total
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( EntityEstimator,
				   resetData,
				   EntityId )
{
  Teuchos::RCP<TestEntityEstimator<EntityId> > entity_estimator;

  initializeEntityEstimator( entity_estimator, true );

  unsigned num_estimator_bins = entity_estimator->getNumberOfBins()*
    entity_estimator->getNumberOfResponseFunctions();

  // Commit one contribution to every bin of the estimator 
  for( unsigned i = 0u; i < num_estimator_bins; ++i )
  {
    entity_estimator->commitHistoryContributionToBinOfTotal( i, 0.5 );
  }

  // Reset the estimator data
  entity_estimator->resetData();

  // Make sure the bins have not been changed
  TEST_EQUALITY_CONST( 
	     entity_estimator->getNumberOfBins( MonteCarlo::ENERGY_DIMENSION ),
	     2 );
  TEST_EQUALITY_CONST( 
	     entity_estimator->getNumberOfBins( MonteCarlo::TIME_DIMENSION ),
	     2 );
  TEST_EQUALITY_CONST( 
	     entity_estimator->getNumberOfBins( MonteCarlo::COSINE_DIMENSION ),
	     2 );
  TEST_EQUALITY_CONST( 
   entity_estimator->getNumberOfBins( MonteCarlo::COLLISION_NUMBER_DIMENSION ),
   3 );
  TEST_EQUALITY_CONST( entity_estimator->getNumberOfBins(), 24 );

  // Make sure the response functions have not changed
  TEST_EQUALITY_CONST( entity_estimator->getNumberOfResponseFunctions(), 1 );
  
  // Initialize the hdf5 file
  std::shared_ptr<Utility::HDF5FileHandler>
    hdf5_file( new Utility::HDF5FileHandler );
  hdf5_file->openHDF5FileAndOverwrite( "test_entity_estimator4.h5" );

  // Export the estimator data
  entity_estimator->exportData( hdf5_file, false );

  // Create an estimator hdf5 file handler
  MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( hdf5_file );

  // Retrieve the raw bin data for each entity
  Teuchos::Array<Utility::Pair<double,double> > 
    raw_bin_data( 24, Utility::Pair<double,double>( 0.0, 0.0 ) ),
    raw_bin_data_copy;

  hdf5_file_handler.getRawEstimatorEntityBinData<EntityId>( 
						   0u, 0u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data, 
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<EntityId>( 
						   0u, 1u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data, 
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<EntityId>( 
						   0u, 2u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data, 
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<EntityId>( 
						   0u, 3u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data, 
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<EntityId>( 
						   0u, 4u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data, 
					raw_bin_data_copy,
					1e-15 );

  // Retrieve the total raw total bin data
  hdf5_file_handler.getRawEstimatorTotalBinData( 0u, raw_bin_data );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data, 
					raw_bin_data_copy,
					1e-15 );
}

UNIT_TEST_INSTANTIATION( EntityEstimator, resetData )

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  int threads = 1;

  clp.setOption( "threads",
		 &threads,
		 "Number of threads to use" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Set up the global OpenMP session
  if( Utility::GlobalOpenMPSession::isOpenMPUsed() )
    Utility::GlobalOpenMPSession::setNumberOfThreads( threads );

  // Run the unit tests
  const bool success = Teuchos::UnitTestRepository::runUnitTests(*out);

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// tstEntityEstimator.cpp
//---------------------------------------------------------------------------//
