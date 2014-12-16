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
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"
#include "FRENSIE_mpi_config.hpp"

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
    d_dimension_values( 1 ),
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
    d_dimension_values( 1 ),
    d_update_tracker( 1 ),
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
  EntityEstimator<EntityId>::enableThreadSupport( num_threads );
  
  // Add thread support to update tracker
  d_update_tracker.resize( num_threads );

  // Add thread support to the dimension value map
  d_dimension_values.resize( num_threads );
}

// Reduce estimator data on all processes and collect on the root process
template<typename EntityId>
void StandardEntityEstimator<EntityId>::reduceData(
	    const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
	    const int root_process )  
{
#ifdef HAVE_FRENSIE_MPI
  // Make sure that mpi has been initialized
  remember( int mpi_initialized );
  remember( ::MPI_Initialized( &mpi_initialized ) );
  testPrecondition( mpi_initialized );
  // Make sure the comm is valid
  testPrecondition( !comm.is_null() );

  EntityEstimator<EntityId>::reduceData( comm, root_process );

  const Teuchos::MpiComm<unsigned long long>* mpi_comm = 
    dynamic_cast<const Teuchos::MpiComm<unsigned long long>* >( 
							    comm.getRawPtr() );
  
  // Only proceed to the reduce call if the comm is an mpi comm
  if( mpi_comm != NULL && comm->getSize() > 1 )
  {
    int rank = comm->getRank();
    MPI_Comm raw_mpi_comm = *(mpi_comm->getRawMpiComm());
    
    // Reduce total data for each entity
    typename EntityEstimatorMomentsArrayMap::iterator entity_data, 
      end_entity_data;
    entity_data = d_entity_total_estimator_moments_map.begin();
    end_entity_data = d_entity_total_estimator_moments_map.end();

    while( entity_data != end_entity_data )
    {
      for( unsigned i = 0; i < entity_data->second.size(); ++i )
      {
	int return_value;
	
	if( rank == root_process )
	{
	  return_value = ::MPI_Reduce( MPI_IN_PLACE,
				       &entity_data->second[i].first,
				       1,
				       MPI_DOUBLE,
				       MPI_SUM,
				       root_process,
				       raw_mpi_comm );
	}
	else
	{
	  return_value = ::MPI_Reduce( &entity_data->second[i].first,
				       NULL,
				       1,
				       MPI_DOUBLE,
				       MPI_SUM,
				       root_process,
				       raw_mpi_comm );
	}

	TEST_FOR_EXCEPTION( return_value != MPI_SUCCESS,
			    std::runtime_error,
			    "Error: unable to perform mpi reduction in "
			    "standard entity estimator " << this->getId() <<
			    " for entity " << entity_data->first <<
			    " and array index " << i << 
			    "! MPI_Reduce failed with the following error: " 
			    << return_value );

	if( rank == root_process )
	{
	  return_value = ::MPI_Reduce( MPI_IN_PLACE,
				       &entity_data->second[i].second,
				       1,
				       MPI_DOUBLE,
				       MPI_SUM,
				       root_process,
				       raw_mpi_comm );
	}
	else
	{
	  return_value = ::MPI_Reduce( &entity_data->second[i].second,
				       NULL,
				       1,
				       MPI_DOUBLE,
				       MPI_SUM,
				       root_process,
				       raw_mpi_comm );
	}

	TEST_FOR_EXCEPTION( return_value != MPI_SUCCESS,
			    std::runtime_error,
			    "Error: unable to perform mpi reduction in "
			    "standard entity estimator " << this->getId() <<
			    " for entity " << entity_data->first <<
			    " and array index " << i << 
			    "! MPI_Reduce failed with the following error: " 
			    << return_value );

	if( rank == root_process )
	{
	  return_value = ::MPI_Reduce( MPI_IN_PLACE,
				       &entity_data->second[i].third,
				       1,
				       MPI_DOUBLE,
				       MPI_SUM,
				       root_process,
				       raw_mpi_comm );
	}
	else
	{
	  return_value = ::MPI_Reduce( &entity_data->second[i].third,
				       NULL,
				       1,
				       MPI_DOUBLE,
				       MPI_SUM,
				       root_process,
				       raw_mpi_comm );
	}

	TEST_FOR_EXCEPTION( return_value != MPI_SUCCESS,
			    std::runtime_error,
			    "Error: unable to perform mpi reduction in "
			    "standard entity estimator " << this->getId() <<
			    " for entity " << entity_data->first <<
			    " and array index " << i << 
			    "! MPI_Reduce failed with the following error: " 
			    << return_value );

	if( rank == root_process )
	{
	  return_value = ::MPI_Reduce( MPI_IN_PLACE,
				       &entity_data->second[i].fourth,
				       1,
				       MPI_DOUBLE,
				       MPI_SUM,
				       root_process,
				       raw_mpi_comm );
	}
	else
	{
	  return_value = ::MPI_Reduce( &entity_data->second[i].fourth,
				       NULL,
				       1,
				       MPI_DOUBLE,
				       MPI_SUM,
				       root_process,
				       raw_mpi_comm );
	}

	TEST_FOR_EXCEPTION( return_value != MPI_SUCCESS,
			    std::runtime_error,
			    "Error: unable to perform mpi reduction in "
			    "standard entity estimator " << this->getId() <<
			    " for entity " << entity_data->first <<
			    " and array index " << i << 
			    "! MPI_Reduce failed with the following error: " 
			    << return_value );

	// Reset the data on all but the root process
	if( rank != root_process )
	  entity_data->second[i]( 0.0, 0.0, 0.0, 0.0 );

	comm->barrier();
      }

      ++entity_data;
    }

    // Reduce the total data
    for( unsigned i = 0; i < d_total_estimator_moments.size(); ++i )
    {
      int return_value;
      
      if( rank == root_process )
      {
	return_value = ::MPI_Reduce( MPI_IN_PLACE,
				     &d_total_estimator_moments[i].first,
				     1,
				     MPI_DOUBLE,
				     MPI_SUM,
				     root_process,
				     raw_mpi_comm );
      }
      else
      {
	return_value = ::MPI_Reduce( &d_total_estimator_moments[i].first,
				     NULL,
				     1,
				     MPI_DOUBLE,
				     MPI_SUM,
				     root_process,
				     raw_mpi_comm );
      }

      TEST_FOR_EXCEPTION( return_value != MPI_SUCCESS,
			  std::runtime_error,
			  "Error: unable to perform mpi reduction in "
			  "standard entity estimator " << this->getId() <<
			  " for total " << entity_data->first <<
			  " and array index " << i <<
			  "! MPI_Reduce failed with the following error: " 
			    << return_value );

      if( rank == root_process )
      {
	return_value = ::MPI_Reduce( MPI_IN_PLACE,
				     &d_total_estimator_moments[i].second,
				     1,
				     MPI_DOUBLE,
				     MPI_SUM,
				     root_process,
				     raw_mpi_comm );
      }
      else
      {
	return_value = ::MPI_Reduce( &d_total_estimator_moments[i].second,
				     NULL,
				     1,
				     MPI_DOUBLE,
				     MPI_SUM,
				     root_process,
				     raw_mpi_comm );
      }

      TEST_FOR_EXCEPTION( return_value != MPI_SUCCESS,
			  std::runtime_error,
			  "Error: unable to perform mpi reduction in "
			  "standard entity estimator " << this->getId() <<
			  " for total " << entity_data->first <<
			  " and array index " << i <<
			  "! MPI_Reduce failed with the following error: " 
			    << return_value );

      if( rank == root_process )
      {
	return_value = ::MPI_Reduce( MPI_IN_PLACE,
				     &d_total_estimator_moments[i].third,
				     1,
				     MPI_DOUBLE,
				     MPI_SUM,
				     root_process,
				     raw_mpi_comm );
      }
      else
      {
	return_value = ::MPI_Reduce( &d_total_estimator_moments[i].third,
				     NULL,
				     1,
				     MPI_DOUBLE,
				     MPI_SUM,
				     root_process,
				     raw_mpi_comm );
      }
	
      TEST_FOR_EXCEPTION( return_value != MPI_SUCCESS,
			  std::runtime_error,
			  "Error: unable to perform mpi reduction in "
			  "standard entity estimator " << this->getId() <<
			  " for total " << entity_data->first <<
			  " and array index " << i <<
			  "! MPI_Reduce failed with the following error: " 
			    << return_value );

      if( rank == root_process )
      {
	return_value = ::MPI_Reduce( MPI_IN_PLACE,
				     &d_total_estimator_moments[i].fourth,
				     1,
				     MPI_DOUBLE,
				     MPI_SUM,
				     root_process,
				     raw_mpi_comm );
      }
      else
      {
	return_value = ::MPI_Reduce( &d_total_estimator_moments[i].fourth,
				     NULL,
				     1,
				     MPI_DOUBLE,
				     MPI_SUM,
				     root_process,
				     raw_mpi_comm );
      }
	
      TEST_FOR_EXCEPTION( return_value != MPI_SUCCESS,
			  std::runtime_error,
			  "Error: unable to perform mpi reduction in "
			  "standard entity estimator " << this->getId() <<
			  " for total " << entity_data->first <<
			  " and array index " << i <<
			  "! MPI_Reduce failed with the following error: " 
			    << return_value );

      // Reset the data on all but the root process
      if( rank != root_process )
	d_total_estimator_moments[i]( 0.0, 0.0, 0.0, 0.0 );

      comm->barrier();
    }
  }    
#endif // end HAVE_FRENSIE_MPI
}

// Export the estimator data
template<typename EntityId>
void StandardEntityEstimator<EntityId>::exportData(
			   EstimatorHDF5FileHandler& hdf5_file,
			   const bool process_data ) const
{
  // Export the lower level data first
  EntityEstimator<EntityId>::exportData( hdf5_file, process_data );

  // Export the raw total data for each entity
  {
    typename EntityEstimatorMomentsArrayMap::const_iterator entity_data = 
      d_entity_total_estimator_moments_map.begin();

    while( entity_data != d_entity_total_estimator_moments_map.end() )
    {
      hdf5_file.setRawEstimatorEntityTotalData( this->getId(),
						entity_data->first,
						entity_data->second );

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

	hdf5_file.setProcessedEstimatorEntityTotalData( this->getId(),
							entity_data->first,
							processed_data );
      }
      
      ++entity_data;
    }
  }

  // Export the raw total data over all entities
  hdf5_file.setRawEstimatorTotalData( this->getId(), 
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

    hdf5_file.setProcessedEstimatorTotalData( this->getId(), processed_data );
  }
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
  // Make sure the thread id is valid
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() <
		    d_dimension_values.size() );
  // Make sure the entity is assigned to the estimator
  testPrecondition( this->isEntityAssigned( entity_id ) );
  // Make sure the particle type can contribute
  testPrecondition( this->isParticleTypeAssigned( particle.getParticleType()));
  // Make sure the contribution is valid
  testPrecondition( !ST::isnaninf( contribution ) );
  
  unsigned thread_id = Utility::GlobalOpenMPSession::getThreadId();
    
  Estimator::DimensionValueMap& thread_dimension_values = 
    d_dimension_values[thread_id];
  
  this->convertParticleStateToGenericMap( particle, 
					  angle_cosine, 
					  thread_dimension_values );
        
  // Only add the contribution if the particle state is in the phase space
  if( this->isPointInEstimatorPhaseSpace( thread_dimension_values ) )
  {
    unsigned bin_index;
      
    for( unsigned i = 0; i < this->getNumberOfResponseFunctions(); ++i )
    {
      bin_index = this->calculateBinIndex( thread_dimension_values, i );
      
      double processed_contribution = 
	contribution*this->evaluateResponseFunction( particle, i );

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

#endif // end FACEMC_STANDARD_ENTITY_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardEntityEstimator_def.hpp
//---------------------------------------------------------------------------//
