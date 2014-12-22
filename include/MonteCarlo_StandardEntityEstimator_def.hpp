//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardEntityEstimator_def.hpp
//! \author Alex Robinson
//! \brief  Standard entity estimator class definition.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_STANDARD_ENTITY_ESTIMATOR_DEF_HPP
#define FACEMC_STANDARD_ENTITY_ESTIMATOR_DEF_HPP

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor (for flux estimators)
template<typename EntityId>
StandardEntityEstimator<EntityId>::StandardEntityEstimator( 
			  const Estimator::idType id,
			  const double multiplier,
			  const Teuchos::Array<EntityId>& entity_ids,
			  const Teuchos::Array<double>& entity_norm_constants )
  : EntityEstimator<EntityId>( id,
			       multiplier,
			       entity_ids,
			       entity_norm_constants ),
    d_total_estimator_moments( 1 )
    
{
  initializeMomentsMaps( entity_ids );
}

// Constructor (for non-flux estimators)
template<typename EntityId>
StandardEntityEstimator<EntityId>::StandardEntityEstimator( 
				   const Estimator::idType id,
				   const double multiplier,
			           const Teuchos::Array<EntityId>& entity_ids )
  : EntityEstimator<EntityId>( id, multiplier, entity_ids ),
    d_total_estimator_moments( 1 )
{
  initializeMomentsMaps( entity_ids );
}

// Set the response functions
template<typename EntityId>
void StandardEntityEstimator<EntityId>::setResponseFunctions(
    const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_functions )
{
  EntityEstimator<EntityId>::setResponseFunctions( response_functions );

  // Resize the entity estimator first moment map arrays
  resizeEntityEstimatorFirstMomentsMapArrays();

  // Resize the entity total estimator momens map arrays
  resizeEntityTotalEstimatorMomentsMapArrays();
  
  // Resize the total estimator moments array
  d_total_estimator_moments.resize( this->getNumberOfResponseFunctions() );
}

// Commit the contribution from the current history to the estimator
template<typename EntityId>
void StandardEntityEstimator<EntityId>::commitHistoryContribution()
{
  // Number of bins per response function
  unsigned num_bins = this->getNumberOfBins();
  
  typename EntityEstimatorFirstMomentsArrayMap::iterator entity, end_entity;
  
  for( unsigned i = 0; i < this->getNumberOfResponseFunctions(); ++i )
  {
    double total_over_all_entities = 0.0;
    
    entity = d_entity_current_history_first_moments_map.begin();
    end_entity = d_entity_current_history_first_moments_map.end();
    
    while( entity != end_entity )
    {
      double total_over_entity = 0.0;
      
      for( unsigned j = 0; j < num_bins; ++j )
      {
	unsigned bin_index = j + num_bins*i;
	
	double bin_contribution = entity->second[bin_index];

	total_over_entity += bin_contribution;
	
	total_over_all_entities += bin_contribution;
	
	this->commitHistoryContributionToBinOfEntity( entity->first,
						      bin_index,
						      bin_contribution );
	
	// Reset the bin
	entity->second[bin_index] = 0.0;
      }
      
      commitHistoryContributionToTotalOfEntity( entity->first,
						i,
						total_over_entity );
      
      ++entity;
    }
    
    commitHistoryContributionToTotalOfEstimator( i, total_over_all_entities );
    
    // Unset the uncommitted history contribution boolean
    this->unsetHasUncommittedHistoryContribution();
  }
}

// Assign bin boundaries to an estimator dimension
template<typename EntityId>
void StandardEntityEstimator<EntityId>::assignBinBoundaries(
	 const Teuchos::RCP<EstimatorDimensionDiscretization>& bin_boundaries )
{
  EntityEstimator<EntityId>::assignBinBoundaries( bin_boundaries );

  // Resize the first moment map arrays
  resizeEntityEstimatorFirstMomentsMapArrays();
}

// Add estimator contribution from a portion of the current history
/*! \details The contribution should incorporate the particle weight (and
 * possibly other multiplier(s) ) but not the response function values.
 */
template<typename EntityId>
void StandardEntityEstimator<EntityId>::addPartialHistoryContribution( 
					    const EntityId entity_id,
					    const ParticleState& particle,
					    const double angle_cosine,
					    const double contribution )
{
  // Make sure the entity is assigned to the estimator
  testPrecondition( this->isEntityAssigned( entity_id ) );
  // Make sure the particle type can contribute
  testPrecondition( this->isParticleTypeAssigned( particle.getParticleType()));
  // Make sure the contribution is valid
  testPrecondition( !ST::isnaninf( contribution ) );
  
  this->convertParticleStateToGenericMap( particle, 
					  angle_cosine, 
					  d_dimension_values );
        
  // Only add the contribution if the particle state is in the phase space
  if( this->isPointInEstimatorPhaseSpace( d_dimension_values ) )
  {
    Teuchos::Array<double>& entity_first_moments_array = 
      d_entity_current_history_first_moments_map[entity_id];
  
    unsigned bin_index;
      
    for( unsigned i = 0; i < this->getNumberOfResponseFunctions(); ++i )
    {
      bin_index = this->calculateBinIndex( d_dimension_values, i );
      
      entity_first_moments_array[bin_index] += 
	contribution*this->evaluateResponseFunction( particle, i );
    }
  }

  // Indicate that there is an uncommitted history contribution
  this->setHasUncommittedHistoryContribution();
}

// Print the estimator data
template<typename EntityId>
void StandardEntityEstimator<EntityId>::printImplementation( 
					 std::ostream& os,
					 const std::string& entity_type ) const
{
  EntityEstimator<EntityId>::printImplementation( os, entity_type );

  // Print the entity total estimator data
  typename EntityEstimatorMomentsArrayMap::const_iterator 
    entity_id, end_entity_id;

  entity_id = d_entity_total_estimator_moments_map.begin();
  end_entity_id = d_entity_total_estimator_moments_map.end();
  
  while( entity_id != end_entity_id )
  {
    os << entity_type << " " << entity_id->first << " Total Data: "<<std::endl;
    os << "--------" << std::endl;
      
    this->printEstimatorTotalData( 
		             os,
			     entity_id->second,
		             this->getEntityNormConstant( entity_id->first ) );
    
    os << std::endl;

    ++entity_id;
  }

  // Print the total estimator data
  os << "All " << entity_type << "s Total Data: " << std::endl;
  os << "--------" << std::endl;

  this->printEstimatorTotalData( os,
				 d_total_estimator_moments,
				 this->getTotalNormConstant() );
}

// Resize the entity estimator first moment map arrays
template<typename EntityId>
void 
StandardEntityEstimator<EntityId>::resizeEntityEstimatorFirstMomentsMapArrays()
{
  typename EntityEstimatorFirstMomentsArrayMap::iterator start, end;
  
  start = d_entity_current_history_first_moments_map.begin();
  end = d_entity_current_history_first_moments_map.end();

  while( start != end )
  {
    start->second.resize( this->getNumberOfBins()*
			  this->getNumberOfResponseFunctions() );
    ++start;
  }
}

// Resize the entity total estimator moments map arrays
template<typename EntityId>
void 
StandardEntityEstimator<EntityId>::resizeEntityTotalEstimatorMomentsMapArrays()
{
  typename EntityEstimatorMomentsArrayMap::iterator 
    start, end;

  start = d_entity_total_estimator_moments_map.begin();
  end = d_entity_total_estimator_moments_map.end();

  while( start != end )
  {
    start->second.resize( this->getNumberOfResponseFunctions() );
    
    ++start;
  }
}

// Commit hist. contr. to the total for a response function of an entity
template<typename EntityId>
void 
StandardEntityEstimator<EntityId>::commitHistoryContributionToTotalOfEntity(
					const EntityId& entity_id,
					const unsigned response_function_index,
					const double contribution )
{
  // Make sure the entity is assigned to this estimator
  testPrecondition( this->isEntityAssigned( entity_id ) );
  // Make sure the response function index is valid
  testPrecondition( response_function_index < 
		    this->getNumberOfResponseFunctions() );
  // Make sure the contribution is valid
  testPrecondition( !ST::isnaninf( contribution ) );

  Estimator::FourEstimatorMomentsArray& entity_total_estimator_moments_array = 
    d_entity_total_estimator_moments_map[entity_id];

  // Add the first moment contribution
  double moment_contribution = contribution;
  entity_total_estimator_moments_array[response_function_index].first += 
    moment_contribution;

  // Add the second moment contribution
  moment_contribution *= contribution;
  entity_total_estimator_moments_array[response_function_index].second +=
    moment_contribution;

  // Add the third moment contribution
  moment_contribution *= contribution;
  entity_total_estimator_moments_array[response_function_index].third +=
    moment_contribution;

  // Add the fourth moment contribution
  moment_contribution *= contribution;
  entity_total_estimator_moments_array[response_function_index].fourth +=
    moment_contribution;
}

// Commit history contr. to the total for a response function of an estimator
template<typename EntityId>
void 
StandardEntityEstimator<EntityId>::commitHistoryContributionToTotalOfEstimator(
					const unsigned response_function_index,
					const double contribution )
{
  // Make sure the response function index is valid
  testPrecondition( response_function_index < 
		    this->getNumberOfResponseFunctions() );
  // Make sure the contribution is valid
  testPrecondition( !ST::isnaninf( contribution ) );

  // Add the first moment contribution
  double moment_contribution = contribution;
  d_total_estimator_moments[response_function_index].first += 
    moment_contribution;

  // Add the second moment contribution
  moment_contribution *= contribution;
  d_total_estimator_moments[response_function_index].second +=
    moment_contribution;

  // Add the third moment contribution
  moment_contribution *= contribution;
  d_total_estimator_moments[response_function_index].third +=
    moment_contribution;

  // Add the fourth moment contribution
  moment_contribution *= contribution;
  d_total_estimator_moments[response_function_index].fourth +=
    moment_contribution;
}

// Initialize the moments maps
template<typename EntityId>
void StandardEntityEstimator<EntityId>::initializeMomentsMaps(
				   const Teuchos::Array<EntityId>& entity_ids )
{
  // Set up the entity maps
  for( unsigned i = 0; i < entity_ids.size(); ++i )
  {
    // Ignore duplicate entity ids
    if( d_entity_current_history_first_moments_map.count( entity_ids[i] ) == 0)
    {
      d_entity_total_estimator_moments_map[ entity_ids[i] ].resize( 
					this->getNumberOfResponseFunctions() );
      
      d_entity_current_history_first_moments_map[ entity_ids[i] ].resize(
		this->getNumberOfBins()*this->getNumberOfResponseFunctions() );
    }
  }
}

} // end MonteCarlo namespace

#endif // end FACEMC_STANDARD_ENTITY_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardEntityEstimator_def.hpp
//---------------------------------------------------------------------------//
