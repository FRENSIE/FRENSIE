//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardParticleSourceComponent_def.hpp
//! \author Alex Robinson
//! \brief  The standard particles source component class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_PARTICLE_SOURCE_COMPONENT_DEF_HPP
#define MONTE_CARLO_STANDARD_PARTICLE_SOURCE_COMPONENT_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardParticleSourceComponent.hpp"
#include "Utility_OpenMPProperties.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default Constructor
template<typename ParticleStateType>
StandardParticleSourceComponent<ParticleStateType>::StandardParticleSourceComponent()
  : ParticleSourceComponent()
{ /* ... */ }

// Constructor
template<typename ParticleStateType>
StandardParticleSourceComponent<ParticleStateType>::StandardParticleSourceComponent(
     const Id id,
     const double selection_weight,
     const std::shared_ptr<const Geometry::Model>& model,
     const std::shared_ptr<const ParticleDistribution>& particle_distribution )
  : StandardParticleSourceComponent( id,
                                     selection_weight,
                                     CellIdSet(),
                                     model,
                                     particle_distribution )
{ /* ... */ }

// Constructor (with rejection cells )
template<typename ParticleStateType>
StandardParticleSourceComponent<ParticleStateType>::StandardParticleSourceComponent(
     const Id id,
     const double selection_weight,
     const std::vector<Geometry::Model::EntityId>& rejection_cells,
     const std::shared_ptr<const Geometry::Model>& model,
     const std::shared_ptr<const ParticleDistribution>& particle_distribution )
  : StandardParticleSourceComponent( id,
                                     selection_weight,
                                     CellIdSet( rejection_cells.begin(),
                                                rejection_cells.end() ),
                                     model,
                                     particle_distribution )
{ /* ... */ }
  
// Constructor (with rejection cells )
template<typename ParticleStateType>
StandardParticleSourceComponent<ParticleStateType>::StandardParticleSourceComponent(
     const Id id,
     const double selection_weight,
     const CellIdSet& rejection_cells,
     const std::shared_ptr<const Geometry::Model>& model,
     const std::shared_ptr<const ParticleDistribution>& particle_distribution )
  : ParticleSourceComponent( id, selection_weight, rejection_cells, model ),
    d_particle_distribution( particle_distribution ),
    d_dimension_trial_counters( 1 ),
    d_dimension_sample_counters( 1 )
{
  // Make sure that the particle distribution pointer is valid
  testPrecondition( particle_distribution.get() );

  // Initialize the dimension trial counters
  this->initializeDimensionTrialCounters();

  // Initialize the dimension sample counters
  this->initializeDimensionSampleCounters();
}

// Return the number of sampling trials in the phase space dimension
/*! \details Only the master thread should call this method.
 */
template<typename ParticleStateType>
auto StandardParticleSourceComponent<ParticleStateType>::getNumberOfDimensionTrials(
                         const PhaseSpaceDimension dimension ) const -> Counter
{
  // Make sure that only the root process calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  if( d_dimension_trial_counters.front().count( dimension ) )
    return this->reduceLocalDimensionTrialCounters( dimension );
  else
    return 0;
}

// Return the number of samples in the phase space dimension
/*! \details Only the master thread should call this method.
 */
template<typename ParticleStateType>
auto StandardParticleSourceComponent<ParticleStateType>::getNumberOfDimensionSamples(
                         const PhaseSpaceDimension dimension ) const -> Counter
{
  // Make sure that only the root process calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  if( d_dimension_sample_counters.front().count( dimension ) )
    return this->reduceLocalDimensionSampleCounters( dimension );
  else
    return 0;
}

// Return the sampling efficiency in the phase space dimension
/*! \details Only the master thread should call this method
 */
template<typename ParticleStateType>
double StandardParticleSourceComponent<ParticleStateType>::getDimensionSamplingEfficiency(
                                    const PhaseSpaceDimension dimension ) const
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  // Reduce the number of samples for the dimension
  Counter total_samples =
    this->reduceLocalDimensionSampleCounters( dimension );

  // Reduce the number of trials for the dimension
  Counter total_trials =
    this->reduceLocalDimensionTrialCounters( dimension );

  if( total_trials > 0 )
    return static_cast<double>( total_samples )/total_trials;
  else
    return 1.0;
}

// Print a summary of the sampling statistics
/*! \details Only the master thread should call this method.
 */
template<typename ParticleStateType>
void StandardParticleSourceComponent<ParticleStateType>::printSummary( std::ostream& os ) const
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  constexpr const ParticleType particle_type = ParticleStateType::type;

  // Print the source sampling statistics
  this->printStandardSummary( "Standard Source Component",
                              Utility::toString( particle_type ),
                              this->getNumberOfTrials(),
                              this->getNumberOfSamples(),
                              this->getSamplingEfficiency(),
                              os );

  // Print the starting cell summary
  CellIdSet starting_cells;
  this->getStartingCells( starting_cells );
  
  this->printStandardStartingCellSummary( starting_cells, os );
  
  // Print the sampling statistics for each source dimension
  DimensionCounterMap::const_iterator dimension_it, dimension_end;
  dimension_it = d_dimension_trial_counters.front().begin();
  dimension_end = d_dimension_trial_counters.front().end();
  
  while( dimension_it != dimension_end )
  {
    this->printStandardDimensionSummary(
      d_particle_distribution->getDimensionDistributionTypeName( dimension_it->first ),
      dimension_it->first,
      this->getNumberOfDimensionTrials( dimension_it->first ),
      this->getNumberOfDimensionSamples( dimension_it->first ),
      this->getDimensionSamplingEfficiency( dimension_it->first ),
      os );
    
    ++dimension_it;
  }
}

// Enable thread support
/*! \details Only the master thread should call this method.
 */
template<typename ParticleStateType>
void StandardParticleSourceComponent<ParticleStateType>::enableThreadSupportImpl( const size_t threads )
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );
  // Make sure a valid number of threads has been requested
  testPrecondition( threads > 0 );

  // Determine the number of new thread to support
  int number_of_threads = d_dimension_trial_counters.size();
  int number_of_new_threads = threads - number_of_threads;

  if( number_of_new_threads > 0 )
  {
    d_dimension_trial_counters.resize( threads );
    d_dimension_sample_counters.resize( threads );

    // Initialize the dimension counters
    this->initializeDimensionCounters(
            Utility::ArrayView<DimensionCounterMap>(
                           d_dimension_trial_counters.data()+number_of_threads,
                           number_of_new_threads ) );

    this->initializeDimensionCounters(
            Utility::ArrayView<DimensionCounterMap>(
                          d_dimension_sample_counters.data()+number_of_threads,
                          number_of_new_threads ) );
  }
}

// Reset the sampling statistics
/*! \details Only the master thread should call this method.
 */
template<typename ParticleStateType>
void StandardParticleSourceComponent<ParticleStateType>::resetDataImpl()
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  this->initializeDimensionSampleCounters();
  this->initializeDimensionTrialCounters();
}

// Reduce the sampling statistics on the root process
/*! \details Only the master thread should call this method.
 */
template<typename ParticleStateType>
void StandardParticleSourceComponent<ParticleStateType>::reduceDataImpl(
                                             const Utility::Communicator& comm,
                                             const int root_process )
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );
  // Make sure the root process is valid
  testPrecondition( root_process < comm.size() );

  // Only do the reduction if there is more than one process
  if( comm.size() > 1 )
  {
    // Reduce the dimension trial counters
    try{
      this->reduceDimensionTrialCounters( comm, root_process );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "unable to reduce the dimension trial "
                             "counters!" );

    // Reduce the dimension sample counters
    try{
      this->reduceDimensionSampleCounters( comm, root_process );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "unable to reduce the dimension sample "
                             "counters!" );
  }
}

// Return the number of particle states that will be sampled for the
// given history number
/*! \details The number of particle states that must be sampled for each
 * history is the the number of critical energies plus one (a probe particle
 * must be generated for each critical energy).
 */
template<typename ParticleStateType>
unsigned long long StandardParticleSourceComponent<ParticleStateType>::getNumberOfParticleStateSamples(
                                       const unsigned long long history ) const
{
  return 1;
}

// Initialize a particle state
template<typename ParticleStateType>
std::shared_ptr<ParticleState> StandardParticleSourceComponent<ParticleStateType>::initializeParticleState(
                                    const unsigned long long history,
                                    const unsigned long long history_state_id )
{
  // Make sure that the history state id is valid
  testPrecondition( history_state_id <
                    this->getNumberOfParticleStateSamples( history ) );
  
  return std::shared_ptr<ParticleState>( new ParticleStateType( history ) );
}

// Sample a particle state from the source
template<typename ParticleStateType>
bool StandardParticleSourceComponent<ParticleStateType>::sampleParticleStateImpl(
                                const std::shared_ptr<ParticleState>& particle,
                                const unsigned long long history_state_id )
{
  // Make sure that the history state id is valid
  testPrecondition( history_state_id < this->getNumberOfParticleStateSamples(particle->getHistoryNumber()) );

  DimensionCounterMap& dimension_trial_counters =
    d_dimension_trial_counters[Utility::OpenMPProperties::getThreadId()];

  DimensionCounterMap& dimension_sample_counters =
    d_dimension_sample_counters[Utility::OpenMPProperties::getThreadId()];

  d_particle_distribution->sampleAndRecordTrials( *particle, dimension_trial_counters );

  // Increment the dimension sample counters
  this->incrementDimensionCounters( dimension_sample_counters, false );

  return true;
}

// Reduce the dimension sample counters on the comm
template<typename ParticleStateType>
void StandardParticleSourceComponent<ParticleStateType>::reduceDimensionSampleCounters(
                                             const Utility::Communicator& comm,
                                             const int root_process )
{
  StandardParticleSourceComponent<ParticleStateType>::reduceDimensionCounters(
                                                   d_dimension_sample_counters,
                                                   comm,
                                                   root_process );
}

// Reduce the dimension trial counters on the comm
template<typename ParticleStateType>
void StandardParticleSourceComponent<ParticleStateType>::reduceDimensionTrialCounters(
                                             const Utility::Communicator& comm,
                                             const int root_process )
{
  StandardParticleSourceComponent<ParticleStateType>::reduceDimensionCounters(
                                                    d_dimension_trial_counters,
                                                    comm,
                                                    root_process );
}

// Reduce the dimension counters on the comm
template<typename ParticleStateType>
void StandardParticleSourceComponent<ParticleStateType>::reduceDimensionCounters(
            std::vector<DimensionCounterMap>& dimension_counters,
            const Utility::Communicator& comm,
            const int root_process )
{
  for( size_t i = 0; i < dimension_counters.size(); ++i )
  {
    if( comm.rank() != root_process )
    {
      Utility::gather( comm, dimension_counters[i], root_process );
    }
    else
    {
      std::vector<DimensionCounterMap> gathered_dimension_counters;
      
      Utility::gather( comm, dimension_counters[i], gathered_dimension_counters, root_process );
      
      DimensionCounterMap reduced_dimension_counters;
      
      StandardParticleSourceComponent<ParticleStateType>::reduceAllDimensionCounters(
                                                 reduced_dimension_counters,
                                                 gathered_dimension_counters );

      dimension_counters[i] = reduced_dimension_counters;
    }

    comm.barrier();
  }
}

// Reduce all of the local dimension samples counters
template<typename ParticleStateType>
void StandardParticleSourceComponent<ParticleStateType>::reduceAllLocalDimensionSampleCounters(
                         DimensionCounterMap& dimension_sample_counters ) const
{
  StandardParticleSourceComponent<ParticleStateType>::reduceAllDimensionCounters(
                                                 dimension_sample_counters,
                                                 d_dimension_sample_counters );
}

// Reduce all of the local dimension trials counters
template<typename ParticleStateType>
void StandardParticleSourceComponent<ParticleStateType>::reduceAllLocalDimensionTrialCounters(
                          DimensionCounterMap& dimension_trial_counters ) const
{
  StandardParticleSourceComponent<ParticleStateType>::reduceAllDimensionCounters(
                                                  dimension_trial_counters,
                                                  d_dimension_trial_counters );
}

// Reduce the dimension counters
template<typename ParticleStateType>
void StandardParticleSourceComponent<ParticleStateType>::reduceAllDimensionCounters(
               DimensionCounterMap& dimension_counters,
               const std::vector<DimensionCounterMap>& all_dimension_counters )
{
  for( size_t i = 0; i < all_dimension_counters.size(); ++i )
  {
    DimensionCounterMap::const_iterator dimension_counter_it,
      dimension_counter_end;
    
    dimension_counter_it = all_dimension_counters[i].begin();
    dimension_counter_end = all_dimension_counters[i].end();

    while( dimension_counter_it != dimension_counter_end )
    {
      // Initialize the dimension counter
      if( dimension_counters.find(dimension_counter_it->first) ==
          dimension_counters.end() )
        dimension_counters[dimension_counter_it->first] = 0;

      dimension_counters.find(dimension_counter_it->first)->second +=
        dimension_counter_it->second;
      
      ++dimension_counter_it;
    }
  }
}

// Reduce the local dimension sample counters
template<typename ParticleStateType>
auto StandardParticleSourceComponent<ParticleStateType>::reduceLocalDimensionSampleCounters(
                         const PhaseSpaceDimension dimension ) const -> Counter
{
  return StandardParticleSourceComponent<ParticleStateType>::reduceDimensionCounters(
                                      dimension, d_dimension_sample_counters );
}

// Reduce the local dimension trial counters
template<typename ParticleStateType>
auto StandardParticleSourceComponent<ParticleStateType>::reduceLocalDimensionTrialCounters(
                         const PhaseSpaceDimension dimension ) const -> Counter
{
  return StandardParticleSourceComponent<ParticleStateType>::reduceDimensionCounters(
                                       dimension, d_dimension_trial_counters );
}

// Reduce the dimension counter
template<typename ParticleStateType>
auto StandardParticleSourceComponent<ParticleStateType>::reduceDimensionCounters(
        const PhaseSpaceDimension dimension,
        const std::vector<DimensionCounterMap>& dimension_counters ) -> Counter
{
  Counter counter = 0;

  for( size_t i = 0; i < dimension_counters.size(); ++i )
  {
    if( dimension_counters[i].find( dimension ) !=
        dimension_counters[i].end() )
      counter += dimension_counters[i].find( dimension )->second;
  }

  return counter;
}

// Initialize the dimension sample counters
template<typename ParticleStateType>
void StandardParticleSourceComponent<ParticleStateType>::initializeDimensionSampleCounters()
{
  this->initializeDimensionCounters( d_dimension_sample_counters );
}

// Initialize the dimension trial counters
template<typename ParticleStateType>
void StandardParticleSourceComponent<ParticleStateType>::initializeDimensionTrialCounters()
{
  this->initializeDimensionCounters( d_dimension_trial_counters );
}

// Initialize the dimension counters
template<typename ParticleStateType>
inline void StandardParticleSourceComponent<ParticleStateType>::initializeDimensionCounters(
                         std::vector<DimensionCounterMap>& dimension_counters )
{
  this->initializeDimensionCounters( Utility::arrayView(dimension_counters) );
}

// Initialize the dimension counters
template<typename ParticleStateType>
void StandardParticleSourceComponent<ParticleStateType>::initializeDimensionCounters(
            const Utility::ArrayView<DimensionCounterMap>& dimension_counters )
{
  for( size_t i = 0; i < dimension_counters.size(); ++i )
    d_particle_distribution->initializeDimensionCounters( dimension_counters[i] );
}

// Get the dimension trial counters
template<typename ParticleStateType>
auto StandardParticleSourceComponent<ParticleStateType>::getDimensionTrialCounterMap() -> DimensionCounterMap&
{
  return d_dimension_trial_counters[Utility::OpenMPProperties::getThreadId()];
}

// Get the dimension sample counters
template<typename ParticleStateType>
auto StandardParticleSourceComponent<ParticleStateType>::getDimensionSampleCounterMap() -> DimensionCounterMap&
{
  return d_dimension_sample_counters[Utility::OpenMPProperties::getThreadId()];
}

// Increment the dimension counters
template<typename ParticleStateType>
void StandardParticleSourceComponent<ParticleStateType>::incrementDimensionCounters(
                                       DimensionCounterMap& dimension_counters,
                                       const bool ignore_energy_dimension )
{
  DimensionCounterMap::iterator dimension_counter_it =
    dimension_counters.begin();

  while( dimension_counter_it != dimension_counters.end() )
  {
    // Always increment a dimension counter if it is not associated with the
    // energy dimension
    if( dimension_counter_it->first != ENERGY_DIMENSION )
      ++dimension_counter_it->second;
    
    // Only increment the energy dimension counter if requested
    else
    {
      if( !ignore_energy_dimension )
        ++dimension_counter_it->second;
    }

    ++dimension_counter_it;
  }
}

// Get the particle distribution
template<typename ParticleStateType>
const ParticleDistribution& StandardParticleSourceComponent<ParticleStateType>::getParticleDistribution() const
{
  return *d_particle_distribution;
}

// Save the data to an archive
template<typename ParticleStateType>
template<typename Archive>
void StandardParticleSourceComponent<ParticleStateType>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleSourceComponent );

  // Save the local data
  ar & BOOST_SERIALIZATION_NVP( d_particle_distribution );

  DimensionCounterMap dimension_trial_counters;
  this->reduceAllLocalDimensionTrialCounters( dimension_trial_counters );
  
  ar & BOOST_SERIALIZATION_NVP( dimension_trial_counters );

  DimensionCounterMap dimension_sample_counters;
  this->reduceAllLocalDimensionSampleCounters( dimension_sample_counters );

  ar & BOOST_SERIALIZATION_NVP( dimension_sample_counters );
}

// Load the data from an archive
template<typename ParticleStateType>
template<typename Archive>
void StandardParticleSourceComponent<ParticleStateType>::load( Archive& ar, const unsigned version )
{
  // Load the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleSourceComponent );

  // Load the local data
  ar & BOOST_SERIALIZATION_NVP( d_particle_distribution );

  DimensionCounterMap dimension_trial_counters;
  
  ar & BOOST_SERIALIZATION_NVP( dimension_trial_counters );

  d_dimension_trial_counters.resize( 1 );
  d_dimension_trial_counters.front() = dimension_trial_counters;

  DimensionCounterMap dimension_sample_counters;
  
  ar & BOOST_SERIALIZATION_NVP( dimension_sample_counters );

  d_dimension_sample_counters.resize( 1 );
  d_dimension_sample_counters.front() = dimension_sample_counters;
}
  
} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( StandardNeutronSourceComponent, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::StandardParticleSourceComponent<MonteCarlo::NeutronState> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, StandardParticleSourceComponent<MonteCarlo::NeutronState> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( StandardPhotonSourceComponent, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::StandardParticleSourceComponent<MonteCarlo::PhotonState> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, StandardParticleSourceComponent<MonteCarlo::PhotonState> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( StandardElectronSourceComponent, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::StandardParticleSourceComponent<MonteCarlo::ElectronState> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, StandardParticleSourceComponent<MonteCarlo::ElectronState> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( StandardPositronSourceComponent, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::StandardParticleSourceComponent<MonteCarlo::PositronState> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, StandardParticleSourceComponent<MonteCarlo::PositronState> );

#endif // end MONTE_CARLO_STANDARD_PARTICLE_SOURCE_COMPONENT_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleSourceComponent_def.hpp
//---------------------------------------------------------------------------//
