//---------------------------------------------------------------------------//
//!
//! \file   EntityEstimator_def.hpp
//! \author Alex Robinson
//! \brief  Entity estimator class definition.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ENTITY_ESTIMATOR_DEF_HPP
#define MONTE_CARLO_ENTITY_ESTIMATOR_DEF_HPP

// Std Lib Includes
#include <sstream>
#include <vector>

// Moab Includes
#include <moab/EntityHandle.hpp>

// FRENSIE Includes
#include "MonteCarlo_EstimatorHDF5FileHandler.hpp"
#include "Geometry_ModuleTraits.hpp"
#include "Utility_CommHelpers.hpp"
#include "Utility_OpenMPProperties.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( EntityEstimator<Geometry::ModuleTraits::InternalCellHandle> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( EntityEstimator<moab::EntityHandle> );

// Constructor (for flux estimators)
/*! \details Flux estimators need to divide the first moment by the cell
 * volume or surface area.
 */
template<typename EntityId>
template<template<typename,typename...> class STLCompliantArrayA,
         template<typename,typename...> class STLCompliantArrayB>
EntityEstimator<EntityId>::EntityEstimator(
                      const Estimator::idType id,
                      const double multiplier,
                      const STLCompliantArrayA<EntityId>& entity_ids,
		      const STLCompliantArrayB<double>& entity_norm_constants )
  : Estimator( id, multiplier ),
    d_total_norm_constant( 1.0 ),
    d_supplied_norm_constants( true ),
    d_estimator_total_bin_data( 1 )
{
  this->initializeEntityEstimatorMomentsMap( entity_ids );
  this->initializeEntityNormConstantsMap( entity_ids, entity_norm_constants );

  // Calculate the total normalization constant
  this->calculateTotalNormalizationConstant();

  // Initialize the total bin data
  this->resizeEstimatorTotalCollection();
}

// Constructor (for non-flux estimators)
/*! \details Non-flux estimators do not need to divide the first moment by the
 * cell volume or surface area.
 */
template<typename EntityId>
template<typename<typename,typename...> class STLCompliantArray>
EntityEstimator<EntityId>::EntityEstimator(
                                const Estimator::idType id,
                                const double multiplier,
				const STLCompliantArray<EntityId>& entity_ids )
  : Estimator( id, multiplier ),
    d_total_norm_constant( 1.0 ),
    d_supplied_norm_constants( false ),
    d_estimator_total_bin_data( 1 )
{
  this->initializeEntityEstimatorMomentsMap( entity_ids );
  this->initializeEntityNormConstantsMap( entity_ids );

  // Initialize the total bin data
  this->resizeEstimatorTotalCollection();
}

// Constructor with no entities (for mesh estimators)
template<typename EntityId>
EntityEstimator<EntityId>::EntityEstimator( const Estimator::idType id,
					    const double multiplier )
  : Estimator( id, multiplier ),
    d_total_norm_constant( 1.0 ),
    d_supplied_norm_constants( false ),
    d_estimator_total_bin_data( 1 )
{ /* ... */ }

// Return the entity ids associated with this estimator
template<typename EntityId>
template<template<typename,typename...> class STLCompliantSet>
void EntityEstimator<EntityId>::getEntityIds(
                                  STLCompliantSet<EntityId>& entity_ids ) const
{
  typename STLCompliantSet<EntityId>::const_iterator it =
    d_entity_norm_constants_map.begin();

  while( it != d_entity_norm_constants_map.end() )
  {
    entity_ids.insert( it->first );

    ++it;
  }
}

// Check if the entity is assigned to this estimator
template<typename EntityId>
inline bool EntityEstimator<EntityId>::isEntityAssigned(
					      const EntityId& entity_id ) const
{
  return d_entity_norm_constants_map.count( entity_id );
}

// Return the normalization constant for an entity
template<typename EntityId>
inline double EntityEstimator<EntityId>::getEntityNormConstant(
					      const EntityId& entity_id ) const
{
  // Make sure the entity is assigned to the estimator
  testPrecondition( this->isEntityAssigned( entity_id ) );

  return d_entity_norm_constants_map.find( entity_id )->second;
}

// Return the total normalization constant
template<typename EntityId>
inline double EntityEstimator<EntityId>::getTotalNormConstant() const
{
  return d_total_norm_constant;
}

// Reset the estimator data
template<typename EntityId>
void EntityEstimator<EntityId>::resetData()
{
  // Reset the total bin data
  d_estimator_total_bin_data.reset();

  // Reset the entity bin data
  typename EntityEstimatorMomentsCollectionMap::iterator entity_data,
    end_entity_data;
  entity_data = d_entity_estimator_moments_map.begin();
  end_entity_data = d_entity_estimator_moments_map.end();

  while( entity_data != end_entity_data )
  {
    entity_data->second->reset();

    ++entity_data;
  }
}

// Reduce estimator data on all processes and collect on the root process
template<typename EntityId>
void EntityEstimator<EntityId>::reduceData(
	    const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
	    const int root_process )
{
  // Make sure the comm is valid
  testPrecondition( !comm.is_null() );
  // Make sure the root process is valid
  testPrecondition( root_process < comm->getSize() );
  
  // Only do the reduction if there is more than one process
  if( comm->getSize() > 1 )
  {
    // Reduce bin data for each entity
    typename EntityEstimatorMomentsCollectionMap::iterator entity_data,
      end_entity_data;
    entity_data = d_entity_estimator_moments_map.begin();
    end_entity_data = d_entity_estimator_moments_map.end();

    while( entity_data != end_entity_data )
    {
      try{
        this->reduceCollection( comm, root_process, entity_data->second );
      }
      EXCEPTION_CATCH_RETHROW( std::runtime_error,
                               "unable to perform mpi reduction in entity "
                               "estimator " << this->getId() << " for entity "
                               << entity_data->first << "!" );

      ++entity_data;
    }
  }

  // Reduce bin data of total
  try{
    this->reduceCollection( comm, root_process, d_estimator_total_bin_data );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "unable to perform mpi reduction in entity "
                           "estimator " << this->getId() << " for total bin "
                           "data!" );
}

// Export the estimator data
template<typename EntityId>
void EntityEstimator<EntityId>::exportData(
                    const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file,
                    const bool process_data ) const
{
  // Export the low level estimator data
  Estimator::exportData( hdf5_file, process_data );

  // Open the estimator hdf5 file
  EstimatorHDF5FileHandler estimator_hdf5_file( hdf5_file );

  // Export the Entity norm constants
  estimator_hdf5_file.setEstimatorEntities( this->getId(),
                                            d_entity_norm_constants_map );

  // Export the total norm constant
  estimator_hdf5_file.setEstimatorTotalNormConstant( this->getId(),
                                                     d_total_norm_constant );

  // Export all of the estimator data
  {
    typename EntityEstimatorMomentsCollectionMap::const_iterator entity_data;
    unsigned i;

    for( i = 0u, entity_data = d_entity_estimator_moments_map.begin();
	 entity_data != d_entity_estimator_moments_map.end();
	 ++entity_data, ++i )
    {
      const double norm_constant =
	d_entity_norm_constants_map.find( entity_data->first )->second;

      // Export the entity norm constant
      estimator_hdf5_file.setEntityNormConstant( this->getId(),
                                                 entity_data->first,
                                                 norm_constant );

      // Export the raw entity moment data
      estimator_hdf5_file.setRawEstimatorEntityBinData( this->getId(),
                                                        entity_data->first,
                                                        entity_data->second );

      if( process_data )
      {
        std::vector<Utility::Pair<double,double> > processed_data(
						  entity_data->second.size() );

	for( unsigned j = 0; j < entity_data->second.size(); ++j )
	{

	  this->processMoments( entity_data->second,
                                j,
				norm_constant,
				Utility::get<0>( processed_data[j] ),
				Utility::get<1>( processed_data[j] ) );
	}

	estimator_hdf5_file.setProcessedEstimatorEntityBinData(
                                                            this->getId(),
                                                            entity_data->first,
                                                            processed_data );
      }
    }
  }

  // Export the total bin data
  estimator_hdf5_file.setRawEstimatorTotalBinData( this->getId(),
                                                   d_estimator_total_bin_data );

  // Export the processed total bin data
  if( process_data )
  {
    Teuchos::Array<Utility::Pair<double,double> > processed_data(
					   d_estimator_total_bin_data.size() );

    for( unsigned i = 0; i < processed_data.size(); ++i )
    {
      this->processMoments( d_estimator_total_bin_data,
                            i,
			    d_total_norm_constant,
			    Utility::get<0>( processed_data[i] ),
			    Utility::get<1>( processed_data[i] ) );
    }


    estimator_hdf5_file.setProcessedEstimatorTotalBinData( this->getId(),
                                                           processed_data );
  }
}

// Assign entities
template<typename EntityId>
void EntityEstimator<EntityId>::assignEntities(
                                   const EntityNormConstMap& entity_norm_data )
{
  // Make sure there is at least one entity
  testPrecondition( entity_norm_data.size() > 0 );

  // Reset the estimator data
  d_total_norm_constant = 1.0;
  d_supplied_norm_constants = true;
  d_estimator_total_bin_data.clear();
  d_entity_estimator_moments_map.clear();
  d_entity_norm_constants_map = entity_norm_data;

  // Initialize the entity data
  typename EntityNormConstMap::const_iterator entity, end_entity;
  entity = entity_norm_data.begin();
  end_entity = entity_norm_data.end();

  while( entity != end_entity )
  {
    d_entity_estimator_moments_map[entity->first];

    ++entity;
  }

  // Calculate the total normalization constant
  this->calculateTotalNormalizationConstant();

  // Resize the data 
  this->resizeEntityEstimatorMapCollections();
  this->resizeEstimatorTotalCollection();
}

// Assign discretization to an estimator dimension
template<typename EntityId>
void EntityEstimator<EntityId>::assignDiscretization(
      const std::shared_ptr<EstimatorDimensionDiscretization>& bin_boundaries )
{
  // Make sure only the root thread calls this
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  Estimator::assignDiscretization( bin_boundaries );

  // Resize the entity estimator moments map collections
  this->resizeEntityEstimatorMapCollections();

  // Resize the total array
  this->resizeEstimatorTotalCollection();
}

// Set the response functions
template<typename EntityId>
void EntityEstimator<EntityId>::assignResponseFunction(
                  const Estimator::ResponseFunctionPointer& response_function )
{
  Estimator::assignResponseFunction( response_functions );

  // Resize the entity estimator moment map collections
  this->resizeEntityEstimatorMapCollections();

  // Resize the total collection
  this->resizeEstimatorTotalCollection();
}

// Commit history contribution to a bin of an entity
template<typename EntityId>
void EntityEstimator<EntityId>::commitHistoryContributionToBinOfEntity(
						    const EntityId& entity_id,
						    const unsigned bin_index,
						    const double contribution )
{
  // Make sure the entity is assigned to this estimator
  testPrecondition( this->isEntityAssigned( entity_id ) );
  // Make sure the bin index is valid
  testPrecondition( bin_index <
		    this->getNumberOfBins()*
                    this->getNumberOfResponseFunctions() );

  TwoEstimatorMomentsCollection& entity_estimator_moments =
    d_entity_estimator_moments_map[entity_id];

  // Update the moments
  #pragma omp critical
  {
    d_entity_estimator_moments_map[entity_id].addRawScore( contribution );
  }
}

// Commit history contribution to a bin of the total
template<typename EntityId>
void EntityEstimator<EntityId>::commitHistoryContributionToBinOfTotal(
						   const unsigned bin_index,
						   const double contribution )
{
  // Make sure the bin index is valid
  testPrecondition( bin_index <
		    this->getNumberOfBins()*
                    this->getNumberOfResponseFunctions() );

  // Update the moments
  #pragma omp critical
  {
    d_estimator_total_bin_data.addRawScore( contribution );
  }
}

// Print the estimator data
template<typename EntityId>
void EntityEstimator<EntityId>::printImplementation(
					 std::ostream& os,
					 const std::string& entity_type ) const
{
  // Print the entity ids that are assigned to this estimator
  this->printEntityIds( os, entity_type );

  // Print the entity norm constants
  if( d_supplied_norm_constants )
    this->printEntityNormConstants( os, entity_type );

  // Print the response function names
  this->printEstimatorResponseFunctionNames( os );

  // Print the binning data
  this->printEstimatorBins( os );

  os << std::endl;

  // Print the estimator data for each entity
  // typename EntityEstimatorMomentsCollectionMap::const_iterator entity_data,
  //   end_entity_data;

  // entity_data = d_entity_estimator_moments_map.begin();
  // end_entity_data = d_entity_estimator_moments_map.end();

  // while( entity_data != end_entity_data )
  // {
  //   os << entity_type << " " << entity_data->first
  //      << " Bin Data: " << std::endl;
  //   os << "--------" << std::endl;

  //   printEstimatorBinData( os,
  //       		   entity_data->second,
  //       		   getEntityNormConstant( entity_data->first ) );
  //   os << std::endl;

  //   ++entity_data;
  // }

  // Print the estimator total bin data
  // os << " Total Bin Data: " << std::endl;
  // os << "--------" << std::endl;

  // printEstimatorBinData( os,
  //       		 d_estimator_total_bin_data,
  //       		 d_total_norm_constant );

  // os << std::endl;
}

// Print the entity ids assigned to the estimator
template<typename EntityId>
void EntityEstimator<EntityId>::printEntityIds(
					  std::ostream& os,
					  const std::string& entity_type) const
{
  os << entity_type << " Ids: ";

  typename EntityNormConstMap::const_iterator entity_id, end_entity_id;

  entity_id = d_entity_norm_constants_map.begin();
  end_entity_id = d_entity_norm_constants_map.end();

  while( entity_id != end_entity_id )
  {
    os << entity_id->first << " ";

    ++entity_id;
  }

  os << std::endl;
}

// Print the entity norm constants assigned to the estimator
template<typename EntityId>
void EntityEstimator<EntityId>::printEntityNormConstants(
					 std::ostream& os,
					 const std::string& entity_type ) const
{
  os << entity_type;

  if( entity_type == "Cell" )
    os << " Volumes: ";
  else if( entity_type == "Surface" )
    os << " Areas: ";

  typename EntityNormConstMap::const_iterator entity_id, end_entity_id;

  entity_id = d_entity_norm_constants_map.begin();
  end_entity_id = d_entity_norm_constants_map.end();

  while( entity_id != end_entity_id )
  {
    os << entity_id->second << " ";

    ++entity_id;
  }

  os << std::endl;
}

// Get the total estimator bin data
/*! \details This function breaks encapsulation and is therefore not ideal.
 * It is needed by mesh estimators for exporting data in .h5m and .vtk formats.
 */
template<typename EntityId>
const Estimator::TwoEstimatorMomentsArray&
EntityEstimator<EntityId>::getTotalBinData() const
{
  return d_estimator_total_bin_data;
}

// Get the bin data for an entity
/*! \details This function breaks encapsulation and is therefore not ideal.
 * It is needed by mesh estimators for exporting data in .h5m and .vtk formats.
 */
template<typename EntityId>
const Estimator::TwoEstimatorMomentsArray&
EntityEstimator<EntityId>::getEntityBinData( const EntityId entity_id ) const
{
  // Make sure the entity is valid
  testPrecondition( d_entity_estimator_moments_map.find( entity_id ) !=
		    d_entity_estimator_moments_map.end() );

  return d_entity_estimator_moments_map.find( entity_id )->second;
}

// Initialize entity estimator moments map
template<typename EntityId>
template<template<typename,typename...> class STLCompliantArray>
void EntityEstimator<EntityId>::initializeEntityEstimatorMomentsMap(
                                const STLCompliantArray<EntityId>& entity_ids )
{
  // Make sure there is at least one entity id
  testPrecondition( entity_ids.size() > 0 );

  for( unsigned i = 0; i < entity_ids.size(); ++i )
  {
    // Ignore duplicate entity ids
    if( d_entity_estimator_moments_map.count( entity_ids[i] ) == 0 )
    {

      d_entity_estimator_moments_map[ entity_ids[i] ].resize(
			    this->getNumberOfBins()*
                            this->getNumberOfResponseFunctions() );
    }
    else
    {
      FRENSIE_LOG_TAGGED_WARNING( "Estimator",
                                  "entity id " << entity_ids[i] <<
                                  " has been specified more than once in "
                                  "estimator " << this->getId() <<
                                  ". All but the first occurrence will be "
                                  "ignored."
    }
  }
}

// Initialize the entity estimator moments map
template<typename EntityId>
template<template<typename,typename...> class STLCompliantArray>
void EntityEstimator<EntityId>::initializeEntityNormConstantsMap(
                                const STLCompliantArray<EntityId>& entity_ids )
{
  // Make sure there is at least one entity id
  testPrecondition( entity_ids.size() > 0 );

  for( unsigned i = 0; i < entity_ids.size(); ++i )
  {
    // Ignore duplicate entity ids
    if( d_entity_norm_constants_map.count( entity_ids[i] ) == 0 )
      d_entity_norm_constants_map[ entity_ids[i] ] = 1.0;
  }
}

// Initialize the entity estimator moments map
template<typename EntityId>
template<template<typename,typename...> class STLCompliantArrayA,
         template<typename,typename...> class STLCompliantArrayB>
void EntityEstimator<EntityId>::initializeEntityNormConstantsMap(
                      const STLCompliantArrayA<EntityId>& entity_ids,
		      const STLCompliantArrayB<double>& entity_norm_constants )
{
  // Make sure there is at least one entity id
  testPrecondition( entity_ids.size() > 0 );
  // Make sure every entity id has a normalization constant
  testPrecondition( entity_ids.size() == entity_norm_constants.size() );

  for( unsigned i = 0; i < entity_ids.size(); ++i )
  {
    // Ignore duplicate entity ids
    if( d_entity_norm_constants_map.count( entity_ids[i] ) == 0 )
      d_entity_norm_constants_map[ entity_ids[i] ] = entity_norm_constants[i];
  }
}

// Calculate the total normalization constant
template<typename EntityId>
void EntityEstimator<EntityId>::calculateTotalNormalizationConstant()
{
  typename EntityNormConstMap::const_iterator norm_constant,
    end_norm_constant;

  norm_constant = d_entity_norm_constants_map.begin();
  end_norm_constant = d_entity_norm_constants_map.end();

  d_total_norm_constant = 0.0;

  while( norm_constant != end_norm_constant )
  {
    d_total_norm_constant += norm_constant->second;

    ++norm_constant;
  }
}

// Resize the entity estimator moments map collections
template<typename EntityId>
void EntityEstimator<EntityId>::resizeEntityEstimatorMapCollections()
{
  typename EntityEstimatorMomentsCollectionMap::iterator start, end;

  start = d_entity_estimator_moments_map.begin();
  end = d_entity_estimator_moments_map.end();

  while( start != end )
  {
    start->second.resize( this->getNumberOfBins()*
                          this->getNumberOfResponseFunctions() );

    ++start;
  }
}

// Resize the estimator total collection
template<typename EntityId>
void EntityEstimator<EntityId>::resizeEstimatorTotalCollection()
{
  d_estimator_total_bin_data.resize(
                this->getNumberOfBins()*this->getNumberOfResponseFunctions() );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ENTITY_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_EntityEstimator_def.hpp
//---------------------------------------------------------------------------//
