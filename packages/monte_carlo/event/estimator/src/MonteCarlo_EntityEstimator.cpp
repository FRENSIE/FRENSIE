//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EntityEstimator.cpp
//! \author Alex Robinson
//! \brief  The Entity estimator class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_EntityEstimator.hpp"
#include "Utility_OpenMPProperties.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default constructor
EntityEstimator::EntityEstimator()
{ /* ... */ }

// Constructor with no entities (for mesh estimators)
EntityEstimator::EntityEstimator( const Id id,
                                  const double multiplier )
  : Estimator( id, multiplier ),
    d_total_norm_constant( 1.0 ),
    d_supplied_norm_constants( false ),
    d_estimator_total_bin_data( 1 )
{ /* ... */ }

// Return the entity ids associated with this estimator
void EntityEstimator::getEntityIds( std::set<EntityId>& entity_ids ) const
{
  for( auto&& entity_data : d_entity_norm_constants_map )
    entity_ids.insert( entity_data.first );
}
// Check if the entity is assigned to this estimator
bool EntityEstimator::isEntityAssigned( const EntityId entity_id ) const
{
  return d_entity_norm_constants_map.find( entity_id ) !=
    d_entity_norm_constants_map.end();
}

// Return the normalization constant for an entity
double EntityEstimator::getEntityNormConstant( const EntityId entity_id ) const
{
  // Make sure the entity is assigned to the estimator
  testPrecondition( this->isEntityAssigned( entity_id ) );

  return d_entity_norm_constants_map.find( entity_id )->second;
}

// Return the total normalization constant
double EntityEstimator::getTotalNormConstant() const
{
  return d_total_norm_constant;
}

// Get the total estimator bin data first moments
Utility::ArrayView<const double> EntityEstimator::getTotalBinDataFirstMoments() const
{
  return Utility::ArrayView<const double>(
                    Utility::getCurrentScores<1>( d_estimator_total_bin_data ),
                    d_estimator_total_bin_data.size() );
}

// Get the total estimator bin data second moments
Utility::ArrayView<const double> EntityEstimator::getTotalBinDataSecondMoments() const
{
  return Utility::ArrayView<const double>(
                    Utility::getCurrentScores<2>( d_estimator_total_bin_data ),
                    d_estimator_total_bin_data.size() );
}

// Get the bin data first moments for an entity
Utility::ArrayView<const double> EntityEstimator::getEntityBinDataFirstMoments( const EntityId entity_id ) const
{
  // Make sure the entity is assigned to the estimator
  testPrecondition( this->isEntityAssigned( entity_id ) );

  const TwoEstimatorMomentsCollection& entity_collection =
    d_entity_estimator_moments_map.find( entity_id )->second;

  return Utility::ArrayView<const double>(
                             Utility::getCurrentScores<1>( entity_collection ),
                             entity_collection.size() );
}
// Get the bin data second moments for an entity
Utility::ArrayView<const double> EntityEstimator::getEntityBinDataSecondMoments( const EntityId entity_id ) const
{
  // Make sure the entity is assigned to the estimator
  testPrecondition( this->isEntityAssigned( entity_id ) );

  const TwoEstimatorMomentsCollection& entity_collection =
    d_entity_estimator_moments_map.find( entity_id )->second;

  return Utility::ArrayView<const double>(
                             Utility::getCurrentScores<2>( entity_collection ),
                             entity_collection.size() );
}

// Reset the estimator data
void EntityEstimator::resetData()
{
  // Reset the total bin data
  d_estimator_total_bin_data.reset();

  // Reset the entity bin data
  for( auto&& entity_data : d_entity_estimator_moments_map )
    entity_data.second.reset();
}

// Reduce estimator data on all processes and collect on the root process
void EntityEstimator::reduceData( const Utility::Communicator& comm,
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

  Estimator::reduceData( comm, root_process );
}

// Assign entities
void EntityEstimator::assignEntities(
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
void EntityEstimator::assignDiscretization(
  const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>& bins,
  const bool range_dimension )
{
  // Make sure only the root thread calls this
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  Estimator::assignDiscretization( bins, range_dimension );

  // Resize the entity estimator moments map collections
  this->resizeEntityEstimatorMapCollections();

  // Resize the total array
  this->resizeEstimatorTotalCollection();
}

// Set the response functions
void EntityEstimator::assignResponseFunction(
             const std::shared_ptr<const ParticleResponse>& response_function )
{
  Estimator::assignResponseFunction( response_function );

  // Resize the entity estimator moment map collections
  this->resizeEntityEstimatorMapCollections();

  // Resize the total collection
  this->resizeEstimatorTotalCollection();
}

// Commit history contribution to a bin of an entity
void EntityEstimator::commitHistoryContributionToBinOfEntity(
						    const EntityId entity_id,
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
void EntityEstimator::commitHistoryContributionToBinOfTotal(
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
void EntityEstimator::printImplementation(
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
  this->printEstimatorDiscretization( os );

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
void EntityEstimator::printEntityIds( std::ostream& os,
                                      const std::string& entity_type) const
{
  os << entity_type << " Ids: ";

  for( auto&& entity_data : d_entity_norm_constants_map )
    os << entity_data.first << " ";

  os << "\n";
}

// Print the entity norm constants assigned to the estimator
void EntityEstimator::printEntityNormConstants(
					 std::ostream& os,
					 const std::string& entity_type ) const
{
  os << entity_type;

  if( entity_type == "Cell" )
    os << " Volumes: ";
  else if( entity_type == "Surface" )
    os << " Areas: ";

  for( auto&& entity_data : d_entity_norm_constants_map )
    os << Utility::toString(entity_data.second) << " ";

  os << "\n";
}

// Get the total estimator bin data
/*! \details This function breaks encapsulation and is therefore not ideal.
 * It is needed by mesh estimators for exporting data in .h5m and .vtk formats.
 */
const Estimator::TwoEstimatorMomentsCollection&
EntityEstimator::getTotalBinData() const
{
  return d_estimator_total_bin_data;
}

// Get the bin data for an entity
/*! \details This function breaks encapsulation and is therefore not ideal.
 * It is needed by mesh estimators for exporting data in .h5m and .vtk formats.
 */
const Estimator::TwoEstimatorMomentsCollection&
EntityEstimator::getEntityBinData( const EntityId entity_id ) const
{
  // Make sure the entity is valid
  testPrecondition( d_entity_estimator_moments_map.find( entity_id ) !=
		    d_entity_estimator_moments_map.end() );

  return d_entity_estimator_moments_map.find( entity_id )->second;
}

// Calculate the total normalization constant
void EntityEstimator::calculateTotalNormalizationConstant()
{
  d_total_norm_constant = 0.0;

  for( auto&& entity_data : d_entity_norm_constants_map )
    d_total_norm_constant += entity_data.second;
}

// Resize the entity estimator moments map collections
void EntityEstimator::resizeEntityEstimatorMapCollections()
{
  for( auto&& entity_data : d_entity_estimator_moments_map )
  {
    entity_data.second.resize( this->getNumberOfBins()*
                               this->getNumberOfResponseFunctions() );
  }
}

// Resize the estimator total collection
void EntityEstimator::resizeEstimatorTotalCollection()
{
  d_estimator_total_bin_data.resize(
                this->getNumberOfBins()*this->getNumberOfResponseFunctions() );
}

EXPLICIT_CLASS_SERIALIZE_INST( EntityEstimator );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_EntityEstimator.cpp
//---------------------------------------------------------------------------//
