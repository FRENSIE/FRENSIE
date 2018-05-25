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
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<typename ParticleStateType,typename ProbeParticleStateType>
StandardParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::StandardParticleSourceComponent(
     const size_t id,
     const double selection_weight,
     const std::shared_ptr<const FilledGeometryModel>& model,
     const std::shared_ptr<const ParticleDistribution>& particle_distribution )
  : StandardParticleComponent( id,
                               selection_weight,
                               CellIdSet(),
                               model,
                               particle_distribution )
{ /* ... */ }

// Constructor (with rejection cells )
template<typename ParticleStateType,typename ProbeParticleStateType>
StandardParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::StandardParticleSourceComponent(
      const size_t id,
      const double selection_weight,
      const CellIdSet& rejection_cells,
      const std::shared_ptr<const FilledGeometryModel>& model,
      const std::shared_ptr<const ParticleDistribution>& particle_distribution,
      const ParticleType particle_type )
  : ParticleComponent( id, selection_weight, rejection_cells, *model ),
    d_particle_distribution( particle_distribution ),
    d_critical_line_energies(),
    d_dimension_trial_counters( 1 ),
    d_dimension_sample_counters( 1 ),
    d_particle_state_critical_line_energy_sampling_functions()
{
  // Make sure that the model pointer is valid
  testPrecondition( model.get() );
  // Make sure that the particle distribution pointer is valid
  testPrecondition( particle_distribution.get() );

  // Set the critical line energy sampling functions
  model->getCriticalLineEnergies( d_critical_line_energies, particle_type );
  this->setCriticalLineEnergySamplingFunctions();

  // Initialize the dimension trial counters
  this->initializeDimensionTrialCounters();

  // Initialize the dimension sample counters
  this->initializeDimensionSampleCounters();
}

// Return the number of sampling trials in the phase space dimension
/*! \details Only the master thread should call this method.
 */
template<typename ParticleStateType,typename ProbeParticleStateType>
auto StandardParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::getNumberOfDimensionTrials(
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
template<typename ParticleStateType,typename ProbeParticleStateType>
auto StandardParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::getNumberOfDimensionSamples(
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
template<typename ParticleStateType,typename ProbeParticleStateType>
double StandardParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::getDimensionSamplingEfficiency(
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
template<typename ParticleStateType,typename ProbeParticleStateType>
void StandardParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::printSummary( std::ostream& os ) const
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  // Print the source sampling statistics
  this->printStandardSummary( "Standard Source Component",
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
template<typename ParticleStateType,typename ProbeParticleStateType>
void StandardParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::enableThreadSupportImpl( const size_t threads )
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );
  // Make sure a valid number of threads has been requested
  testPrecondition( threads > 0 );

  d_dimension_trial_counters.resize( threads );
  d_dimension_sample_counters.resize( threads );

  // Initialize the dimension counters
  this->initializeDimensionTrialCounters();
  this->initializeDimensionSampleCounters();
}

// Reset the sampling statistics
/*! \details Only the master thread should call this method.
 */
template<typename ParticleStateType,typename ProbeParticleStateType>
void StandardParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::resetDataImpl()
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );
  // Make sure the root process is valid
  testPrecondition( root_process < comm->getSize() );

  this->initializeDimensionSampleCounters();
  this->initializeDimensionTrialCounters();
}

// Reduce the sampling statistics on the root process
/*! \details Only the master thread should call this method.
 */
template<typename ParticleStateType,typename ProbeParticleStateType>
void StandardParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::reduceDataImpl(
                                             const Utility::Communicator& comm,
                                             const int root_process )
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );
  // Make sure the root process is valid
  testPrecondition( root_process < comm->getSize() );

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
template<typename ParticleStateType,typename ProbeParticleStateType>
unsigned long long StandardParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::getNumberOfParticleStateSamples(
                                       const unsigned long long history ) const
{
  return d_particle_state_critical_line_energy_sampling_functions.size() + 1;
}

// Initialize a particle state
template<typename ParticleStateType,typename ProbeParticleStateType>
std::shared_ptr<ParticleState> StandardParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::initializeParticleState(
                                    const unsigned long long history,
                                    const unsigned long long history_state_id )
{
  // Make sure that the history state id is valid
  testPrecondition( history_state_id <
                    this->getNumberOfParticleStateSamples( history ) );
  
  if( history_state_id == 0 )
  {
    // Initialize the particle
    std::shared_ptr<ParticleState>
      particle( new ParticleStateType( history ) );
    
    return particle;
  }
  else if( history_state_id > 0 )
  {
    // Initialize the particle (probe)
    std::shared_ptr<ParticleState>
      particle( new ProbeParticleStateType( history ) );

    return particle;
  }
}

// Sample a particle state from the source
/*! \details Probe particles are currently sampled completely independently 
 * from the parent particle. It is quite possible that there is a more 
 * efficient way to generate probe particles but given that a particle 
 * distribution can be defined in a very general way it is not obvious how to 
 * do this. 
 */
template<typename ParticleStateType,typename ProbeParticleStateType>
bool StandardParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::sampleParticleStateImpl(
                                const std::shared_ptr<ParticleState>& particle,
                                const unsigned long long history_state_id )
{
  // Make sure that the history state id is valid
  testPrecondition( history_state_id < this->getNumberOfParticleStateSamples(particle->getHistoryNumber()) );

  DimensionCounterMap& dimension_trial_counters =
    d_dimension_trial_counters[Utility::OpenMPProperties::getThreadId()];

  DimensionCounterMap& dimension_sample_counters =
    d_dimension_sample_counters[Utility::OpenMPProperties::getThreadId()];

  if( history_state_id == 0 )
  {
    // Sample a standard particle
    d_particle_distribution->sampleAndRecordTrials( *particle, dimension_trial_counters );

    // Increment the dimension sample counters
    this->incrementDimensionCounters( dimension_sample_counters, false );
  }
  else if( history_state_id > 0 )
  {
    // Sample a probe particle
    Utility::get<1>(d_particle_state_critical_line_energy_sampling_functions[history_state_id-1])( *particle, dimension_trial_counters );

    // Increment the dimension sample counters
    this->incrementDimensionCounters( dimension_sample_counters, true );
  }

  return true;
}

// Set the critical line energies
template<typename ParticleStateType,typename ProbeParticleStateType>
void StandardParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::setCriticalLineEnergySamplingFunctions()
{
  if( d_critical_line_energies.size() > 0 )
  {
    d_particle_state_critical_line_energy_sampling_functions.resize(
                                             d_critical_line_energies.size() );

    // Create the sampling function for each critical line energy
    for( size_t i = 0; i < critical_line_energies.size(); ++i )
    {
      Utility::get<0>(d_particle_state_critical_line_energy_sampling_functions[i]) =
        critical_line_energies[i];

      Utility::get<1>(d_particle_state_critical_line_energy_sampling_functions[i]) =
        std::bind<void>( &ParticleDistribution::sampleWithDimensionValueAndRecordTrials,
                         std::cref( *d_particle_distribution ),
                         std::placeholders::_1,
                         std::placeholders::_2,
                         ENERGY_DIMENSION,
                         critical_line_energies[i] );
    }
  }
}

// Reduce the dimension sample counters on the comm
template<typename ParticleStateType,typename ProbeParticleStateType>
void StandardParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::reduceDimensionSampleCounters(
                                             const Utility::Communicator& comm,
                                             const int root_process )
{
  StandardParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::reduceDimensionCounters(
                                                       d_sample_trial_counters,
                                                       comm,
                                                       root_process );
}

// Reduce the dimension trial counters on the comm
template<typename ParticleStateType,typename ProbeParticleStateType>
void StandardParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::reduceDimensionTrialCounters(
                                             const Utility::Communicator& comm,
                                             const int root_process )
{
  StandardParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::reduceDimensionCounters(
                                                    d_dimension_trial_counters,
                                                    comm,
                                                    root_process );
}

// Reduce the dimension counters on the comm
template<typename ParticleStateType,typename ProbeParticleStateType>
void StandardParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::reduceDimensionCounters(
            std::vector<DimensionCounterMap>& dimension_counters,
            const Utility::Communicator& comm,
            const int root_process )
{
  for( size_t i = 0; i < dimension_counter.size(); ++i )
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
      
      StandardParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::reduceAllDimensionCounters(
                                                 reduced_dimension_counters,
                                                 gathered_dimension_counters );

      dimension_counters[i] = reduced_dimension_counters;
    }

    comm.barrier();
  }
}

// Reduce all of the local dimension samples counters
template<typename ParticleStateType,typename ProbeParticleStateType>
void StandardParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::reduceAllLocalDimensionSampleCounters(
                         DimensionCounterMap& dimension_sample_counters ) const
{
  StandardParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::reduceAllDimensionCounters(
                                                 dimension_sample_counters,
                                                 d_dimension_sample_counters );
}

// Reduce all of the local dimension trials counters
template<typename ParticleStateType,typename ProbeParticleStateType>
void StandardParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::reduceAllLocalDimensionTrialCounters(
                          DimensionCounterMap& dimension_trial_counters ) const
{
  StandardParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::reduceAllDimensionCounters(
                                                  dimension_trial_counters,
                                                  d_dimension_trial_counters );
}

// Reduce the dimension counters
template<typename ParticleStateType,typename ProbeParticleStateType>
void StandardParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::reduceAllDimensionCounters(
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
template<typename ParticleStateType,typename ProbeParticleStateType>
auto StandardParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::reduceLocalDimensionSampleCounters(
                         const PhaseSpaceDimension dimension ) const -> Counter
{
  return StandardParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::reduceDimensionCounters(
                                      dimension, d_dimension_sample_counters );
}

// Reduce the local dimension trial counters
template<typename ParticleStateType,typename ProbeParticleStateType>
auto StandardParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::reduceLocalDimensionTrialCounters(
                         const PhaseSpaceDimension dimension ) const -> Counter
{
  return StandardParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::reduceDimensionCounters(
                                       dimension, d_dimension_trial_counters );
}

// Reduce the dimension counter
template<typename ParticleStateType,typename ProbeParticleStateType>
auto StandardParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::reduceDimensionCounters(
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
template<typename ParticleStateType,typename ProbeParticleStateType>
void StandardParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::initializeDimensionSampleCounters()
{
  StandardParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::initializeDimensionCounters(
                                                 d_dimension_sample_counters );
}

// Initialize the dimension trial counters
template<typename ParticleStateType,typename ProbeParticleStateType>
void StandardParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::initializeDimensionTrialCounters()
{
  StandardParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::initializeDimensionCounters(
                                                  d_dimension_trial_counters );
}

// Initialize the dimension counters
template<typename ParticleStateType,typename ProbeParticleStateType>
void StandardParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::initializeDimensionCounters(
                         std::vector<DimensionCounterMap>& dimension_counters )
{
  for( size_t i = 0; i < dimension_counters.size(); ++i )
    d_particle_distribution->initializeDimensionCounters( dimension_counters[i] );
}

// Increment the dimension counters
template<typename ParticleStateType,typename ProbeParticleStateType>
void StandardParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::incrementDimensionCounters(
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
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_PARTICLE_SOURCE_COMPONENT_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleSourceComponent_def.hpp
//---------------------------------------------------------------------------//
