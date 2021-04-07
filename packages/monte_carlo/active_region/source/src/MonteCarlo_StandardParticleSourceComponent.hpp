//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardParticleSourceComponent.hpp
//! \author Alex Robinson
//! \brief  The standard particle source component class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_PARTICLE_SOURCE_COMPONENT_HPP
#define MONTE_CARLO_STANDARD_PARTICLE_SOURCE_COMPONENT_HPP

// Std Lib Includes
#include <functional>

// FRENSIE Includes
#include "MonteCarlo_ParticleSourceComponent.hpp"
#include "MonteCarlo_ParticleDistribution.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_PositronState.hpp"

namespace MonteCarlo{

/*! The standard particle source component class
 * 
 * The standard particle source class simply wraps the
 * MonteCarlo::ParticleDistribution class and provides some additional 
 * capabilities for calculating sampling efficiencies. 
 */
template<typename ParticleStateType>
class StandardParticleSourceComponent : public ParticleSourceComponent
{

public:

  //! The id type
  typedef ParticleSourceComponent::Id Id;

  //! The trial counter type
  typedef ParticleSourceComponent::Counter Counter;

  //! The cell id set
  typedef ParticleSourceComponent::CellIdSet CellIdSet;

  //! Constructor
  StandardParticleSourceComponent(
    const Id id,
    const double selection_weight,
    const std::shared_ptr<const Geometry::Model>& model,
    const std::shared_ptr<const ParticleDistribution>& particle_distribution );

  //! Constructor (with rejection cells )
  StandardParticleSourceComponent(
    const Id id,
    const double selection_weight,
    const std::vector<Geometry::Model::EntityId>& rejection_cells,
    const std::shared_ptr<const Geometry::Model>& model,
    const std::shared_ptr<const ParticleDistribution>& particle_distribution );
  
  //! Constructor (with rejection cells )
  StandardParticleSourceComponent(
    const Id id,
    const double selection_weight,
    const CellIdSet& rejection_cells,
    const std::shared_ptr<const Geometry::Model>& model,
    const std::shared_ptr<const ParticleDistribution>& particle_distribution );

  //! Destructor
  ~StandardParticleSourceComponent()
  { /* ... */ }

  //! Return the number of sampling trials in the phase space dimension
  Counter getNumberOfDimensionTrials(
                    const PhaseSpaceDimension dimension ) const final override;

  //! Return the number of samples in the phase space dimension
  Counter getNumberOfDimensionSamples(
                    const PhaseSpaceDimension dimension ) const final override;

  //! Return the sampling efficiency in the phase space dimension
  double getDimensionSamplingEfficiency(
                    const PhaseSpaceDimension dimension ) const final override;

  //! Print a summary of the sampling statistics
  void printSummary( std::ostream& os ) const final override;

protected:

  //! Typedef for the dimension trial counter map
  typedef ParticleDistribution::DimensionCounterMap DimensionCounterMap;

  //! Default Constructor
  StandardParticleSourceComponent();

  //! Enable thread support
  void enableThreadSupportImpl( const size_t threads ) final override;

  //! Reset the sampling statistics
  void resetDataImpl() final override;

  //! Reduce the sampling statistics on the root process
  void reduceDataImpl( const Utility::Communicator& comm,
                       const int root_process ) final override;

  /*! \brief Return the number of particle states that will be sampled for the 
   * given history number
   */
  virtual unsigned long long getNumberOfParticleStateSamples(
                             const unsigned long long history ) const override;

  //! Initialize a particle state
  virtual std::shared_ptr<ParticleState> initializeParticleState(
                          const unsigned long long history,
                          const unsigned long long history_state_id ) override;

  //! Sample a particle state from the source
  virtual bool sampleParticleStateImpl(
                    const std::shared_ptr<ParticleState>& particle,
                    const unsigned long long history_state_id ) override;

  //! Get the particle distribution
  const ParticleDistribution& getParticleDistribution() const;

  //! Get the dimension trial counters
  DimensionCounterMap& getDimensionTrialCounterMap();

  //! Get the dimension sample counters
  DimensionCounterMap& getDimensionSampleCounterMap();

  //! Increment the dimension counters
  static void incrementDimensionCounters(
                                  DimensionCounterMap& dimension_counters,
                                  const bool ignore_energy_dimension = false );
  
private:

  // Reduce the dimension sample counters on the comm
  void reduceDimensionSampleCounters( const Utility::Communicator& comm,
                                      const int root_process );

  // Reduce the dimension trial counters on the comm
  void reduceDimensionTrialCounters( const Utility::Communicator& comm,
                                     const int root_process );

  // Reduce the dimension counters on the comm
  static void reduceDimensionCounters(
                          std::vector<DimensionCounterMap>& dimension_counters,
                          const Utility::Communicator& comm,
                          const int root_process );

  // Reduce all of the local dimension samples counters
  void reduceAllLocalDimensionSampleCounters(
                        DimensionCounterMap& dimension_sample_counters ) const;

  // Reduce all of the local dimension trials counters
  void reduceAllLocalDimensionTrialCounters(
                         DimensionCounterMap& dimension_trial_counters ) const;

  // Reduce the dimension counters
  static void reduceAllDimensionCounters(
           DimensionCounterMap& dimension_counters,
           const std::vector<DimensionCounterMap>& all_dimension_counters );

  // Reduce the local dimension sample counters
  Counter reduceLocalDimensionSampleCounters(
                                   const PhaseSpaceDimension dimension ) const;

  // Reduce the local dimension trial counters
  Counter reduceLocalDimensionTrialCounters(
                                   const PhaseSpaceDimension dimension ) const;

  // Reduce the dimension counter
  static Counter reduceDimensionCounters(
               const PhaseSpaceDimension dimension,
               const std::vector<DimensionCounterMap>& dimension_counters );

  // Initialize the dimension sample counters
  void initializeDimensionSampleCounters();

  // Initialize the dimension trial counters
  void initializeDimensionTrialCounters();

  // Initialize the dimension counters
  void initializeDimensionCounters(
                     std::vector<DimensionCounterMap>& dimension_counters );

  // Initialize the dimension counters
  void initializeDimensionCounters(
           const Utility::ArrayView<DimensionCounterMap>& dimension_counters );

  // Save the data to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the data from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The particle distribution
  std::shared_ptr<const ParticleDistribution> d_particle_distribution;

  // The dimension trial counters
  std::vector<DimensionCounterMap> d_dimension_trial_counters;

  // The dimension samples counters
  std::vector<DimensionCounterMap> d_dimension_sample_counters;
};

//! The standard neutron source component
typedef StandardParticleSourceComponent<NeutronState> StandardNeutronSourceComponent;

//! The standard photon source component
typedef StandardParticleSourceComponent<PhotonState> StandardPhotonSourceComponent;

//! The standard electron source component
typedef StandardParticleSourceComponent<ElectronState> StandardElectronSourceComponent;

//! The standard positron source component
typedef StandardParticleSourceComponent<PositronState> StandardPositronSourceComponent;
  
} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS1_VERSION( StandardParticleSourceComponent, MonteCarlo, 0 );  

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardParticleSourceComponent_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_PARTICLE_SOURCE_COMPONENT_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleSourceComponent.hpp
//---------------------------------------------------------------------------//
