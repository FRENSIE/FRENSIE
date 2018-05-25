//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardAdjointParticleSourceComponent_def.hpp
//! \author Alex Robinson
//! \brief  The standard adjoint particle source component class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_ADJOINT_PARTICLE_SOURCE_COMPONENT_DEF_HPP
#define MONTE_CARLO_STANDARD_ADJOINT_PARTICLE_SOURCE_COMPONENT_DEF_HPP

namespace MonteCarlo{

// Constructor
template<typename ParticleStateType,typename ProbeParticleStateType>
StandardAdjointParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::StandardAdjointParticleSourceComponent(
     const size_t id,
     const double selection_weight,
     const std::shared_ptr<const FilledGeometryModel>& model,
     const std::shared_ptr<const ParticleDistribution>& particle_distribution )
  : StandardAdjointParticleSourceComponent( id,
                                            selection_weight,
                                            CellIdSet(),
                                            model,
                                            particle_distribution )
{ /* ... */ }

// Constructor (with rejection cells )
template<typename ParticleStateType,typename ProbeParticleStateType>
StandardAdjointParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::StandardAdjointParticleSourceComponent(
     const size_t id,
     const double selection_weight,
     const CellIdSet& rejection_cells,
     const std::shared_ptr<const FilledGeometryModel>& model,
     const std::shared_ptr<const ParticleDistribution>& particle_distribution )
  : BaseType( id,
              selectrion_weight,
              rejection_cells,
              *model,
              particle_distribution ),
    d_critical_line_energies(),
    d_particle_state_critical_line_energy_sampling_functions()
{
  // Make sure that the model pointer is valid
  testPrecondition( model.get() );

  // Set the critical line energy sampling functions
  const FilledGeometryModelUpcastHelper<ParticleStateType>::UpcastType&
    upcast_model = *model;

  d_critical_line_energies = upcast_model.getCriticalLineEnergies();

  this->setCriticalLineEnergySamplingFunctions();
}

// Set the critical line energies
template<typename ParticleStateType,typename ProbeParticleStateType>
void StandardAdjointParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::setCriticalLineEnergySamplingFunctions()
{
  if( d_critical_line_energies.size() > 0 )
  {
    d_particle_state_critical_line_energy_sampling_functions.resize(
                                             d_critical_line_energies.size() );

    // Create the sampling function for each critical line energy
    for( size_t i = 0; i < critical_line_energies.size(); ++i )
    {
      Utility::get<0>(d_particle_state_critical_line_energy_sampling_functions[i]) =
        d_critical_line_energies[i];

      Utility::get<1>(d_particle_state_critical_line_energy_sampling_functions[i]) =
        std::bind<void>( &ParticleDistribution::sampleWithDimensionValueAndRecordTrials,
                         std::cref( this->getParticleDistribution() ),
                         std::placeholders::_1,
                         std::placeholders::_2,
                         ENERGY_DIMENSION,
                         d_critical_line_energies[i] );
    }
  }
}

// Return the number of particle states that will be sampled for the 
// given history number
template<typename ParticleStateType,typename ProbeParticleStateType>
unsigned long long StandardAdjointParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::getNumberOfParticleStateSamples(
                                       const unsigned long long history ) const
{
  return d_particle_state_critical_line_energy_sampling_functions.size() + 1;
}

// Initialize a particle state
template<typename ParticleStateType,typename ProbeParticleStateType>
std::shared_ptr<ParticleState> StandardAdjointParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::initializeParticleState(
                                    const unsigned long long history,
                                    const unsigned long long history_state_id )
{
  // Make sure that the history state id is valid
  testPrecondition( history_state_id <
                    this->getNumberOfParticleStateSamples( history ) );
  
  if( history_state_id == 0 )
    return BaseType::initializeParticleState( history, history_state_id );
  else // history_state_id > 0 
  {
    // Initialize the probe particle
    return std::shared_ptr<ParticleState>( new ProbeParticleStateType( history ) );
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
bool StandardAdjointParticleSourceComponent<ParticleStateType,ProbeParticleStateType>::sampleParticleStateImpl(
                                const std::shared_ptr<ParticleState>& particle,
                                const unsigned long long history_state_id )
{
  // Make sure that the history state id is valid
  testPrecondition( history_state_id < this->getNumberOfParticleStateSamples(particle->getHistoryNumber()) );

  if( history_state_id == 0 )
    return BaseType::sampleParticleStateImpl( particle, history_state_id );
  else
  {
    // Sample a probe particle
    Utility::get<1>(d_particle_state_critical_line_energy_sampling_functions[history_state_id-1])( *particle, this->getDimensionTrialCounters() );

    // Increment the dimension sample counters
    this->incrementDimensionCounters( this->getDimensionSampleCounters(), true );
    
    return true;
  }
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_ADJOINT_PARTICLE_SOURCE_COMPONENT_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardAdjointParticleSourceComponent_def.hpp
//---------------------------------------------------------------------------//
