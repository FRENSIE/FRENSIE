//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardEntityEstimator_def.hpp
//! \author Alex Robinson
//! \brief  Standard entity estimator class definition.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_ENTITY_ESTIMATOR_DEF_HPP
#define MONTE_CARLO_STANDARD_ENTITY_ESTIMATOR_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_EstimatorHDF5FileHandler.hpp"
#include "Utility_CommHelpers.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_ExceptionTestMacros.hpp"
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
    d_update_tracker( 1 ),
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
    d_update_tracker( 1 ),
    d_total_estimator_moments( 1 )
{ 
  initializeMomentsMaps( entity_ids );
}

// Constructor with no entities (for mesh estimator)
template<typename EntityId>
StandardEntityEstimator<EntityId>::StandardEntityEstimator( 
				   const Estimator::idType id,
				   const double multiplier )
  : EntityEstimator<EntityId>( id, multiplier ),
    d_update_tracker( 1 ),
    d_total_estimator_moments( 1 )
{ /* ... */ }

// Set the response functions
template<typename EntityId>
void StandardEntityEstimator<EntityId>::setResponseFunctions(
                      const Teuchos::Array<std::shared_ptr<ResponseFunction> >&
                      response_functions )
{
  // Make sure only the root thread calls this
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
  EntityEstimator<EntityId>::setResponseFunctions( response_functions );

  // Resize the entity total estimator momens map arrays
  resizeEntityTotalEstimatorMomentsMapArrays();
  
  // Resize the total estimator moments array
  d_total_estimator_moments.resize( this->getNumberOfResponseFunctions() );
}

// Commit the contribution from the current history to the estimator
/*! \details This function must only be called within an omp critical block
 * if multiple threads are being used. Failure to do this may result in 
 * race conditions.
 */ 
template<typename EntityId>
void StandardEntityEstimator<EntityId>::commitHistoryContribution()
{
  // Thread id
  unsigned thread_id = Utility::GlobalOpenMPSession::getThreadId();
  
  // Number of bins per response function
  unsigned num_bins = this->getNumberOfBins();

  // Number of response functions
  unsigned num_response_funcs = this->getNumberOfResponseFunctions();

  // The entity totals
  Teuchos::Array<double> entity_totals( num_response_funcs, 0.0 );

  // The totals over all entities
  Teuchos::Array<double> totals( num_response_funcs, 0.0 );

  // The bin totals over all entities
  BinContributionMap bin_totals;

  // Get the entities with updated data
  typename SerialUpdateTracker::const_iterator entity, end_entity;
  
  getEntityIteratorFromUpdateTracker( thread_id, entity, end_entity );

  while( entity != end_entity )
  {    
    // Process each updated bin
    BinContributionMap::const_iterator bin_data, end_bin_data;
    
    getBinIteratorFromUpdateTrackerIterator( thread_id, 
					     entity, 
					     bin_data, 
					     end_bin_data );

    while( bin_data != end_bin_data )
    {
      unsigned response_func_index = 
	this->calculateResponseFunctionIndex( bin_data->first );

      double bin_contribution = bin_data->second;
      
      entity_totals[response_func_index] += bin_contribution;
      
      totals[response_func_index] += bin_contribution;
      
      if( bin_totals.find( bin_data->first ) != bin_totals.end() )
	bin_totals[bin_data->first] += bin_contribution;
      else
	bin_totals[bin_data->first] = bin_contribution;

      this->commitHistoryContributionToBinOfEntity( entity->first,
						    bin_data->first,
						    bin_contribution );

      ++bin_data;
    }

    // Commit the entity totals
    for( unsigned i = 0; i < num_response_funcs; ++i )
    {
      commitHistoryContributionToTotalOfEntity( entity->first,
						i,
						entity_totals[i] );
      
      // Reset the entity totals
      entity_totals[i] = 0.0;
    }
    
    ++entity;
  }

  // Commit the totals over all entities
  for( unsigned i = 0; i < num_response_funcs; ++i )
    commitHistoryContributionToTotalOfEstimator( i, totals[i] );

  // Commit the bin totals over all entities
  BinContributionMap::const_iterator bin_data, end_bin_data;
  bin_data = bin_totals.begin();
  end_bin_data = bin_totals.end();
  
  while( bin_data != end_bin_data )
  {
    this->commitHistoryContributionToBinOfTotal( bin_data->first,
						 bin_data->second );
    ++bin_data;    
  }
  
  // Reset the update tracker
  resetUpdateTracker( thread_id );

  // Unset the uncommitted history contribution flag
  this->unsetHasUncommittedHistoryContribution( thread_id );
}

// Enable support for multiple threads
template<typename EntityId>
void StandardEntityEstimator<EntityId>::enableThreadSupport(
						  const unsigned num_threads )
{  
  // Make sure only the root thread calls this
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
  EntityEstimator<EntityId>::enableThreadSupport( num_threads );
  
  // Add thread support to update tracker
  d_update_tracker.resize( num_threads );
}

// Reset the estimator data
/*! 
 */
template<typename EntityId>
void StandardEntityEstimator<EntityId>::resetData()
{
  // Make sure only the root thread calls this
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
  EntityEstimator<EntityId>::resetData();

  // Reset the total moments
  for( unsigned i = 0; i < d_total_estimator_moments.size(); ++i )
    d_total_estimator_moments[i]( 0.0, 0.0, 0.0, 0.0 );

  // Reset the entity total moments
  typename EntityEstimatorMomentsArrayMap::iterator entity_data, 
    end_entity_data;
  entity_data = d_entity_total_estimator_moments_map.begin();
  end_entity_data = d_entity_total_estimator_moments_map.end();

  while( entity_data != end_entity_data )
  {
    for( unsigned i = 0; i < entity_data->second.size(); ++i )
      entity_data->second[i]( 0.0, 0.0, 0.0, 0.0 );
    
    ++entity_data;
  }

  // Reset the update tracker
  for( unsigned i = 0; i < d_update_tracker.size(); ++i )
  {
    d_update_tracker[i].clear();
    
    this->unsetHasUncommittedHistoryContribution( i );
  }
}

// Reduce estimator data on all processes and collect on the root process
template<typename EntityId>
void StandardEntityEstimator<EntityId>::reduceData(
	    const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
	    const int root_process )  
{
  // Make sure only the root thread calls this
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  // Make sure the comm is valid
  testPrecondition( !comm.is_null() );
  // Make sure the root process is valid
  testPrecondition( root_process < comm->getSize() );

  // Only do the reduction if there is more than one process
  if( comm->getSize() > 1 )
  {
    // Reduce the bin data first
    EntityEstimator<EntityId>::reduceData( comm, root_process );

    // Reduce total data for each entity
    typename EntityEstimatorMomentsArrayMap::iterator entity_data, 
      end_entity_data;
    entity_data = d_entity_total_estimator_moments_map.begin();
    end_entity_data = d_entity_total_estimator_moments_map.end();

    while( entity_data != end_entity_data )
    {
      for( unsigned i = 0; i < entity_data->second.size(); ++i )
      {
	double first_reduced_value, second_reduced_value,
          third_reduced_value, fourth_reduced_value;

        try{
          Teuchos::reduceAll( *comm,
                              Teuchos::REDUCE_SUM,
                              entity_data->second[i].first,
                              Teuchos::inOutArg( first_reduced_value ) );

          Teuchos::reduceAll( *comm,
                              Teuchos::REDUCE_SUM,
                              entity_data->second[i].second,
                              Teuchos::inOutArg( second_reduced_value ) );

          Teuchos::reduceAll( *comm,
                              Teuchos::REDUCE_SUM,
                              entity_data->second[i].third,
                              Teuchos::inOutArg( third_reduced_value ) );

          Teuchos::reduceAll( *comm,
                              Teuchos::REDUCE_SUM,
                              entity_data->second[i].fourth,
                              Teuchos::inOutArg( fourth_reduced_value ) );
        }
        EXCEPTION_CATCH_RETHROW(
                               std::runtime_error,
                               "Error: unable to perform mpi reduction in "
                               "standard entity estimator " << this->getId() <<
                               " for entity " << entity_data->first <<
                               " and array index " << i << "!" );
        
	// Reset the data on all but the root process
	if( comm->getRank() == root_process )
        {
          entity_data->second[i]( first_reduced_value,
                                  second_reduced_value,
                                  third_reduced_value,
                                  fourth_reduced_value );
        }
        else
          entity_data->second[i]( 0.0, 0.0, 0.0, 0.0 );

	comm->barrier();
      }

      ++entity_data;
    }

    // Reduce the total data
    for( unsigned i = 0; i < d_total_estimator_moments.size(); ++i )
    {
      double first_reduced_value, second_reduced_value,
          third_reduced_value, fourth_reduced_value;
      
      try{
        Teuchos::reduceAll( *comm,
                            Teuchos::REDUCE_SUM,
                            d_total_estimator_moments[i].first,
                            Teuchos::inOutArg( first_reduced_value ) );

        Teuchos::reduceAll( *comm,
                            Teuchos::REDUCE_SUM,
                            d_total_estimator_moments[i].second,
                            Teuchos::inOutArg( second_reduced_value ) );

        Teuchos::reduceAll( *comm,
                            Teuchos::REDUCE_SUM,
                            d_total_estimator_moments[i].third,
                            Teuchos::inOutArg( third_reduced_value ) );

        Teuchos::reduceAll( *comm,
                            Teuchos::REDUCE_SUM,
                            d_total_estimator_moments[i].fourth,
                            Teuchos::inOutArg( fourth_reduced_value ) );
      }
      EXCEPTION_CATCH_RETHROW( std::runtime_error,
                               "Error: unable to perform mpi reduction in "
                               "standard entity estimator " << this->getId() <<
                               " for total " << entity_data->first <<
                               " and array index " << i << "!" );

      // Reset the data on all but the root process
      if( comm->getRank() == root_process )
      {
        d_total_estimator_moments[i]( first_reduced_value,
                                      second_reduced_value,
                                      third_reduced_value,
                                      fourth_reduced_value );
      }
      else
	d_total_estimator_moments[i]( 0.0, 0.0, 0.0, 0.0 );

      comm->barrier();
    }
  }
}


// Export the estimator data
template<typename EntityId>
void StandardEntityEstimator<EntityId>::exportData(
                   const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file,
                   const bool process_data ) const
{
  // Make sure only the root thread calls this
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
  // Export the lower level data first
  EntityEstimator<EntityId>::exportData( hdf5_file, process_data );

  // Open the estimator hdf5 file
  EstimatorHDF5FileHandler estimator_hdf5_file( hdf5_file );

  // Export the raw total data for each entity
  {
    typename EntityEstimatorMomentsArrayMap::const_iterator entity_data = 
      d_entity_total_estimator_moments_map.begin();

    while( entity_data != d_entity_total_estimator_moments_map.end() )
    {
      estimator_hdf5_file.setRawEstimatorEntityTotalData( this->getId(),
                                                          entity_data->first,
                                                          entity_data->second);

      if( process_data )
      {
	Teuchos::Array<Utility::Quad<double,double,double,double> > 
	  processed_data( entity_data->second.size() );
	
	for( unsigned i = 0; i < processed_data.size(); ++i )
	{
	  this->processMoments( 
			     entity_data->second[i],
			     this->getEntityNormConstant( entity_data->first ),
			     processed_data[i].first,
			     processed_data[i].second,
			     processed_data[i].third,
			     processed_data[i].fourth );
	}

	estimator_hdf5_file.setProcessedEstimatorEntityTotalData( 
                                                            this->getId(),
                                                            entity_data->first,
                                                            processed_data );
      }
      
      ++entity_data;
    }
  }

  // Export the raw total data over all entities
  estimator_hdf5_file.setRawEstimatorTotalData( this->getId(), 
                                                d_total_estimator_moments );

  // Export the processed total data over all entities
  if( process_data )
  {
    Teuchos::Array<Utility::Quad<double,double,double,double> > processed_data(
					    d_total_estimator_moments.size() );

    for( unsigned i = 0; i < d_total_estimator_moments.size(); ++i )
    {
      this->processMoments( d_total_estimator_moments[i],
			    this->getTotalNormConstant(),
			    processed_data[i].first,
			    processed_data[i].second,
			    processed_data[i].third,
			    processed_data[i].fourth );
    }

    estimator_hdf5_file.setProcessedEstimatorTotalData( this->getId(), 
                                                        processed_data );
  }
}

// Assign entities
template<typename EntityId>
void StandardEntityEstimator<EntityId>::assignEntities(
		const boost::unordered_map<EntityId,double>& entity_norm_data )
{
  // Make sure there is at least one entity
  testPrecondition( entity_norm_data.size() > 0 );

  EntityEstimator<EntityId>::assignEntities( entity_norm_data );
  
  // Reset the estimator data
  d_total_estimator_moments.clear();
  d_entity_total_estimator_moments_map.clear();

  // Initialize the entity data
  typename boost::unordered_map<EntityId,double>::const_iterator entity, 
    end_entity;
  entity = entity_norm_data.begin();
  end_entity = entity_norm_data.end();

  while( entity != end_entity )
  {
    d_entity_total_estimator_moments_map[entity->first];

    ++entity;
  }

  // Resize the entity total estimator momens map arrays
  resizeEntityTotalEstimatorMomentsMapArrays();
  
  // Resize the total estimator moments array
  d_total_estimator_moments.resize( this->getNumberOfResponseFunctions() );
}

// Add estimator contribution from a portion of the current history
/*! \details The contribution should incorporate the particle weight (and
 * possibly other multiplier(s) ) but not the response function values.
 */
template<typename EntityId>
void StandardEntityEstimator<EntityId>::addPartialHistoryContribution( 
		   const EntityId entity_id,
		   const EstimatorParticleStateWrapper& particle_state_wrapper,
                   const double contribution )
{
  // Make sure the thread id is valid
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() <
		    d_update_tracker.size() );
  // Make sure the entity is assigned to the estimator
  testPrecondition( this->isEntityAssigned( entity_id ) );
  // Make sure the particle type can contribute
  testPrecondition( this->isParticleTypeAssigned( 
               particle_state_wrapper.getParticleState().getParticleType() ) );
  // Make sure the contribution is valid
  testPrecondition( !ST::isnaninf( contribution ) );
  
  unsigned thread_id = Utility::GlobalOpenMPSession::getThreadId();
    
  // Only add the contribution if the particle state is in the phase space
  if( this->isPointInEstimatorPhaseSpace( particle_state_wrapper ) )
  {
    unsigned bin_index;
      
    for( unsigned i = 0; i < this->getNumberOfResponseFunctions(); ++i )
    {
      bin_index = this->calculateBinIndex( particle_state_wrapper, i );
      
      double processed_contribution = 
        contribution*this->evaluateResponseFunction( 
                                particle_state_wrapper.getParticleState(), i );

      addInfoToUpdateTracker( thread_id, 
			      entity_id, 
			      bin_index,
			      processed_contribution );
    }

    // Indicate that there is an uncommitted history contribution
    this->setHasUncommittedHistoryContribution( thread_id );
  }
}

// Print the estimator data
template<typename EntityId>
void StandardEntityEstimator<EntityId>::printImplementation( 
					 std::ostream& os,
					 const std::string& entity_type ) const
{
  // Make sure only the root thread calls this
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
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

// Get the total estimator data
/*! \details This function breaks encapsulation and is therefore not ideal.
 * It is needed by mesh estimators for exporting data in .h5m and .vtk formats.
 */
template<typename EntityId>
const Estimator::FourEstimatorMomentsArray&
StandardEntityEstimator<EntityId>::getTotalData() const
{
  return d_total_estimator_moments;
}

// Get the total data for an entity
/*! \details This function breaks encapsulation and is therefore not ideal.
 * It is needed by mesh estimators for exporting data in .h5m and .vtk formats.
 */
template<typename EntityId>
const Estimator::FourEstimatorMomentsArray&
StandardEntityEstimator<EntityId>::getEntityTotalData( 
					       const EntityId entity_id ) const
{
  // Make sure the entity is valid
  testPrecondition( d_entity_total_estimator_moments_map.find( entity_id ) !=
		    d_entity_total_estimator_moments_map.end() );
  
  return d_entity_total_estimator_moments_map.find( entity_id )->second;
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
  
  #pragma omp atomic update
  entity_total_estimator_moments_array[response_function_index].first += 
    moment_contribution;

  // Add the second moment contribution
  moment_contribution *= contribution;

  #pragma omp atomic update
  entity_total_estimator_moments_array[response_function_index].second +=
    moment_contribution;

  // Add the third moment contribution
  moment_contribution *= contribution;

  #pragma omp atomic update
  entity_total_estimator_moments_array[response_function_index].third +=
    moment_contribution;

  // Add the fourth moment contribution
  moment_contribution *= contribution;

  #pragma omp atomic update
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

  #pragma omp atomic update
  d_total_estimator_moments[response_function_index].first += 
    moment_contribution;

  // Add the second moment contribution
  moment_contribution *= contribution;

  #pragma omp atomic update
  d_total_estimator_moments[response_function_index].second +=
    moment_contribution;

  // Add the third moment contribution
  moment_contribution *= contribution;

  #pragma omp atomic update
  d_total_estimator_moments[response_function_index].third +=
    moment_contribution;

  // Add the fourth moment contribution
  moment_contribution *= contribution;
  
  #pragma omp atomic update
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
    if( d_entity_total_estimator_moments_map.count( entity_ids[i] ) == 0 )
    {
      d_entity_total_estimator_moments_map[ entity_ids[i] ].resize(
				        this->getNumberOfResponseFunctions() );
    }
  }
}

// Add info to update tracker
template<typename EntityId>
void StandardEntityEstimator<EntityId>::addInfoToUpdateTracker( 
						    const unsigned thread_id,
						    const EntityId entity_id,
						    const unsigned bin_index,
						    const double contribution )
{
  // Make sure the thread id is valid
  testPrecondition( thread_id < d_update_tracker.size() );
  
  BinContributionMap& thread_entity_bin_contribution_map = 
    d_update_tracker[thread_id][entity_id];

  if( thread_entity_bin_contribution_map.find( bin_index ) !=
      thread_entity_bin_contribution_map.end() )
    thread_entity_bin_contribution_map[bin_index] += contribution;
  else
    thread_entity_bin_contribution_map[bin_index] = contribution;
}

// Get the bin iterator from an update tracker iterator
template<typename EntityId>
inline void 
StandardEntityEstimator<EntityId>::getEntityIteratorFromUpdateTracker( 
	      const unsigned thread_id,
	      typename SerialUpdateTracker::const_iterator& start_entity,
	      typename SerialUpdateTracker::const_iterator& end_entity ) const
{
  // Make sure the thread is is valid
  testPrecondition( thread_id < d_update_tracker.size() );

  start_entity = d_update_tracker[thread_id].begin();
  end_entity = d_update_tracker[thread_id].end();
}

// Get the bin iterator from an update tracker iterator
template<typename EntityId>
inline void 
StandardEntityEstimator<EntityId>::getBinIteratorFromUpdateTrackerIterator(
	   const unsigned thread_id,
	   const typename SerialUpdateTracker::const_iterator& entity_iterator,
	   BinContributionMap::const_iterator& start_bin,
	   BinContributionMap::const_iterator& end_bin ) const
{
  // Make sure the thread id is valid
  testPrecondition( thread_id < d_update_tracker.size() );
  // Make sure the entity iterator is valid
  testPrecondition( entity_iterator != d_update_tracker[thread_id].end() );

  start_bin = entity_iterator->second.begin();
  end_bin = entity_iterator->second.end();
}

// Reset the update tracker
template<typename EntityId>
void StandardEntityEstimator<EntityId>::resetUpdateTracker( 
						     const unsigned thread_id )
{
  d_update_tracker[thread_id].clear();
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_ENTITY_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardEntityEstimator_def.hpp
//---------------------------------------------------------------------------//
