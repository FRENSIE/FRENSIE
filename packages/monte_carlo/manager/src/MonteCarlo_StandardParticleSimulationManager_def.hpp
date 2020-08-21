//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardParticleSimulationManager_def.hpp
//! \author Alex Robinson
//! \brief  Standard particle simulation manager definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_PARTICLE_SIMULATION_MANAGER_DEF_HPP
#define MONTE_CARLO_STANDARD_PARTICLE_SIMULATION_MANAGER_DEF_HPP

// Boost Includes
#include <boost/mpl/find.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/begin_end.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleModeTypeTraits.hpp"
#include "MonteCarlo_CollisionForcer.hpp"
#include "MonteCarlo_StandardCollisionForcer.hpp"

namespace MonteCarlo{

namespace Details{

// The mode initialization helper class
template<typename BeginParticleIterator, typename EndParticleIterator>
struct ModeInitializationHelper
{
  //! Initialize simulate particle functors map
  template<typename Manager>
  static inline void initializeSimulateParticleFunctions( Manager& manager )
  {
    typedef typename boost::mpl::deref<BeginParticleIterator>::type ParticleStateType;

    manager.template addSimulateParticleFunction<ParticleStateType>();

    ModeInitializationHelper<typename boost::mpl::next<BeginParticleIterator>::type,EndParticleIterator>::initializeSimulateParticleFunctions( manager );
  }
};

// End initialization
template<typename EndParticleIterator>
struct ModeInitializationHelper<EndParticleIterator,EndParticleIterator>
{
  //! Initialize simulate particle functors map
  template<typename Manager>
  static inline void initializeSimulateParticleFunctions( Manager& manager )
  { /* ... */ }
};

} // end Details namespace

// Constructor
template<ParticleModeType mode>
StandardParticleSimulationManager<mode>::StandardParticleSimulationManager(
                 const std::string& simulation_name,
                 const std::string& archive_type,
                 const std::shared_ptr<const FilledGeometryModel>& model,
                 const std::shared_ptr<ParticleSource>& source,
                 const std::shared_ptr<EventHandler>& event_handler,
                 const std::shared_ptr<PopulationControl> population_controller,
                 const std::shared_ptr<const CollisionForcer> collision_forcer,
                 const std::shared_ptr<const SimulationProperties>& properties,
                 const uint64_t next_history,
                 const uint64_t rendezvous_number,
                 const bool use_single_rendezvous_file )
  : ParticleSimulationManager( simulation_name,
                               archive_type,
                               model,
                               source,
                               event_handler,
                               population_controller,
                               collision_forcer,
                               properties,
                               next_history,
                               rendezvous_number,
                               use_single_rendezvous_file )
{
  Details::ModeInitializationHelper<typename boost::mpl::begin<typename ParticleModeTypeTraits<mode>::ActiveParticles>::type,typename boost::mpl::end<typename ParticleModeTypeTraits<mode>::ActiveParticles>::type>::initializeSimulateParticleFunctions( *this );
}

// Simulate an unresolved particle
template<ParticleModeType mode>
void StandardParticleSimulationManager<mode>::simulateUnresolvedParticle(
                                            ParticleState& unresolved_particle,
                                            ParticleBank& bank,
                                            const bool source_particle )
{
  SimulateParticleFunctionMap::const_iterator simulation_function_it =
    d_simulate_particle_function_map.find( unresolved_particle.getParticleType() );

  // Only simulate the particle if there is a simulation function associated
  // with the type
  if( simulation_function_it != d_simulate_particle_function_map.end() )
  {
    simulation_function_it->second( unresolved_particle, bank, source_particle );
  }
  else
    unresolved_particle.setAsGone();
}

// Add simulate particle function for particle type
template<ParticleModeType mode>
template<typename State>
void StandardParticleSimulationManager<mode>::addSimulateParticleFunction()
{
  constexpr const ParticleType particle_type = State::type;

  // Make sure that the state is compatible with the mode
  testPrecondition( MonteCarlo::isParticleTypeCompatible<mode>( particle_type ) );

  if( this->getCollisionForcer().hasForcedCollisionCells( particle_type ) )
  {
    d_simulate_particle_function_map[particle_type] =
      std::bind<void>( &ParticleSimulationManager::simulateParticleAlternative<State>,
                       std::ref( *this ),
                       std::placeholders::_1,
                       std::placeholders::_2,
                       std::placeholders::_3 );
  }
  else
  {
    d_simulate_particle_function_map[particle_type] =
      std::bind<void>( &ParticleSimulationManager::simulateParticle<State>,
                       std::ref( *this ),
                       std::placeholders::_1,
                       std::placeholders::_2,
                       std::placeholders::_3 );
  }
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_PARTICLE_SIMULATION_MANAGER_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleSimulationManager_def.hpp
//---------------------------------------------------------------------------//

