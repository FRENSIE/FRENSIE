//---------------------------------------------------------------------------//
//!
//! \file   EntityEstimator_def.hpp
//! \author Alex Robinson
//! \brief  Entity estimator class definition.
//!
//---------------------------------------------------------------------------//

#ifndef ENTITY_ESTIMATOR_DEF_HPP
#define ENTITY_ESTIMATOR_DEF_HPP

// FACEMC Includes
#include "ContractException.hpp"

namespace FACEMC{

// Constructor (for flux estimators)
/*! \details Flux estimators need to divide the first moment by the cell 
 * volume or surface area.
 */
template<typename EntityId>
EntityEstimator<EntityId>::EntityEstimator( 
			  const unsigned long long id,
			  const double multiplier,
			  const Teuchos::Array<EntityId>& entity_ids,
			  const Teuchos::Array<double>& entity_norm_constants )
  : Estimator( id, multiplier ),
    d_total_norm_constant( 1.0 )
{
  initializeEntityIds( entity_ids );
  initializeEntityEstimatorMomentsMap( entity_ids );
  initializeEntityNormConstantsMap( entity_ids, entity_norm_constants );

  // Calculate the total normalization constant
  calculateTotalNormalizationConstant();

  // Make sure that the maps have the same size
  testPostcondition( d_entity_ids.size() == 
		     d_entity_norm_constants_map.size() );
  testPostcondition( d_entity_ids.size() == 
		     d_entity_estimator_moments_map.size() );
}

// Constructor (for non-flux estimators)
/*! \details Non-flux estimators do not need to divide the first moment by the 
 * cell volume or surface area.
 */
template<typename EntityId>
EntityEstimator<EntityId>::EntityEstimator( 
			  const unsigned long long id,
			  const double multiplier,
			  const Teuchos::Array<EntityId>& entity_ids )
  : Estimator( id, multiplier ),
    d_total_norm_constant( 1.0 )
{
  initializeEntityIds( entity_ids );
  initializeEntityEstimatorMomentsMap( entity_ids );
  initializeEntityNormConstantsMap( entity_ids );

  // Make sure that the maps have the same size
  testPostcondition( d_entity_ids.size() == 
		     d_entity_norm_constants_map.size() );
  testPostcondition( d_entity_ids.size() == 
		     d_entity_estimator_moments_map.size() );
}

// Set the response functions
template<typename EntityId>
void EntityEstimator<EntityId>::setResponseFunctions( 
   const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_functions )
{
  Estimator::setResponseFunctions( response_functions );

  // Resize the entity estimator moment map arrays
  resizeEntityEstimatorMapArrays();
}

// Return the entity ids associated with this estimator
template<typename EntityId>
inline const typename EntityEstimator<EntityId>::EntityIdSet&
EntityEstimator<EntityId>::getEntityIds() const
{
  return d_entity_ids;
}

// Assign bin boundaries to an estimator dimension
template<typename EntityId>
void EntityEstimator<EntityId>::assignBinBoundaries(
         const Teuchos::RCP<EstimatorDimensionDiscretization>& bin_boundaries )
{
  Estimator::assignBinBoundaries( bin_boundaries );

  // Resize the entity estimator moments map arrays
  resizeEntityEstimatorMapArrays();
}

// Return the normalization constant for an entity
template<typename EntityId>
inline double EntityEstimator<EntityId>::getEntityNormConstant( 
					      const EntityId& entity_id ) const
{
  // Make sure the entity is assigned to the estimator
  testPrecondition( isEntityAssigned( entity_id ) );

  return d_entity_norm_constants_map.find( entity_id )->second;
}

// Return the total normalization constant
template<typename EntityId>
inline double EntityEstimator<EntityId>::getTotalNormConstant() const
{
  return d_total_norm_constant;
}

// Check if the entity is assigned to this estimator
template<typename EntityId>
inline bool EntityEstimator<EntityId>::isEntityAssigned( 
					      const EntityId& entity_id ) const
{
  return d_entity_ids.count( entity_id );
}

// Commit history contribution to a bin of an entity
template<typename EntityId>
void EntityEstimator<EntityId>::commitHistoryContributionToBinOfEntity(
						    const EntityId& entity_id,
						    const unsigned bin_index,
						    const double contribution )
{
  // Make sure the entity is assigned to this estimator
  testPrecondition( isEntityAssigned( entity_id ) );
  // Make sure the bin index is valid
  testPrecondition( bin_index < 
		    getNumberOfBins()*getNumberOfResponseFunctions() );
  // Make sure the contribution is valid
  testPrecondition( !ST::isnaninf( contribution ) );

  EstimatorMomentsArray& entity_estimator_moments_array = 
    d_entity_estimator_moments_map[entity_id];

  // Add the first moment contribution
  double moment_contribution = contribution;
  entity_estimator_moments_array[bin_index].first += moment_contribution;

  // Add the second moment contribution
  moment_contribution *= contribution;
  entity_estimator_moments_array[bin_index].second += moment_contribution;

  // Add the third moment contribution
  moment_contribution *= contribution;
  entity_estimator_moments_array[bin_index].third += moment_contribution;

  // Add the fourth moment contribution
  moment_contribution *= contribution;
  entity_estimator_moments_array[bin_index].fourth += moment_contribution;
}

// Print the entity ids assigned to the estimator
template<typename EntityId>
void EntityEstimator<EntityId>::printEntityIds( 
					  std::ostream& os,
					  const std::string& entity_type) const
{
  os << entity_type << " Ids: ";

  typename EntityIdSet::const_iterator entity_id, end_entity_id;
    
  entity_id = d_entity_ids.begin();
  end_entity_id = d_entity_ids.end();

  while( entity_id != end_entity_id )
  {
    os << *entity_id << " ";
    
    ++entity_id;
  }

  os << std::endl;
}

// Print the estimator data
template<typename EntityId>
void EntityEstimator<EntityId>::printImplementation( 
					 std::ostream& os,
					 const std::string& entity_type ) const
{
  // Print the entity ids that are assigned to this estimator
  printEntityIds( os, entity_type );

  // Print the response function names
  printEstimatorResponseFunctionNames( os );
  
  // Print the binning data
  printEstimatorBins( os );

  os << std::endl;
  
  // Print the estimator data for each entity
  typename EntityEstimatorMomentsArrayMap::const_iterator entity_data, 
    end_entity_data;

  entity_data = d_entity_estimator_moments_map.begin();
  end_entity_data = d_entity_estimator_moments_map.end();

  while( entity_data != end_entity_data )
  {
    os << entity_type << " " << entity_data->first 
       << " Bin Data: " << std::endl;
    os << "--------" << std::endl;

    printEstimatorBinData( os, 
			   entity_data->second,
			   getEntityNormConstant( entity_data->first ) );
    os << std::endl;

    ++entity_data;
  }
}

// Initialize entity ids and entity moment map
template<typename EntityId>
void EntityEstimator<EntityId>::initializeEntityIds( 
				   const Teuchos::Array<EntityId>& entity_ids )
{
  // Make sure there is at least one entity id
  testPrecondition( entity_ids.size() > 0 );
  
  for( unsigned i = 0; i < entity_ids.size(); ++i )
  {
    // Ignore duplicate entity ids
    if( d_entity_ids.count( entity_ids[i] ) == 0 )
    {
      d_entity_ids.insert( entity_ids[i] );
    }
    else
    {
      std::cerr << "Warning: entity id " << entity_ids[i] << "has been "
		<< "specified more than once in estimator " 
		<< getId() << ". All but the first occurrence will be ignored."
		<< std::endl;
    }
  }
}

// Initialize entity estimator moments map
template<typename EntityId>
void EntityEstimator<EntityId>::initializeEntityEstimatorMomentsMap(
				   const Teuchos::Array<EntityId>& entity_ids )
{
  // Make sure there is at least one entity id
  testPrecondition( entity_ids.size() > 0 );
  
  for( unsigned i = 0; i < entity_ids.size(); ++i )
  {
    // Ignore duplicate entity ids
    if( d_entity_estimator_moments_map.count( entity_ids[i] ) == 0 )
    {
      
      d_entity_estimator_moments_map[ entity_ids[i] ].resize( 
			    getNumberOfBins()*getNumberOfResponseFunctions() );
    }
  }
}

// Initialize the entity estimator moments map
template<typename EntityId>
void EntityEstimator<EntityId>::initializeEntityNormConstantsMap(
				   const Teuchos::Array<EntityId>& entity_ids )
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
void EntityEstimator<EntityId>::initializeEntityNormConstantsMap(
			  const Teuchos::Array<EntityId>& entity_ids,
			  const Teuchos::Array<double>& entity_norm_constants )
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

// Resize the entity estimator moments map arrays
template<typename EntityId>
void EntityEstimator<EntityId>::resizeEntityEstimatorMapArrays()
{
  typename EntityEstimatorMomentsArrayMap::iterator start, end;

  start = d_entity_estimator_moments_map.begin();
  end = d_entity_estimator_moments_map.end();

  while( start != end )
  {
    start->second.resize( getNumberOfBins()*getNumberOfResponseFunctions() );
    
    ++start;
  }
}

// Calculate the total normalization constant
template<typename EntityId>
void EntityEstimator<EntityId>::calculateTotalNormalizationConstant()
{
  typename boost::unordered_map<EntityId,double>::const_iterator norm_constant,
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

} // end FACEMC namespace

#endif // end ENTITY_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end EntityEstimator_def.hpp
//---------------------------------------------------------------------------//
