//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardAdjointParticleSourceComponent.hpp
//! \author Alex Robinson
//! \brief  The standard adjoint particle source component class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_ADJOINT_PARTICLE_SOURCE_COMPONENT_HPP
#define MONTE_CARLO_STANDARD_ADJOINT_PARTICLE_SOURCE_COMPONENT_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardParticleSourceComponent.hpp"
#include "MonteCarlo_FilledGeometryModel.hpp"
#include "MonteCarlo_AdjointPhotonState.hpp"
#include "MonteCarlo_AdjointElectronState.hpp"

namespace MonteCarlo{

/*! The standard adjoint particle source component class
 *
 * This class generates the probe particles required by the model (one
 * for each critical line energy defined).
 */
template<typename ParticleStateType,typename ProbeParticleStateType>
class StandardAdjointParticleSourceComponent : public StandardParticleSourceComponent<ParticleStateType>
{
  // Typedef for the base type
  typedef StandardParticleSourceComponent<ParticleStateType> BaseType;

public:

  //! Constructor
  StandardAdjointParticleSourceComponent(
    const size_t id,
    const double selection_weight,
    const std::shared_ptr<const FilledGeometryModel>& model,
    const std::shared_ptr<const ParticleDistribution>& particle_distribution );

  //! Constructor (with rejection cells )
  StandardAdjointParticleSourceComponent(
    const size_t id,
    const double selection_weight,
    const CellIdSet& rejection_cells,
    const std::shared_ptr<const FilledGeometryModel>& model,
    const std::shared_ptr<const ParticleDistribution>& particle_distribution );

  //! Destructor
  ~StandardAdjointParticleSourceComponent()
  { /* ... */ }

protected:

  /*! \brief Return the number of particle states that will be sampled for the 
   * given history number
   */
  virtual unsigned long long getNumberOfParticleStateSamples(
                             const unsigned long long history ) const override;

  //! Initialize a particle state
  std::shared_ptr<ParticleState> initializeParticleState(
                          const unsigned long long history,
                          const unsigned long long history_state_id ) override;

  //! Sample a particle state from the source
  bool sampleParticleStateImpl(
                    const std::shared_ptr<ParticleState>& particle,
                    const unsigned long long history_state_id ) override;

private:

  // Set the critical line energy sampling functions
  void setCriticalLineEnergySamplingFunctions();

  // Typedef for the dimension trial counter map
  typedef BaseType::DimensionCounterMap DimensionCounterMap;

  // The critical line energies
  std::vector<double> d_critical_line_energies;

  // The particle state critical line energy sampling functions
  typedef std::function<void(ParticleState&,DimensionCounterMap&)>
  ParticleStateSamplingFunction;
  
  std::vector<std::pair<double,ParticleStateSamplingFunction> >
  d_particle_state_critical_line_energy_sampling_functions;
};

//! The standard adjoint photon source component
typedef StandardAdjointParticleSourceComponent<AdjointPhotonState,AdjointPhotonProbeState> StandardAdjointPhotonSourceComponent;

//! The standard adjoint electron source component
typedef StandardAdjointParticleSourceComponent<AdjointElectronState,AdjointElectronProbeState> StandardAdjointElectronSourceComponent;
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardAdjointParticleSourceComponent_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_ADJOINT_PARTICLE_SOURCE_COMPONENT_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardAdjointParticleSourceComponent.hpp
//---------------------------------------------------------------------------//
