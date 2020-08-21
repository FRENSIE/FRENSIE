//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardParticleSimulationManager.hpp
//! \author Alex Robinson
//! \brief  Standard particle simulation manager class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_PARTICLE_SIMULATION_MANAGER_HPP
#define MONTE_CARLO_STANDARD_PARTICLE_SIMULATION_MANAGER_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleSimulationManager.hpp"
#include "Utility_Map.hpp"

namespace MonteCarlo{

namespace Details{

//! The mode initialization helper class
template<typename BeginParticleIterator, typename EndParticleIterator>
struct ModeInitializationHelper;
  
} // end Details namespace

//! The standard particle simulation manager class
template<ParticleModeType mode>
class StandardParticleSimulationManager : public ParticleSimulationManager
{

public:

  //! Constructor
  StandardParticleSimulationManager(
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
                 const bool use_single_rendezvous_file );

  //! Destructor
  ~StandardParticleSimulationManager()
  { /* ... */ }

protected:

  //! Simulate an unresolved particle
  void simulateUnresolvedParticle( ParticleState& unresolved_particle,
                                   ParticleBank& bank,
                                   const bool source_particle ) final override;

private:

  // Add simulate particle function for particle type
  template<typename State>
  void addSimulateParticleFunction();

  // Add the mode initialization helper class as a friend
  template<typename T, typename U>
  friend class Details::ModeInitializationHelper;

  // The simulation functions
  typedef std::function<void(ParticleState&, ParticleBank&, const bool)>
  SimulateParticleFunction;

  typedef std::map<ParticleType,SimulateParticleFunction>
  SimulateParticleFunctionMap;

  SimulateParticleFunctionMap d_simulate_particle_function_map;
};
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardParticleSimulationManager_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_PARTICLE_SIMULATION_MANAGER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleSimulationManager.hpp
//---------------------------------------------------------------------------//
