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
#include "Geometry_Model.hpp"
#include "Utility_CommHelpers.hpp"
#include "Utility_OpenMPProperties.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Default constructor
template<typename EntityId>
EntityEstimator<EntityId>::EntityEstimator()
{ /* ... */ }
  
// Constructor (for flux estimators)
/*! \details Flux estimators need to divide the first moment by the cell
 * volume or surface area.
 */
template<typename EntityId>
EntityEstimator<EntityId>::EntityEstimator(
                      const Estimator::idType id,
                      const double multiplier,
                      const std::vector<EntityId>& entity_ids,
		      const std::vector<double>& entity_norm_constants )
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
EntityEstimator<EntityId>::EntityEstimator(
                                      const Estimator::idType id,
                                      const double multiplier,
				      const std::vector<EntityId>& entity_ids )
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
void EntityEstimator<EntityId>::getEntityIds(
                                        std::vector<size_t>& entity_ids ) const
{
  for( auto&& entity_data : d_entity_norm_constants_map )
    entity_ids.insert( entity_data.first );
}

// Check if the entity is assigned to this estimator
template<typename EntityId>
inline bool EntityEstimator<EntityId>::isEntityAssigned(
					      const size_t& entity_id ) const
{
  return d_entity_norm_constants_map.find( entity_id ) !=
    d_entity_norm_constants_map.end();
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

// Get the total estimator bin data first moments
template<typename EntityId>
Utility::ArrayView<const double> EntityEstimator<EntityId>::getTotalBinDataFirstMoments() const
{
  return Utility::ArrayView<const double>(
                    Utility::getCurrentScores<1>( d_estimator_total_bin_data ),
                    d_estimator_total_bin_data.size() );
}

// Get the total estimator bin data second moments
template<typename EntityId>
Utility::ArrayView<const double> EntityEstimator<EntityId>::getTotalBinDataSecondMoments() const
{
  return Utility::ArrayView<const double>(
                    Utility::getCurrentScores<2>( d_estimator_total_bin_data ),
                    d_estimator_total_bin_data.size() );
}

// Get the bin data first moments for an entity
template<typename EntityId>
Utility::ArrayView<const double> EntityEstimator<EntityId>::getEntityBinDataFirstMoments( const size_t entity_id ) const
{
  // Make sure the entity is assigned to the estimator
  testPrecondition( this->isEntityAssigned( entity_id ) );

  const TwoEstimatorMomentsCollection& entity_collection =
    d_entity_estimator_moments_map.find( entity_id )->second;

  return Utility::ArrayView<const double>(
                             Utility::getCurrentScores<1>( entity_collection ),
                             entity_collections.size() );
}

// Get the bin data second moments for an entity
template<typename EntityId>
Utility::ArrayView<const double> EntityEstimator<EntityId>::getEntityBinDataSecondMoments( const size_t entity_id ) const
{
  // Make sure the entity is assigned to the estimator
  testPrecondition( this->isEntityAssigned( entity_id ) );

  const TwoEstimatorMomentsCollection& entity_collection =
    d_entity_estimator_moments_map.find( entity_id )->second;

  return Utility::ArrayView<const double>(
                             Utility::getCurrentScores<2>( entity_collection ),
                             entity_collections.size() );
}

// Reset the estimator data
template<typename EntityId>
void EntityEstimator<EntityId>::resetData()
{
  // Reset the total bin data
  d_estimator_total_bin_data.reset();

  // Reset the entity bin data
  for( auto&& entity_data : d_entity_estimator_moments_map )
    entity_data.second->reset();
}

// Reduce estimator data on all processes and collect on the root process
template<typename EntityId>
void EntityEstimator<EntityId>::reduceData( const Utility::Communicator& comm,
                                            const int root_process )
{
  // Make sure the root process is valid
  testPrecondition( root_process < comm.size() );
  
  // Only do the reduction if there is more than one process
  if( comm.size() > 1 )
  {
    try{
      // Gather all of the entity data on the root process
      if( comm.rank() == root_process )
      {
        std::vector<EntityEstimatorMomentsCollectionMap>
          gathered_entity_data( comm.size() );
        
        Utility::gather( comm,
                         d_entity_estimator_moments_map,
                         gathered_entity_data,
                         root_process );
        
        // Reduce the data that was on each process
        for( auto&& entity_data : d_entity_estimator_moments_map )
        {
          // Don't double count data on this process (j starts from 1)
          for( size_t j = 1; j < gathered_entity_data.size(); ++j )
          {
            const EntityEstimatorMomentsCollectionMap::value_type&
              other_entity_data = *gathered_entity_data[j].find( entity_data.first );
          
            for( size_t i = 0; i < entity_data.second.size(); ++i )
            {
              Utility::getCurrentScore<1>( entity_data.second, i ) +=
                Utility::getCurrentScore<1>( other_entity_data.second, i );
            
              Utility::getCurrentScore<2>( entity_data.second, i ) +=
                Utility::getCurrentScore<2>( other_entity_data.second, i );
            }
          }
        }
      }
      else
      {
        Utility::gather( comm,
                         d_entity_estimator_moments_map,
                         root_process );
      }
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Unable to perform mpi reduction in entity bin "
                             "estimator " << this->getId() << " for entity "
                             "bin data!" );

    comm.barrier();
    
    // Reduce bin data of total
    try{
      this->reduceCollection( comm, root_process, d_estimator_total_bin_data );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Unable to perform mpi reduction in entity "
                             "estimator " << this->getId() << " for total bin "
                             "data!" );
  }

  Estimator::reduce( comm, root_process );
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
  for( auto&& entity_data : entity_norm_data )
    d_entity_estimator_moments_map[entity_data.first];

  // Calculate the total normalization constant
  this->calculateTotalNormalizationConstant();

  // Resize the data 
  this->resizeEntityEstimatorMapCollections();
  this->resizeEstimatorTotalCollection();
}

// Assign discretization to an estimator dimension
template<typename EntityId>
void EntityEstimator<EntityId>::assignDiscretization(
  const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>& bins,
  const bool range_dimension )
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
             const std::shared_ptr<const ParticleResponse>& response_function )
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
						    const size_t bin_index,
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
    d_entity_estimator_moments_map[entity_id].addRawScore( bin_index, contribution );
  }
}

// Commit history contribution to a bin of the total
template<typename EntityId>
void EntityEstimator<EntityId>::commitHistoryContributionToBinOfTotal(
						   const size_t bin_index,
						   const double contribution )
{
  // Make sure the bin index is valid
  testPrecondition( bin_index <
		    this->getNumberOfBins()*
                    this->getNumberOfResponseFunctions() );

  // Update the moments
  #pragma omp critical
  {
    d_estimator_total_bin_data.addRawScore( bin_index, contribution );
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

  os << "\n";

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

  for( auto&& entity_data : d_entity_norm_constants_map )
    os << entity_id.first << " ";

  os << "\n";
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

  for( auto&& entity_data : d_entity_norm_constants_map )
    os << Utility::toString(entity_id.second) << " ";

  os << "\n"
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
void EntityEstimator<EntityId>::initializeEntityEstimatorMomentsMap(
                                      const std::vector<EntityId>& entity_ids )
{
  // Make sure there is at least one entity id
  testPrecondition( entity_ids.size() > 0 );

  for( size_t i = 0; i < entity_ids.size(); ++i )
  {
    // Ignore duplicate entity ids
    if( d_entity_estimator_moments_map.count( entity_ids[i] ) == 0 )
    {
      d_entity_estimator_moments_map[entity_ids[i]].resize(
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
void EntityEstimator<EntityId>::initializeEntityNormConstantsMap(
                                      const std::vector<EntityId>& entity_ids )
{
  // Make sure there is at least one entity id
  testPrecondition( entity_ids.size() > 0 );

  for( size_t i = 0; i < entity_ids.size(); ++i )
  {
    // Ignore duplicate entity ids
    if( d_entity_norm_constants_map.count( entity_ids[i] ) == 0 )
      d_entity_norm_constants_map[ entity_ids[i] ] = 1.0;
  }
}

// Initialize the entity estimator moments map
template<typename EntityId>
void EntityEstimator<EntityId>::initializeEntityNormConstantsMap(
                             const std::vector<EntityId>& entity_ids,
                             const std::vector<double>& entity_norm_constants )
{
  // Make sure there is at least one entity id
  testPrecondition( entity_ids.size() > 0 );
  // Make sure every entity id has a normalization constant
  testPrecondition( entity_ids.size() == entity_norm_constants.size() );

  for( size_t i = 0; i < entity_ids.size(); ++i )
  {
    // Ignore duplicate entity ids
    if( d_entity_norm_constants_map.count( entity_ids[i] ) == 0 )
      d_entity_norm_constants_map[entity_ids[i]] = entity_norm_constants[i];
  }
}

// Calculate the total normalization constant
template<typename EntityId>
void EntityEstimator<EntityId>::calculateTotalNormalizationConstant()
{
  d_total_norm_constant = 0.0;

  for( auto&& entity_data : d_entity_norm_constants_map )
    d_total_norm_constant += entity_data.second;
}

// Resize the entity estimator moments map collections
template<typename EntityId>
void EntityEstimator<EntityId>::resizeEntityEstimatorMapCollections()
{
  for( auto&& entity_data : d_entity_estimator_moments_map )
  {
    entity_data.second.resize( this->getNumberOfBins()*
                               this->getNumberOfResponseFunctions() );
  }
}

// Resize the estimator total collection
template<typename EntityId>
void EntityEstimator<EntityId>::resizeEstimatorTotalCollection()
{
  d_estimator_total_bin_data.resize(
                this->getNumberOfBins()*this->getNumberOfResponseFunctions() );
}

// Serialize the entity estimator
template<typename EntityId>
template<typename Archive>
void EntityEstimator<EntityId>::serialize( Archive& ar, const unsigned version )
{
  // Serialize the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( Estimator );

  // Serialize the local data
  ar & BOOST_SERIALIZATION_NVP( d_total_norm_constant );
  ar & BOOST_SERIALIZATION_NVP( d_supplied_norm_constants );
  ar & BOOST_SERIALIZATION_NVP( d_estimator_total_bin_data );
  ar & BOOST_SERIALIZATION_NVP( d_entity_estimator_moments_map );
  ar & BOOST_SERIALIZATION_NVP( d_entity_norm_constants_map );
}

} // end MonteCarlo namespace

BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS1( EntityEstimator, MonteCarlo );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::EntityEstimator<Geometry::Model::InternalCellHandle> );
EXTERN_EXPLICIT_MONTE_CARLO_CLASS_SERIALIZATION_INST( MonteCarlo::EntityEstimator<Geometry::Model::InternalCellHandle> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::EntityEstimator<size_t> );
EXTERN_EXPLICIT_MONTE_CARLO_CLASS_SERIALIZATION_INST( MonteCarlo::EntityEstimator<size_t> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::EntityEstimator<moab::EntityHandle> );
EXTERN_EXPLICIT_MONTE_CARLO_CLASS_SERIALIZATION_INST( MonteCarlo::EntityEstimator<moab::EntityHandle> );

#endif // end MONTE_CARLO_ENTITY_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_EntityEstimator_def.hpp
//---------------------------------------------------------------------------//
