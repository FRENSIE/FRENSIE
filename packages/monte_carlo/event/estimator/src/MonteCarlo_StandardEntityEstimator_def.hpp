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
#include "Utility_OpenMPProperties.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Default constructor
template<typename EntityId>
StandardEntityEstimator<EntityId>::StandardEntityEstimator()
{ /* ... */ }

// Constructor (for flux estimators)
template<typename EntityId>
StandardEntityEstimator<EntityId>::StandardEntityEstimator(
                             const Estimator::idType id,
                             const double multiplier,
                             const std::vector<EntityId>& entity_ids,
                             const std::vector<double>& entity_norm_constants )
  : BaseEstimatorType( id,
                       multiplier,
                       entity_ids,
                       entity_norm_constants ),
    d_total_estimator_moments( 1 ),
    d_update_tracker( 1 )
{
  this->initializeMomentsMaps( entity_ids );
}

// Constructor (for non-flux estimators)
template<typename EntityId>
StandardEntityEstimator<EntityId>::StandardEntityEstimator(
                                      const Estimator::idType id,
                                      const double multiplier,
			              const std::vector<EntityId>& entity_ids )
  : BaseEstimatorType( id, multiplier, entity_ids ),
    d_total_estimator_moments( 1 ),
    d_update_tracker( 1 )
{
  this->initializeMomentsMaps( entity_ids );
}

// Constructor with no entities (for mesh estimator)
template<typename EntityId>
StandardEntityEstimator<EntityId>::StandardEntityEstimator(
                                                    const Estimator::idType id,
                                                    const double multiplier )
  : BaseEstimatorType( id, multiplier ),
    d_total_estimator_moments( 1 ),
    d_update_tracker( 1 )
{ /* ... */ }

// Check if total data is available
template<typename EntityId>
bool StandardEntityEstimator<EntityId>::isTotalDataAvailable() const
{
  return true;
}

// Get the total data first moments
template<typename EntityId>
Utility::ArrayView<const double> StandardEntityEstimator<EntityId>::getTotalDataFirstMoments() const
{
  return Utility::ArrayView<const double>(
                     Utility::getCurrentScores<1>( d_total_estimator_moments ),
                     d_total_estimator_moments.size() );
}

// Get the total data second moments
template<typename EntityId>
Utility::ArrayView<const double> StandardEntityEstimator<EntityId>::getTotalDataSecondMoments() const
{
  return Utility::ArrayView<const double>(
                     Utility::getCurrentScores<2>( d_total_estimator_moments ),
                     d_total_estimator_moments.size() );
}

// Get the total data third moments
template<typename EntityId>
Utility::ArrayView<const double> StandardEntityEstimator<EntityId>::getTotalDataThirdMoments() const
{
  return Utility::ArrayView<const double>(
                     Utility::getCurrentScores<3>( d_total_estimator_moments ),
                     d_total_estimator_moments.size() );
}

// Get the total data fourth moments
template<typename EntityId>
Utility::ArrayView<const double> StandardEntityEstimator<EntityId>::getTotalDataFourthMoments() const
{
  return Utility::ArrayView<const double>(
                     Utility::getCurrentScores<4>( d_total_estimator_moments ),
                     d_total_estimator_moments.size() );
}

// Get the total data first moments for an entity
template<typename EntityId>
Utility::ArrayView<const double> StandardEntityEstimator<EntityId>::getEntityTotalDataFirstMoments( const size_t entity_id ) const
{
  // Make sure the entity is assigned to the estimator
  testPrecondition( this->isEntityAssigned( entity_id ) );
  
  const Estimator::FourEstimatorMomentsCollection& entity_collection =
    d_entity_total_estimator_moments_map.find( entity_id )->second;

  return Utility::ArrayView<const double>(
                             Utility::getCurrentScores<1>( entity_collection ),
                             entity_collection.size() );
}

// Get the total data second moments for an entity
template<typename EntityId>
Utility::ArrayView<const double> StandardEntityEstimator<EntityId>::getEntityTotalDataSecondMoments( const size_t entity_id ) const
{
  // Make sure the entity is assigned to the estimator
  testPrecondition( this->isEntityAssigned( entity_id ) );
  
  const Estimator::FourEstimatorMomentsCollection& entity_collection =
    d_entity_total_estimator_moments_map.find( entity_id )->second;

  return Utility::ArrayView<const double>(
                             Utility::getCurrentScores<2>( entity_collection ),
                             entity_collection.size() );
}

// Get the total data third moments for an entity
template<typename EntityId>
Utility::ArrayView<const double> StandardEntityEstimator<EntityId>::getEntityTotalDataThirdMoments( const size_t entity_id ) const
{
  // Make sure the entity is assigned to the estimator
  testPrecondition( this->isEntityAssigned( entity_id ) );
  
  const Estimator::FourEstimatorMomentsCollection& entity_collection =
    d_entity_total_estimator_moments_map.find( entity_id )->second;

  return Utility::ArrayView<const double>(
                             Utility::getCurrentScores<3>( entity_collection ),
                             entity_collection.size() );
}

// Get the total data fourth moments for an entity
template<typename EntityId>
Utility::ArrayView<const double> StandardEntityEstimator<EntityId>::getEntityTotalDataFourthMoments( const size_t entity_id ) const
{
  // Make sure the entity is assigned to the estimator
  testPrecondition( this->isEntityAssigned( entity_id ) );
  
  const Estimator::FourEstimatorMomentsCollection& entity_collection =
    d_entity_total_estimator_moments_map.find( entity_id )->second;

  return Utility::ArrayView<const double>(
                             Utility::getCurrentScores<4>( entity_collection ),
                             entity_collection.size() );
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
  size_t thread_id = Utility::OpenMPProperties::getThreadId();

  // Number of bins per response function
  size_t num_bins = this->getNumberOfBins();

  // Number of response functions
  size_t num_response_funcs = this->getNumberOfResponseFunctions();

  // The entity totals
  std::vector<double> entity_totals( num_response_funcs, 0.0 );

  // The totals over all entities
  std::vector<double> totals( num_response_funcs, 0.0 );

  // The bin totals over all entities
  BinContributionMap bin_totals;

  // Get the entities with updated data
  typename SerialUpdateTracker::const_iterator entity, end_entity;

  this->getEntityIteratorFromUpdateTracker( thread_id, entity, end_entity );

  while( entity != end_entity )
  {
    // Process each updated bin
    BinContributionMap::const_iterator bin_data, end_bin_data;

    this->getBinIteratorFromUpdateTrackerIterator( thread_id,
                                                   entity,
                                                   bin_data,
                                                   end_bin_data );

    while( bin_data != end_bin_data )
    {
      size_t response_func_index =
	this->calculateResponseFunctionIndex( bin_data->first );

      const double bin_contribution = bin_data->second;

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
    for( size_t i = 0; i < num_response_funcs; ++i )
    {
      this->commitHistoryContributionToTotalOfEntity( entity->first,
                                                      i,
                                                      entity_totals[i] );

      // Reset the entity totals
      entity_totals[i] = 0.0;
    }

    ++entity;
  }

  // Commit the totals over all entities
  for( size_t i = 0; i < num_response_funcs; ++i )
    this->commitHistoryContributionToTotalOfEstimator( i, totals[i] );

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
  this->resetUpdateTracker( thread_id );

  // Unset the uncommitted history contribution flag
  this->unsetHasUncommittedHistoryContribution( thread_id );
}

// Enable support for multiple threads
template<typename EntityId>
void StandardEntityEstimator<EntityId>::enableThreadSupport(
                                                     const size_t num_threads )
{
  // Make sure only the root thread calls this
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  BaseEstimatorType::enableThreadSupport( num_threads );

  // Add thread support to update tracker
  d_update_tracker.resize( num_threads );
}

// Reset the estimator data
template<typename EntityId>
void StandardEntityEstimator<EntityId>::resetData()
{
  // Make sure only the root thread calls this
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  BaseEstimatorType::resetData();

  // Reset the total moments
  d_total_estimator_moments.reset();

  // Reset the entity total moments
  for( auto&& entity_data : d_entity_total_estimator_moments_map )
    entity_data.second.reset();

  // Reset the update tracker
  for( size_t i = 0; i < d_update_tracker.size(); ++i )
  {
    d_update_tracker[i].clear();

    this->unsetHasUncommittedHistoryContribution( i );
  }
}

// Reduce estimator data on all processes and collect on the root process
template<typename EntityId>
void StandardEntityEstimator<EntityId>::reduceData(
                                             const Utility::Communicator& comm,
                                             const int root_process )
{
  // Make sure only the root thread calls this
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );
  // Make sure the root process is valid
  testPrecondition( root_process < comm.size() );

  // Only do the reduction if there is more than one process
  if( comm.size() > 1 )
  {
    try{
      // Gather all of the total data of each entity
      if( comm.rank() == root_process )
      {
        std::vector<EntityEstimatorMomentsCollectionMap>
          gathered_entity_data( comm.size() );

        Utility::gather( comm,
                         d_entity_total_estimator_moments_map,
                         gathered_entity_data,
                         root_process );

        // Reduce the data that was on each process
        for( auto&& entity_data : d_entity_total_estimator_moments_map )
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

              Utility::getCurrentScore<3>( entity_data.second, i ) +=
                Utility::getCurrentScore<3>( other_entity_data.second, i );

              Utility::getCurrentScore<4>( entity_data.second, i ) +=
                Utility::getCurrentScore<4>( other_entity_data.second, i );
            }
          }
        }
      }
      else
      {
        Utility::gather( comm,
                         d_entity_total_estimator_moments_map,
                         root_process );
      } 
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Unable to perform mpi reduction in "
                             "standard entity estimator " << this->getId() <<
                             " for entity total data!" );

    comm.barrier();
    
    // Reduce the total data
    try{
      this->reduceCollection( comm, root_process, d_total_estimator_moments );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Unable to perform mpi reduction in "
                             "standard entity estimator " << this->getId() <<
                             " for total data!" );
  }

  // Reduce the bin data
  BaseEstimatorType::reduceData( comm, root_process );
}

// Assign entities
template<typename EntityId>
void StandardEntityEstimator<EntityId>::assignEntities(
                          const typename BaseEstimatorType::EntityNormConstMap&
                          entity_norm_data )
{
  // Make sure there is at least one entity
  testPrecondition( entity_norm_data.size() > 0 );

  BaseEstimatorType::assignEntities( entity_norm_data );

  // Reset the estimator data
  d_total_estimator_moments.clear();
  d_entity_total_estimator_moments_map.clear();

  // Initialize the entity data
  for( auto&& entity_data : entity_norm_data )
    d_entity_total_estimator_moments_map[entity_data.first];

  // Resize the entity total estimator momens map collections
  this->resizeEntityTotalEstimatorMomentsMapCollections();

  // Resize the total estimator moments array
  d_total_estimator_moments.resize( this->getNumberOfResponseFunctions() );
}

// Set the response functions
template<typename EntityId>
void StandardEntityEstimator<EntityId>::assignResponseFunction(
             const std::shared_ptr<const ParticleResponse>& response_function )
{
  // Make sure only the root thread calls this
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  BaseEstimatorType::setResponseFunction( response_function );

  // Resize the entity total estimator momens map collections
  this->resizeEntityTotalEstimatorMomentsMapCollections();

  // Resize the total estimator moments array
  d_total_estimator_moments.resize( this->getNumberOfResponseFunctions() );
}

// Print the estimator data
template<typename EntityId>
void StandardEntityEstimator<EntityId>::printImplementation(
					 std::ostream& os,
					 const std::string& entity_type ) const
{
  // Make sure only the root thread calls this
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  BaseEstimatorType::printImplementation( os, entity_type );

  // Print the entity total estimator data
  for( auto&& : d_entity_total_estimator_moments_map )
  {
    os << entity_type << " " << entity_id.first << " Total Data:\n";
    os << "--------\n";

    this->printEstimatorTotalData(
		              os,
                              entity_id.second,
		              this->getEntityNormConstant( entity_id.first ) );

    os << "\n";
  }

  // Print the total estimator data
  os << "All " << entity_type << "s Total Data:\n";
  os << "--------\n";

  this->printEstimatorTotalData( os,
				 d_total_estimator_moments,
				 this->getTotalNormConstant() );

  os << std::flush;
}

// Add estimator contribution from a point of the current history
/*! \details The contribution should incorporate the particle weight (and
 * possibly other multiplier(s) ) but not the response function values.
 */
template<typename EntityId>
void StandardEntityEstimator<EntityId>::addPartialHistoryPointContribution(
		   const EntityId entity_id,
		   const EstimatorParticleStateWrapper& particle_state_wrapper,
                   const double contribution )
{
  // Make sure the thread id is valid
  testPrecondition( Utility::OpenMPProperties::getThreadId() <
		    d_update_tracker.size() );
  // Make sure the entity is assigned to the estimator
  testPrecondition( this->isEntityAssigned( entity_id ) );
  // Make sure that the particle type is assigned
  testPrecondition( this->isParticleTypeAssigned( particle_state_wrapper.getParticleState().getParticleType() ) );
  
  const size_t thread_id = Utility::OpenMPProperties::getThreadId();
    
  // Only add the contribution if the particle state is in the phase space
  if( this->isPointInEstimatorPhaseSpace( particle_state_wrapper ) )
  {
    typename ObserverPhaseSpaceDimensionDiscretization::BinIndexArray
      bin_indices;

    for( size_t r = 0; r < this->getNumberOfResponseFunctions(); ++r )
    {
      this->calculateBinIndicesOfPoint( particle_state_wrapper,
                                        r,
                                        bin_indices );
      
      const double processed_contribution = contribution*
        this->evaluateResponseFunction(
                                particle_state_wrapper.getParticleState(), r );

      for( size_t i = 0; i < bin_indices.size(); ++i )
      {
        this->addInfoToUpdateTracker( thread_id,
                                      entity_id,
                                      bin_indices[i],
                                      processed_contribution );
      }
      
      bin_indices.clear();
    }
  }

  // Indicate that there is an uncommitted history contribution
  if( !this->hasUncommittedHistoryContribution( thread_id ) )
    this->setHasUncommittedHistoryContribution( thread_id );
}

// Add estimator contribution from a range of the current history
/*! \details The contribution should incorporate the particle weight (and
 * possibly other multiplier(s) ) but not the response function values.
 */
template<typename EntityId>
template<ObserverPhaseSpaceDimensions... RangeDimensions>
void StandardEntityEstimator<EntityId>::addPartialHistoryRangeContribution(
                   const EntityId entity_id,
                   const EstimatorParticleStateWrapper& particle_state_wrapper,
                   const double contribution )
{
  // Make sure the thread id is valid
  testPrecondition( Utility::OpenMPProperties::getThreadId() <
		    d_update_tracker.size() );
  // Make sure the entity is assigned to the estimator
  testPrecondition( this->isEntityAssigned( entity_id ) );
  // Make sure that the particle type is assigned
  testPrecondition( this->isParticleTypeAssigned( particle_state_wrapper.getParticleState().getParticleType() ) );
  
  const size_t thread_id = Utility::OpenMPProperties::getThreadId();
    
  // Only add the contribution if the particle state is in the phase space
  if( this->doesRangeIntersectEstimatorPhaseSpace( particle_state_wrapper ) )
  {
    typename ObserverPhaseSpaceDimensionDiscretization::BinIndexWeightPairArray
      bin_indices_and_weights;

    for( size_t r = 0; r < this->getNumberOfResponseFunctions(); ++r )
    {
      this->calculateBinIndicesAndWeightsOfRange( particle_state_wrapper,
                                                  r,
                                                  bin_indices_and_weights );

      for( size_t i = 0; i < bin_indices_and_weights.size(); ++i )
      {
        const double processed_contribution = contribution*
          Utility::get<1>( bin_indices_and_weights[i] )*
          this->evaluateResponseFunction(
                                particle_state_wrapper.getParticleState(), r );
                  
        this->addInfoToUpdateTracker( thread_id,
                                      entity_id,
                                      bin_indices_and_weights[i],
                                      processed_contribution );
      }

      bin_indices_and_weights.clear();
    }
  }

  // Indicate that there is an uncommitted history contribution
  if( !this->hasUncommittedHistoryContribution( thread_id ) )
    this->setHasUncommittedHistoryContribution( thread_id );
}

// Get the total estimator data
/*! \details This function breaks encapsulation and is therefore not ideal.
 * It is needed by mesh estimators for exporting data in .h5m and .vtk formats.
 */
template<typename EntityId>
const Estimator::FourEstimatorMomentsCollection&
StandardEntityEstimator<EntityId>::getTotalData() const
{
  return d_total_estimator_moments;
}

// Get the total data for an entity
/*! \details This function breaks encapsulation and is therefore not ideal.
 * It is needed by mesh estimators for exporting data in .h5m and .vtk formats.
 */
template<typename EntityId>
const Estimator::FourEstimatorMomentsCollection&
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
void StandardEntityEstimator<EntityId>::resizeEntityTotalEstimatorMomentsMapArrays()
{
  typename EntityEstimatorMomentsCollectionMap::iterator
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
void StandardEntityEstimator<EntityId>::commitHistoryContributionToTotalOfEntity(
					const EntityId& entity_id,
					const unsigned response_function_index,
					const double contribution )
{
  // Make sure the entity is assigned to this estimator
  testPrecondition( this->isEntityAssigned( entity_id ) );
  // Make sure the response function index is valid
  testPrecondition( response_function_index <
		    this->getNumberOfResponseFunctions() );
  
  Estimator::FourEstimatorMomentsCollection&
    entity_total_estimator_moments_collection =
    d_entity_total_estimator_moments_map[entity_id];

  // Update the moments 
  #pragma omp critical
  {
    entity_total_estimator_moments_collection.addRawScore( response_function_index, constribution );
  }
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
  testPrecondition( !Utility::QuantityTraits<double>::isnaninf( contribution ) );

  // Update the moments
  #pragma omp critical
  {
    d_total_estimator_moments.addRawScore( response_function_index, contribution );
  }
}

// Initialize the moments maps
template<typename EntityId>
void StandardEntityEstimator<EntityId>::initializeMomentsMaps(
                                      const std::vector<EntityId>& entity_ids )
{
  // Set up the entity maps
  for( size_t i = 0; i < entity_ids.size(); ++i )
  {
    // Ignore duplicate entity ids
    if( d_entity_total_estimator_moments_map.find( entity_ids[i] ) ==
        d_entity_total_estimator_moments_map.end() )
    {
      d_entity_total_estimator_moments_map[ entity_ids[i] ].resize(
				        this->getNumberOfResponseFunctions() );
    }
  }
}

// Add info to update tracker
template<typename EntityId>
void StandardEntityEstimator<EntityId>::addInfoToUpdateTracker(
						    const size_t thread_id,
						    const EntityId entity_id,
						    const size_t bin_index,
						    const double contribution )
{
  // Make sure the thread id is valid
  testPrecondition( thread_id < d_update_tracker.size() );

  BinContributionMap& thread_entity_bin_contribution_map =
    d_update_tracker[thread_id][entity_id];

  BinContributionMap::iterator entity_bin_data =
    thread_entity_bin_contribution_map.find( bin_index );
  
  if( entity_bin_data != thread_entity_bin_contribution_map.end() )
    entity_bin_data->second += contribution;
  else
    thread_entity_bin_contribution_map[bin_index] = contribution;
}

// Get the bin iterator from an update tracker iterator
template<typename EntityId>
inline void
StandardEntityEstimator<EntityId>::getEntityIteratorFromUpdateTracker(
              const size_t thread_id,
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
           const size_t thread_id,
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
                                                       const size_t thread_id )
{
  d_update_tracker[thread_id].clear();
}

// Save the data to an archive
template<typename EntityId>
template<typename Archive>
void StandardEntityEstimator<EntityId>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseEstimatorType );

  // Save the local data
  ar & BOOST_SERIALIZATION_NVP( d_total_estimator_moments );
  ar & BOOST_SERIALIZATION_NVP( d_total_estimator_moments );
}

// Load the data from an archive
template<typename EntityId>
template<typename Archive>
void StandardEntityEstimator<EntityId>::load( Archive& ar, const unsigned version )
{
  // Load the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseEstimatorType );

  // Load the local data
  ar & BOOST_SERIALIZATION_NVP( d_total_estimator_moments );
  ar & BOOST_SERIALIZATION_NVP( d_total_estimator_moments );

  // Initialize the thread data
  d_update_tracker.resize( 1 );
}

} // end MonteCarlo namespace

BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS1( StandardEntityEstimator, MonteCarlo );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardEntityEstimator<Geometry::Model::InternalCellHandle> );
EXTERN_EXPLICIT_MONTE_CARLO_CLASS_SERIALIZATION_INST( MonteCarlo::EntityEstimator<Geometry::Model::InternalCellHandle> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardEntityEstimator<size_t> );
EXTERN_EXPLICIT_MONTE_CARLO_CLASS_SERIALIZATION_INST( MonteCarlo::EntityEstimator<size_t> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardEntityEstimator<moab::EntityHandle> );
EXTERN_EXPLICIT_MONTE_CARLO_CLASS_SERIALIZATION_INST( MonteCarlo::EntityEstimator<moab::EntityHandle> );

#endif // end MONTE_CARLO_STANDARD_ENTITY_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardEntityEstimator_def.hpp
//---------------------------------------------------------------------------//
