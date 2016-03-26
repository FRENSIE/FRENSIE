//---------------------------------------------------------------------------//
//!
//! \file   tstEstimatorHDF5FileHandler.cpp
//! \author Alex Robinson
//! \brief  Estimator hdf5 file handler unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <string>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"
#include "MonteCarlo_EstimatorHDF5FileHandler.hpp"
#include "MonteCarlo_PhaseSpaceDimension.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_HDF5FileHandler.hpp"

//---------------------------------------------------------------------------//
// Instantiation Macros
//---------------------------------------------------------------------------//
#define DIMENSION_UNIT_TEST_INSTANTIATION( type, name )	\
  using namespace MonteCarlo;						\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, ENERGY_DIMENSION ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, COSINE_DIMENSION ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, TIME_DIMENSION );	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, COLLISION_NUMBER_DIMENSION ); \

#define ENTITY_ID_UNIT_TEST_INSTANTIATION( type, name )			\
  typedef unsigned long unsigned_l;					\
  typedef unsigned long long unsigned_ll;				\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, unsigned );		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, unsigned_l );	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, unsigned_ll );	\
    
//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

const std::string hdf5_file_name( "test_estimators.h5" );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the handler can be constructed
TEUCHOS_UNIT_TEST( EstimatorHDF5FileHandler, constructor_ownership )
{
  std::shared_ptr<MonteCarlo::EstimatorHDF5FileHandler> file_handler;
  TEST_NOTHROW( file_handler.reset( 
		new MonteCarlo::EstimatorHDF5FileHandler( hdf5_file_name ) ) );

  // Make sure setter methods work
  TEST_NOTHROW( file_handler->setSurfaceEstimator( 0u ) );
  
  file_handler.reset();
  
  TEST_NOTHROW( file_handler.reset( new MonteCarlo::EstimatorHDF5FileHandler(
	hdf5_file_name,
	MonteCarlo::EstimatorHDF5FileHandler::APPEND_ESTIMATOR_HDF5_FILE ) ) );

  // Make sure file has not been overwritten
  TEST_ASSERT( file_handler->isSurfaceEstimator( 0u ) );

  // Make sure setter methods work
  TEST_NOTHROW( file_handler->setSurfaceEstimator( 1u ) );

  file_handler.reset();

  TEST_NOTHROW( file_handler.reset( new MonteCarlo::EstimatorHDF5FileHandler(
     hdf5_file_name,
     MonteCarlo::EstimatorHDF5FileHandler::READ_ONLY_ESTIMATOR_HDF5_FILE ) ) );

  // Make sure file has not been overwritten
  TEST_ASSERT( file_handler->isSurfaceEstimator( 0u ) );
  TEST_ASSERT( file_handler->isSurfaceEstimator( 1u ) );

  TEST_THROW( file_handler->setSurfaceEstimator( 2u ), std::runtime_error );

  // Reset the file
  file_handler.reset();
  file_handler.reset(
		  new MonteCarlo::EstimatorHDF5FileHandler( hdf5_file_name ) );
}

//---------------------------------------------------------------------------//
// Check that the handler can be constructed
TEUCHOS_UNIT_TEST( EstimatorHDF5FileHandler, constructor_sharing )
{
  std::shared_ptr<Utility::HDF5FileHandler> shared_handler( 
						new Utility::HDF5FileHandler );
  shared_handler->openHDF5FileAndOverwrite( hdf5_file_name );

  std::shared_ptr<MonteCarlo::EstimatorHDF5FileHandler> estimator_file_handler(
		  new MonteCarlo::EstimatorHDF5FileHandler( shared_handler ) );

  estimator_file_handler->setSurfaceEstimator( 0u );
  
  estimator_file_handler.reset();

  TEST_ASSERT( shared_handler->hasOpenFile() );
  
  shared_handler->closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that an estimator can be set as a surface estimator
TEUCHOS_UNIT_TEST( EstimatorHDF5FileHandler, setSurfaceEstimator )
{
  MonteCarlo::EstimatorHDF5FileHandler file_handler( hdf5_file_name );

  file_handler.setSurfaceEstimator( 0u );

  TEST_ASSERT( file_handler.isSurfaceEstimator( 0u ) );
  TEST_ASSERT( !file_handler.isCellEstimator( 0u ) );
  TEST_ASSERT( !file_handler.isMeshEstimator( 0u ) );
}

//---------------------------------------------------------------------------//
// Check that an estimator can be set as a cell estimator
TEUCHOS_UNIT_TEST( EstimatorHDF5FileHandler, setCellEstimator )
{
  MonteCarlo::EstimatorHDF5FileHandler file_handler( hdf5_file_name );

  file_handler.setCellEstimator( 0u );

  TEST_ASSERT( !file_handler.isSurfaceEstimator( 0u ) );
  TEST_ASSERT( file_handler.isCellEstimator( 0u ) );
  TEST_ASSERT( !file_handler.isMeshEstimator( 0u) );
}

//---------------------------------------------------------------------------//
// Check that an estimator can be set as a mesh estimator
TEUCHOS_UNIT_TEST( EstimatorHDF5FileHandler, setMeshEstimator )
{
  MonteCarlo::EstimatorHDF5FileHandler file_handler( hdf5_file_name );

  file_handler.setMeshEstimator( 0u );

  TEST_ASSERT( !file_handler.isSurfaceEstimator( 0u ) );
  TEST_ASSERT( !file_handler.isCellEstimator( 0u ) );
  TEST_ASSERT( file_handler.isMeshEstimator( 0u) );
}

//---------------------------------------------------------------------------//
// Check if an estimator can be tested for existence 
TEUCHOS_UNIT_TEST( EstimatorHDF5FileHandler, doesEstimatorExist )
{
  MonteCarlo::EstimatorHDF5FileHandler file_handler( hdf5_file_name );

  file_handler.setCellEstimator( 0u );
  file_handler.setSurfaceEstimator( 1u );

  TEST_ASSERT( file_handler.doesEstimatorExist( 0u ) );
  TEST_ASSERT( file_handler.doesEstimatorExist( 1u ) );
  TEST_ASSERT( !file_handler.doesEstimatorExist( 2u ) );
}

//---------------------------------------------------------------------------//
// Check if the estimator multiplier can be set
TEUCHOS_UNIT_TEST( EstimatorHDF5FileHandler, set_getEstimatorMultiplier )
{
  MonteCarlo::EstimatorHDF5FileHandler file_handler( hdf5_file_name );

  // Write new multiplier
  file_handler.setEstimatorMultiplier( 0u, 1.0 );
  
  double multiplier;
  
  file_handler.getEstimatorMultiplier( 0u, multiplier );

  TEST_EQUALITY_CONST( multiplier, 1.0 );

  // Overwrite the multiplier
  file_handler.setEstimatorMultiplier( 0u, 2.0 );
  
  file_handler.getEstimatorMultiplier( 0u, multiplier );

  TEST_EQUALITY_CONST( multiplier, 2.0 );
}

//---------------------------------------------------------------------------//
// Check if the estimator total norm constant can be set
TEUCHOS_UNIT_TEST( EstimatorHDF5FileHandler, 
		   set_getEstimatorTotalNormConstant )
{
  MonteCarlo::EstimatorHDF5FileHandler file_handler( hdf5_file_name );

  // Write new multiplier
  file_handler.setEstimatorTotalNormConstant( 0u, 10.0 );
  
  double total_norm_constant;
  
  file_handler.getEstimatorTotalNormConstant( 0u, total_norm_constant );

  TEST_EQUALITY_CONST( total_norm_constant, 10.0 );

  // Overwrite the multiplier
  file_handler.setEstimatorTotalNormConstant( 0u, 20.0 );
  
  file_handler.getEstimatorTotalNormConstant( 0u, total_norm_constant );

  TEST_EQUALITY_CONST( total_norm_constant, 20.0 );
}

//---------------------------------------------------------------------------//
// Check if the estimator response function ordering can be set
TEUCHOS_UNIT_TEST( EstimatorHDF5FileHandler, 
		   set_getEstimatorResponseFunctionOrdering )
{
  MonteCarlo::EstimatorHDF5FileHandler file_handler( hdf5_file_name );

  // Write the new ordering
  Teuchos::Array<unsigned> ordering( 3 );
  ordering[0] = 10u;
  ordering[1] = 1u;
  ordering[2] = 5u;

  file_handler.setEstimatorResponseFunctionOrdering( 1u, ordering );
  
  Teuchos::Array<unsigned> ordering_copy;

  file_handler.getEstimatorResponseFunctionOrdering( 1u, ordering_copy );

  TEST_COMPARE_ARRAYS( ordering, ordering_copy );

  // Overwrite the ordering
  ordering[0] = 2u;
  ordering[1] = 3u;
  ordering[2] = 9u;

  file_handler.setEstimatorResponseFunctionOrdering( 1u, ordering );

  file_handler.getEstimatorResponseFunctionOrdering( 1u, ordering_copy );

  TEST_COMPARE_ARRAYS( ordering, ordering_copy );
}

//---------------------------------------------------------------------------//
// Check if the estimator dimension ordering can be returned
TEUCHOS_UNIT_TEST( EstimatorHDF5FileHandler,
		   set_getEstimatorDimensionOrdering )
{
  MonteCarlo::EstimatorHDF5FileHandler file_handler( hdf5_file_name );

  // Write the new ordering
  Teuchos::Array<MonteCarlo::PhaseSpaceDimension> ordering( 4 );
  ordering[0] = MonteCarlo::COSINE_DIMENSION;
  ordering[1] = MonteCarlo::ENERGY_DIMENSION;
  ordering[2] = MonteCarlo::COLLISION_NUMBER_DIMENSION;
  ordering[3] = MonteCarlo::TIME_DIMENSION;

  file_handler.setEstimatorDimensionOrdering( 2u, ordering );

  Teuchos::Array<MonteCarlo::PhaseSpaceDimension> ordering_copy;
  
  file_handler.getEstimatorDimensionOrdering( 2u, ordering_copy );
  
  TEST_COMPARE_ARRAYS( ordering, ordering_copy );

  // Overwrite the ordering
  ordering[0] = MonteCarlo::ENERGY_DIMENSION;
  ordering[1] = MonteCarlo::COLLISION_NUMBER_DIMENSION;
  ordering[2] = MonteCarlo::TIME_DIMENSION;
  ordering[3] = MonteCarlo::COSINE_DIMENSION;

  file_handler.setEstimatorDimensionOrdering( 2u, ordering );

  file_handler.getEstimatorDimensionOrdering( 2u, ordering_copy );

  TEST_COMPARE_ARRAYS( ordering, ordering_copy );
}

//---------------------------------------------------------------------------//
// Check that the estimator bin boundaries can be set
MC_UNIT_TEST_EPSD_TEMPLATE_1_DECL( EstimatorHDF5FileHandler,
				   set_getEstimatorBinBoundaries,
				   dimension )
{
  MonteCarlo::EstimatorHDF5FileHandler file_handler( hdf5_file_name );

  // Write the new bin boundaries
  Teuchos::Array<typename MonteCarlo::PhaseSpaceDimensionTraits<dimension>::dimensionType>
    bin_boundaries( 2 );
  bin_boundaries[0] = 0;
  bin_boundaries[1] = 1;
  
  file_handler.setEstimatorBinBoundaries<dimension>( 0u, bin_boundaries );

  Teuchos::Array<typename MonteCarlo::PhaseSpaceDimensionTraits<dimension>::dimensionType>
    bin_boundaries_copy;

  file_handler.getEstimatorBinBoundaries<dimension>( 0u, bin_boundaries_copy );

  TEST_COMPARE_ARRAYS( bin_boundaries, bin_boundaries_copy );
}

DIMENSION_UNIT_TEST_INSTANTIATION( EstimatorHDF5FileHandler, 
				   set_getEstimatorBinBoundaries );
 
//---------------------------------------------------------------------------//
// Check that the estimator entities can be set
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( EstimatorHDF5FileHandler,
				   set_getEstimatorEntities_array,
				   EntityIdType )
{
  Teuchos::RCP<MonteCarlo::EstimatorHDF5FileHandler> 
    file_handler( new MonteCarlo::EstimatorHDF5FileHandler( hdf5_file_name ) );

  // Write the new entity data
  Teuchos::Array<Utility::Pair<EntityIdType,double> > entity_data( 4 );
  entity_data[0]( 0, 1.0 );
  entity_data[1]( 1, 2.0 );
  entity_data[2]( 3, 4.0 );
  entity_data[3]( 10, 7.0 );

  file_handler->setEstimatorEntities( 1u, entity_data );

  Teuchos::Array<Utility::Pair<EntityIdType,double> > entity_data_copy;

  file_handler->getEstimatorEntities( 1u, entity_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( entity_data, entity_data_copy );

  // Overwrite the entity data (make sure large arrays can be written)
  file_handler.reset();
  file_handler.reset( new MonteCarlo::EstimatorHDF5FileHandler( 
       hdf5_file_name,
       MonteCarlo::EstimatorHDF5FileHandler::OVERWRITE_ESTIMATOR_HDF5_FILE ) );
  
  entity_data.resize( 500000 );

  for( unsigned i = 0; i < entity_data.size(); ++i )
    entity_data[i]( i, i+1.0 );

  file_handler->setEstimatorEntities( 1u, entity_data );

  file_handler->getEstimatorEntities( 1u, entity_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( entity_data, entity_data_copy );
}

ENTITY_ID_UNIT_TEST_INSTANTIATION( EstimatorHDF5FileHandler, 
				   set_getEstimatorEntities_array );

//---------------------------------------------------------------------------//
// Check that the estimator entities can be set
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( EstimatorHDF5FileHandler,
				   set_getEstimatorEntities_map,
				   EntityIdType )
{
  MonteCarlo::EstimatorHDF5FileHandler file_handler( hdf5_file_name );

  // Write the new entity data
  boost::unordered_map<EntityIdType,double> entity_data;
  entity_data[0] = 1.0;
  entity_data[1] = 2.0;
  entity_data[3] = 4.0;
  entity_data[10] = 7.0;

  file_handler.setEstimatorEntities( 1u, entity_data );

  boost::unordered_map<EntityIdType,double> entity_data_copy;

  file_handler.getEstimatorEntities( 1u, entity_data_copy );

  TEST_EQUALITY( entity_data.size(), entity_data_copy.size() );
  TEST_EQUALITY_CONST( entity_data_copy.find( 0 )->second, 1.0 );
  TEST_EQUALITY_CONST( entity_data_copy.find( 1 )->second, 2.0 );
  TEST_EQUALITY_CONST( entity_data_copy.find( 3 )->second, 4.0 );
  TEST_EQUALITY_CONST( entity_data_copy.find( 10 )->second, 7.0 );

  // Overwrite the entity data
  entity_data.clear();
  entity_data[2] = 2.0;
  entity_data[3] = 5.0;
  entity_data[9] = 9.0;
  entity_data[20] = 1.0;

  file_handler.setEstimatorEntities( 1u, entity_data );

  entity_data_copy.clear();
  file_handler.getEstimatorEntities( 1u, entity_data_copy );

  TEST_EQUALITY( entity_data.size(), entity_data_copy.size() );
  TEST_EQUALITY_CONST( entity_data_copy.find( 2 )->second, 2.0 );
  TEST_EQUALITY_CONST( entity_data_copy.find( 3 )->second, 5.0 );
  TEST_EQUALITY_CONST( entity_data_copy.find( 9 )->second, 9.0 );
  TEST_EQUALITY_CONST( entity_data_copy.find( 20 )->second, 1.0 );
}

ENTITY_ID_UNIT_TEST_INSTANTIATION( EstimatorHDF5FileHandler, 
				   set_getEstimatorEntities_map );

//---------------------------------------------------------------------------//
// Check that the estimator entity norm constant can be set
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( EstimatorHDF5FileHandler,
				   set_getEntityNormConstant,
				   EntityIdType )
{
  MonteCarlo::EstimatorHDF5FileHandler file_handler( hdf5_file_name );

  // Write the new entity norm constant
  file_handler.setEntityNormConstant<EntityIdType>( 0u, 0, 1.0 );

  double norm_constant;

  file_handler.getEntityNormConstant<EntityIdType>( 0u, 0, norm_constant );

  TEST_EQUALITY_CONST( norm_constant, 1.0 );

  // Overwrite the entity norm constant
  file_handler.setEntityNormConstant<EntityIdType>( 0u, 0, 2.0 );

  file_handler.getEntityNormConstant<EntityIdType>( 0u, 0, norm_constant );

  TEST_EQUALITY_CONST( norm_constant, 2.0 );
}

ENTITY_ID_UNIT_TEST_INSTANTIATION( EstimatorHDF5FileHandler, 
				   set_getEntityNormConstant );

//---------------------------------------------------------------------------//
// Check that an entity can be tested for existence
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( EstimatorHDF5FileHandler, 
				   isEntityAssignedToEstimator,
				   EntityIdType )
{
  MonteCarlo::EstimatorHDF5FileHandler file_handler( hdf5_file_name );

  file_handler.setEntityNormConstant<EntityIdType>( 0u, 0, 1.0 );
  file_handler.setEntityNormConstant<EntityIdType>( 0u, 1, 1.0 );
  file_handler.setEntityNormConstant<EntityIdType>( 0u, 2, 1.0 );

  TEST_ASSERT(file_handler.isEntityAssignedToEstimator<EntityIdType>( 0u, 0 ));
  TEST_ASSERT(file_handler.isEntityAssignedToEstimator<EntityIdType>( 0u, 1 ));
  TEST_ASSERT(file_handler.isEntityAssignedToEstimator<EntityIdType>( 0u, 2 ));
  TEST_ASSERT(!file_handler.isEntityAssignedToEstimator<EntityIdType>( 0u, 3));
}

ENTITY_ID_UNIT_TEST_INSTANTIATION( EstimatorHDF5FileHandler, 
				   isEntityAssignedToEstimator );

//---------------------------------------------------------------------------//
// Check that raw estimator bin data for an entity can be set
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( EstimatorHDF5FileHandler,
				   set_getRawEstimatorEntityBinData,
				   EntityIdType )
{
  MonteCarlo::EstimatorHDF5FileHandler file_handler( hdf5_file_name );

  // Write the new entity bin data
  Teuchos::Array<Utility::Pair<double,double> > raw_bin_data( 3 );
  raw_bin_data[0]( 1.0, 1.0 );
  raw_bin_data[1]( 0.0, 0.0 );
  raw_bin_data[2]( 0.5, 1.5 );
  
  file_handler.setRawEstimatorEntityBinData<EntityIdType>(0u, 0, raw_bin_data);
  
  Teuchos::Array<Utility::Pair<double,double> > raw_bin_data_copy;

  file_handler.getRawEstimatorEntityBinData<EntityIdType>( 0u,
							   0,
							   raw_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

  // Overwrite the raw bin data
  raw_bin_data[0]( 0.0, 0.0 );
  raw_bin_data[1]( 1.0, 5.5 );
  raw_bin_data[2]( 3.0, 9.2 );

  file_handler.setRawEstimatorEntityBinData<EntityIdType>(0u, 0, raw_bin_data);
  
  file_handler.getRawEstimatorEntityBinData<EntityIdType>( 0u,
							   0,
							   raw_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );
}

ENTITY_ID_UNIT_TEST_INSTANTIATION( EstimatorHDF5FileHandler,
				   set_getRawEstimatorEntityBinData );

//---------------------------------------------------------------------------//
// Check that processed estimator bin data for an entity can be set
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( EstimatorHDF5FileHandler,
				   set_getProcessedEstimatorEntityBinData,
				   EntityIdType )
{
  MonteCarlo::EstimatorHDF5FileHandler file_handler( hdf5_file_name );

  // Write the new entity bin data
  Teuchos::Array<Utility::Pair<double,double> > processed_bin_data( 3 );
  processed_bin_data[0]( 1.0, 1.0 );
  processed_bin_data[1]( 0.0, 0.0 );
  processed_bin_data[2]( 0.5, 1.5 );
  
  file_handler.setProcessedEstimatorEntityBinData<EntityIdType>( 
							   0u, 
							   0, 
							   processed_bin_data);
  
  Teuchos::Array<Utility::Pair<double,double> > processed_bin_data_copy;

  file_handler.getProcessedEstimatorEntityBinData<EntityIdType>( 
						     0u,
						     0,
						     processed_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( processed_bin_data, processed_bin_data_copy );

  // Overwrite the processed bin data
  processed_bin_data[0]( 0.0, 0.0 );
  processed_bin_data[1]( 1.0, 5.5 );
  processed_bin_data[2]( 3.0, 9.2 );

  file_handler.setProcessedEstimatorEntityBinData<EntityIdType>( 
							  0u, 
							  0, 
							  processed_bin_data );
  
  file_handler.getProcessedEstimatorEntityBinData<EntityIdType>( 
						     0u,
						     0,
						     processed_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( processed_bin_data, processed_bin_data_copy );
}

ENTITY_ID_UNIT_TEST_INSTANTIATION( EstimatorHDF5FileHandler,
				   set_getProcessedEstimatorEntityBinData );

//---------------------------------------------------------------------------//
// Check that raw estimator total data for an entity can be set
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( EstimatorHDF5FileHandler,
				   set_getRawEstimatorEntityTotalData,
				   EntityIdType )
{
  MonteCarlo::EstimatorHDF5FileHandler file_handler( hdf5_file_name );

  // Write the new entity total data
  Teuchos::Array<Utility::Quad<double,double,double,double> > 
    raw_total_data( 3 );
  raw_total_data[0]( 1.0, 1.0, 1.0, 1.0 );
  raw_total_data[1]( 0.0, 0.0, 0.0, 0.0 );
  raw_total_data[2]( 0.5, 1.5, 2.5, 4.5 );
  
  file_handler.setRawEstimatorEntityTotalData<EntityIdType>( 0u, 
							     0, 
							     raw_total_data );
  
  Teuchos::Array<Utility::Quad<double,double,double,double> > 
    raw_total_data_copy;

  file_handler.getRawEstimatorEntityTotalData<EntityIdType>( 
							 0u,
							 0,
							 raw_total_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_total_data, raw_total_data_copy );

  // Overwrite the raw total data
  raw_total_data[0]( 0.0, 0.0, 0.0, 0.0 );
  raw_total_data[1]( 1.0, 5.5, 2.4, 3.9 );
  raw_total_data[2]( 3.0, 9.2, 8.7, 6.3 );

  file_handler.setRawEstimatorEntityTotalData<EntityIdType>( 0u, 
							     0, 
							     raw_total_data );
  
  file_handler.getRawEstimatorEntityTotalData<EntityIdType>( 
							 0u,
							 0,
							 raw_total_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_total_data, raw_total_data_copy );
}

ENTITY_ID_UNIT_TEST_INSTANTIATION( EstimatorHDF5FileHandler,
				   set_getRawEstimatorEntityTotalData );

//---------------------------------------------------------------------------//
// Check that processed estimator total data for an entity can be set
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( EstimatorHDF5FileHandler,
				   set_getProcessedEstimatorEntityTotalData,
				   EntityIdType )
{
  MonteCarlo::EstimatorHDF5FileHandler file_handler( hdf5_file_name );

  // Write the new entity total data
  Teuchos::Array<Utility::Quad<double,double,double,double> > 
    processed_total_data( 3 );
  processed_total_data[0]( 1.0, 1.0, 1.0, 1.0 );
  processed_total_data[1]( 0.0, 0.0, 0.0, 0.0 );
  processed_total_data[2]( 0.5, 1.5, 2.5, 4.5 );
  
  file_handler.setProcessedEstimatorEntityTotalData<EntityIdType>( 
							0u, 
							0, 
							processed_total_data );
  
  Teuchos::Array<Utility::Quad<double,double,double,double> > 
    processed_total_data_copy;

  file_handler.getProcessedEstimatorEntityTotalData<EntityIdType>( 
						   0u,
						   0,
						   processed_total_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( processed_total_data, 
			       processed_total_data_copy );

  // Overwrite the processed total data
  processed_total_data[0]( 0.0, 0.0, 0.0, 0.0 );
  processed_total_data[1]( 1.0, 5.5, 2.4, 3.9 );
  processed_total_data[2]( 3.0, 9.2, 8.7, 6.3 );

  file_handler.setProcessedEstimatorEntityTotalData<EntityIdType>( 
							0u, 
							0, 
							processed_total_data );
  
  file_handler.getProcessedEstimatorEntityTotalData<EntityIdType>( 
						   0u,
						   0,
						   processed_total_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( processed_total_data, 
			       processed_total_data_copy );
}

ENTITY_ID_UNIT_TEST_INSTANTIATION( EstimatorHDF5FileHandler,
				   set_getProcessedEstimatorEntityTotalData );

//---------------------------------------------------------------------------//
// Check that all estimator entity data can be set and retrieved
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( EstimatorHDF5FileHandler,
				   set_get_all_entity_data,
				   EntityIdType )
{
  MonteCarlo::EstimatorHDF5FileHandler file_handler( hdf5_file_name );

  // Initialize the estimator data
  Teuchos::Array<Utility::Pair<double,double> > raw_bin_data( 3 );
  raw_bin_data[0]( 1.0, 1.0 );
  raw_bin_data[1]( 0.0, 0.0 );
  raw_bin_data[2]( 0.5, 1.5 );

  Teuchos::Array<Utility::Pair<double,double> > processed_bin_data( 3 );
  processed_bin_data[0]( 1.0, 1.0 );
  processed_bin_data[1]( 0.0, 0.0 );
  processed_bin_data[2]( 0.5, 1.5 );

  Teuchos::Array<Utility::Quad<double,double,double,double> > 
    raw_total_data( 3 );
  raw_total_data[0]( 1.0, 1.0, 1.0, 1.0 );
  raw_total_data[1]( 0.0, 0.0, 0.0, 0.0 );
  raw_total_data[2]( 0.5, 1.5, 2.5, 4.5 );

  Teuchos::Array<Utility::Quad<double,double,double,double> > 
    processed_total_data( 3 );
  processed_total_data[0]( 1.0, 1.0, 1.0, 1.0 );
  processed_total_data[1]( 0.0, 0.0, 0.0, 0.0 );
  processed_total_data[2]( 0.5, 1.5, 2.5, 4.5 );
  
  // Set the estimator data
  file_handler.setRawEstimatorEntityBinData<EntityIdType>(0u, 0, raw_bin_data);
  file_handler.setProcessedEstimatorEntityBinData<EntityIdType>( 
							   0u, 
							   0, 
							   processed_bin_data);
  file_handler.setRawEstimatorEntityTotalData<EntityIdType>( 0u, 
							     0, 
							     raw_total_data );
  file_handler.setProcessedEstimatorEntityTotalData<EntityIdType>( 
							0u, 
							0, 
							processed_total_data );
  
  // Get the estimator data back
  Teuchos::Array<Utility::Pair<double,double> > raw_bin_data_copy; 
  Teuchos::Array<Utility::Pair<double,double> > processed_bin_data_copy;
  Teuchos::Array<Utility::Quad<double,double,double,double> > 
    raw_total_data_copy;
  Teuchos::Array<Utility::Quad<double,double,double,double> > 
    processed_total_data_copy;

  file_handler.getRawEstimatorEntityBinData<EntityIdType>( 0u,
							   0,
							   raw_bin_data_copy );

  file_handler.getProcessedEstimatorEntityBinData<EntityIdType>( 
						     0u,
						     0,
						     processed_bin_data_copy );
  file_handler.getRawEstimatorEntityTotalData<EntityIdType>( 
							 0u,
							 0,
							 raw_total_data_copy );
  file_handler.getProcessedEstimatorEntityTotalData<EntityIdType>( 
						   0u,
						   0,
						   processed_total_data_copy );

  // Compare the retrieved data
  UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );
  UTILITY_TEST_COMPARE_ARRAYS( processed_bin_data, processed_bin_data_copy );
  UTILITY_TEST_COMPARE_ARRAYS( raw_total_data, raw_total_data_copy );
  UTILITY_TEST_COMPARE_ARRAYS( processed_total_data, 
			       processed_total_data_copy );
}

ENTITY_ID_UNIT_TEST_INSTANTIATION( EstimatorHDF5FileHandler,
				   set_get_all_entity_data );

//---------------------------------------------------------------------------//
// Check that raw estimator total bin data can be set
TEUCHOS_UNIT_TEST( EstimatorHDF5FileHandler, set_getRawEstimatorTotalBinData )
{
  MonteCarlo::EstimatorHDF5FileHandler file_handler( hdf5_file_name );

  // Write the new total bin data
  Teuchos::Array<Utility::Pair<double,double> > raw_total_bin_data( 3 );
  raw_total_bin_data[0]( 0.0, 0.0 );
  raw_total_bin_data[1]( 1.0, 0.5 );
  raw_total_bin_data[2]( 3.0, 2.5 );

  file_handler.setRawEstimatorTotalBinData( 0u, raw_total_bin_data );
  
  Teuchos::Array<Utility::Pair<double,double> > raw_total_bin_data_copy;

  file_handler.getRawEstimatorTotalBinData( 0u, raw_total_bin_data_copy );
  
  UTILITY_TEST_COMPARE_ARRAYS( raw_total_bin_data, raw_total_bin_data_copy );

  // Overwrite the total bin data
  raw_total_bin_data[0]( 1.0, 2.0 );
  raw_total_bin_data[1]( 0.1, 0.2 );
  raw_total_bin_data[2]( 9.0, 7.2 );

  file_handler.setRawEstimatorTotalBinData( 0u, raw_total_bin_data );
  
  file_handler.getRawEstimatorTotalBinData( 0u, raw_total_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_total_bin_data, raw_total_bin_data_copy );
}

//---------------------------------------------------------------------------// // Check that processed estimator total bin data can be set
TEUCHOS_UNIT_TEST( EstimatorHDF5FileHandler, 
		   set_getProcessedEstimatorTotalBinData )
{
  MonteCarlo::EstimatorHDF5FileHandler file_handler( hdf5_file_name );

  // Write the new total bin data
  Teuchos::Array<Utility::Pair<double,double> > processed_total_bin_data( 3 );
  processed_total_bin_data[0]( 0.0, 0.0 );
  processed_total_bin_data[1]( 1.0, 0.5 );
  processed_total_bin_data[2]( 3.0, 2.5 );

  file_handler.setProcessedEstimatorTotalBinData( 0u, 
						  processed_total_bin_data );
  
  Teuchos::Array<Utility::Pair<double,double> > processed_total_bin_data_copy;

  file_handler.getProcessedEstimatorTotalBinData( 
					       0u, 
					       processed_total_bin_data_copy );
  
  UTILITY_TEST_COMPARE_ARRAYS( processed_total_bin_data, 
			       processed_total_bin_data_copy );

  // Overwrite the total bin data
  processed_total_bin_data[0]( 1.0, 2.0 );
  processed_total_bin_data[1]( 0.1, 0.2 );
  processed_total_bin_data[2]( 9.0, 7.2 );

  file_handler.setProcessedEstimatorTotalBinData( 0u, 
						  processed_total_bin_data );
  
  file_handler.getProcessedEstimatorTotalBinData( 
					       0u, 
					       processed_total_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( processed_total_bin_data, 
			       processed_total_bin_data_copy );
}

//---------------------------------------------------------------------------// // Check that raw estimator total data can be set
TEUCHOS_UNIT_TEST( EstimatorHDF5FileHandler, set_getRawEstimatorTotalData )
{
  MonteCarlo::EstimatorHDF5FileHandler file_handler( hdf5_file_name );

  // Write the new total  data
  Teuchos::Array<Utility::Quad<double,double,double,double> > 
    raw_total_data( 3 );
  raw_total_data[0]( 0.0, 0.0, 0.0, 0.0 );
  raw_total_data[1]( 1.0, 0.5, 2.0, 1.7 );
  raw_total_data[2]( 3.0, 2.5, 3.0, 4.0 );

  file_handler.setRawEstimatorTotalData( 0u, raw_total_data );
  
  Teuchos::Array<Utility::Quad<double,double,double,double> > 
    raw_total_data_copy;

  file_handler.getRawEstimatorTotalData( 0u, raw_total_data_copy );
  
  UTILITY_TEST_COMPARE_ARRAYS( raw_total_data, raw_total_data_copy );

  // Overwrite the total  data
  raw_total_data[0]( 1.0, 2.0, 3.0, 4.0 );
  raw_total_data[1]( 0.1, 0.2, 0.3, 0.4 );
  raw_total_data[2]( 9.0, 7.2, 3.5, 2.6 );

  file_handler.setRawEstimatorTotalData( 0u, raw_total_data );
  
  file_handler.getRawEstimatorTotalData( 0u, raw_total_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_total_data, raw_total_data_copy );
}

//---------------------------------------------------------------------------// // Check that processed estimator total data can be set
TEUCHOS_UNIT_TEST( EstimatorHDF5FileHandler, 
		   set_getProcessedEstimatorTotalData )
{
  MonteCarlo::EstimatorHDF5FileHandler file_handler( hdf5_file_name );

  // Write the new total  data
  Teuchos::Array<Utility::Quad<double,double,double,double> > 
    processed_total_data( 3 );
  processed_total_data[0]( 0.0, 0.0, 0.0, 0.0 );
  processed_total_data[1]( 1.0, 0.5, 2.0, 1.7 );
  processed_total_data[2]( 3.0, 2.5, 3.0, 4.0 );

  file_handler.setProcessedEstimatorTotalData( 0u, processed_total_data );
  
  Teuchos::Array<Utility::Quad<double,double,double,double> > 
    processed_total_data_copy;

  file_handler.getProcessedEstimatorTotalData( 0u, processed_total_data_copy );
  
  UTILITY_TEST_COMPARE_ARRAYS( processed_total_data, 
			       processed_total_data_copy );

  // Overwrite the total  data
  processed_total_data[0]( 1.0, 2.0, 3.0, 4.0 );
  processed_total_data[1]( 0.1, 0.2, 0.3, 0.4 );
  processed_total_data[2]( 9.0, 7.2, 3.5, 2.6 );

  file_handler.setProcessedEstimatorTotalData( 0u, processed_total_data );
  
  file_handler.getProcessedEstimatorTotalData( 0u, processed_total_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( processed_total_data, 
			       processed_total_data_copy );
}

//---------------------------------------------------------------------------// // Check that all estimator total data can be set
TEUCHOS_UNIT_TEST( EstimatorHDF5FileHandler, set_get_all_total_data )
{
  MonteCarlo::EstimatorHDF5FileHandler file_handler( hdf5_file_name );

  // Initialize the total data
  Teuchos::Array<Utility::Pair<double,double> > raw_total_bin_data( 3 );
  raw_total_bin_data[0]( 0.0, 0.0 );
  raw_total_bin_data[1]( 1.0, 0.5 );
  raw_total_bin_data[2]( 3.0, 2.5 );

  Teuchos::Array<Utility::Pair<double,double> > processed_total_bin_data( 3 );
  processed_total_bin_data[0]( 0.0, 0.0 );
  processed_total_bin_data[1]( 1.0, 0.5 );
  processed_total_bin_data[2]( 3.0, 2.5 );

  Teuchos::Array<Utility::Quad<double,double,double,double> > 
    raw_total_data( 3 );
  raw_total_data[0]( 0.0, 0.0, 0.0, 0.0 );
  raw_total_data[1]( 1.0, 0.5, 2.0, 1.7 );
  raw_total_data[2]( 3.0, 2.5, 3.0, 4.0 );

  Teuchos::Array<Utility::Quad<double,double,double,double> > 
    processed_total_data( 3 );
  processed_total_data[0]( 0.0, 0.0, 0.0, 0.0 );
  processed_total_data[1]( 1.0, 0.5, 2.0, 1.7 );
  processed_total_data[2]( 3.0, 2.5, 3.0, 4.0 );

  // Set the total data
  file_handler.setRawEstimatorTotalBinData( 0u, raw_total_bin_data );
  file_handler.setProcessedEstimatorTotalBinData( 0u, 
						  processed_total_bin_data );
  file_handler.setRawEstimatorTotalData( 0u, raw_total_data );
  file_handler.setProcessedEstimatorTotalData( 0u, processed_total_data );
  
  // Get the total data back
  Teuchos::Array<Utility::Pair<double,double> > raw_total_bin_data_copy;
  Teuchos::Array<Utility::Pair<double,double> > processed_total_bin_data_copy;
  Teuchos::Array<Utility::Quad<double,double,double,double> > 
    raw_total_data_copy;
  Teuchos::Array<Utility::Quad<double,double,double,double> > 
    processed_total_data_copy;

  file_handler.getRawEstimatorTotalBinData( 0u, raw_total_bin_data_copy );
  file_handler.getProcessedEstimatorTotalBinData( 
					       0u, 
					       processed_total_bin_data_copy );
  file_handler.getRawEstimatorTotalData( 0u, raw_total_data_copy );
  file_handler.getProcessedEstimatorTotalData( 0u, processed_total_data_copy );
  
  // Compare the retrieved total data
  UTILITY_TEST_COMPARE_ARRAYS( raw_total_bin_data, raw_total_bin_data_copy );
  UTILITY_TEST_COMPARE_ARRAYS( processed_total_bin_data, 
			       processed_total_bin_data_copy );  
  UTILITY_TEST_COMPARE_ARRAYS( raw_total_data, raw_total_data_copy );
  UTILITY_TEST_COMPARE_ARRAYS( processed_total_data, 
			       processed_total_data_copy );
}

//---------------------------------------------------------------------------//
// end tstEstimatorHDF5FileHandler.cpp
//---------------------------------------------------------------------------//
