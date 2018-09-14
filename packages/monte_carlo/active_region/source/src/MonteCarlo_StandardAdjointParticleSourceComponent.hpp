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
#include "MonteCarlo_AdjointPhotonProbeState.hpp"
#include "MonteCarlo_AdjointElectronState.hpp"
#include "MonteCarlo_AdjointElectronProbeState.hpp"

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

  //! The id type
  typedef ParticleState::sourceIdType Id;

  //! The trial counter type
  typedef typename BaseType::Counter Counter;

  //! The cell id set
  typedef typename BaseType::CellIdSet CellIdSet;

  //! Constructor
  StandardAdjointParticleSourceComponent(
    const Id id,
    const double selection_weight,
    const std::shared_ptr<const Geometry::Model>& model,
    const std::shared_ptr<const ParticleDistribution>& particle_distribution,
    const std::vector<double>& critical_line_energies );

  //! Constructor (with rejection cells )
  StandardAdjointParticleSourceComponent(
    const Id id,
    const double selection_weight,
    const std::vector<Geometry::Model::EntityId>& rejection_cells,
    const std::shared_ptr<const Geometry::Model>& model,
    const std::shared_ptr<const ParticleDistribution>& particle_distribution,
    const std::vector<double>& critical_line_energies );

  //! Constructor (with rejection cells )
  StandardAdjointParticleSourceComponent(
    const Id id,
    const double selection_weight,
    const CellIdSet& rejection_cells,
    const std::shared_ptr<const Geometry::Model>& model,
    const std::shared_ptr<const ParticleDistribution>& particle_distribution,
    const std::vector<double>& critical_line_energies );

  //! Constructor
  StandardAdjointParticleSourceComponent(
    const Id id,
    const double selection_weight,
    const std::shared_ptr<const FilledGeometryModel>& model,
    const std::shared_ptr<const ParticleDistribution>& particle_distribution );

  //! Constructor (with rejection cells )
  StandardAdjointParticleSourceComponent(
    const Id id,
    const double selection_weight,
    const std::vector<Geometry::Model::EntityId>& rejection_cells,
    const std::shared_ptr<const FilledGeometryModel>& model,
    const std::shared_ptr<const ParticleDistribution>& particle_distribution );

  //! Constructor (with rejection cells )
  StandardAdjointParticleSourceComponent(
    const Id id,
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

  // Default Constructor
  StandardAdjointParticleSourceComponent();

  // Set the critical line energy sampling functions
  void setCriticalLineEnergySamplingFunctions();

  // Save the data to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the data from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The critical line energies
  std::vector<double> d_critical_line_energies;

  // The particle state critical line energy sampling functions
  typedef typename BaseType::DimensionCounterMap DimensionCounterMap;
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
