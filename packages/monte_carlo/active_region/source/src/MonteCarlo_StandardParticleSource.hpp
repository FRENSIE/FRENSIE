//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardParticleSource.hpp
//! \author Alex Robinson
//! \brief  Standard source class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_PARTICLE_SOURCE_HPP
#define MONTE_CARLO_STANDARD_PARTICLE_SOURCE_HPP

// Std Lib Includes
#include <memory>
#include <set>
#include <functional>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleSource.hpp"
#include "MonteCarlo_ParticleDistribution.hpp"
#include "Utility_OpenMPProperties.hpp"

namespace MonteCarlo{

/*! The standard particle source class
 * \details The standard particle source class simply wraps the
 * MonteCarlo::ParticleDistribution class and provides some additional 
 * capabilities for calculating sampling efficiencies, for generating
 * probe particles (commonly needed in adjoint simulations) and for 
 * adding geometry based rejection functions. Since the 
 * MonteCarlo::ParticleDistribution class is geometry agnostic and 
 * because it is sometimes necessary to limit where a particle's spatial 
 * coordinates are sampled, this class allows the user to specify rejection 
 * cells in the model of interest. Any sampled particle states with spatial 
 * coordinates that do not fall within one of the rejection cells will be 
 * discarded and a new state will be sampled. If no rejection cells are 
 * specified all sampled particle states will be used.
 */ 
class StandardParticleSource : public ParticleSource
{

private:

  // Typedef for scalar traits
  typedef Teuchos::ScalarTraits<double> ST;

  // Typedef for the dimension trial counter map
  typedef ParticleDistribution::DimensionCounterMap DimensionCounterMap;

  // Typedef for the particle state sampling function
  typedef std::function<void(ParticleState&,DimensionCounterMap&)>
  ParticleStateSamplingFunction;

public:

  //! Constructor
  StandardParticleSource(
      const std::shared_ptr<const ParticleDistribution>& particle_distribution,
      const ParticleType particle_type );

  //! Destructor
  ~StandardParticleSource()
  { /* ... */ }

  //! Get the source id
  ModuleTraits::InternalROIHandle getId() const override;

  //! Get the particle type
  ParticleType getParticleType() const;

  //! Set the critical line energies
  void setCriticalLineEnergies(
               const Teuchos::ArrayRCP<const double>& critical_line_energies );

  //! Print a summary of the source data
  void printSummary( std::ostream& os ) const override;

  //! Return the number of trials in the phase space dimension
  ModuleTraits::InternalCounter getNumberOfDimensionTrials(
                          const PhaseSpaceDimension dimension ) const override;

  //! Return the number of samples in the phase space dimension
  ModuleTraits::InternalCounter getNumberOfDimensionSamples(
                          const PhaseSpaceDimension dimension ) const override;

  //! Return the sampling efficiency in the phase space dimension
  double getDimensionSamplingEfficiency(
                          const PhaseSpaceDimension dimension ) const override;

protected:

  //! Enable thread support
  void enableThreadSupportImpl( const size_t threads ) override;

  //! Reset the source data
  void resetDataImpl() override;

  //! Reduce the source data
  void reduceDataImpl(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process ) override;

  //! Export the source data
  void exportDataImpl( SourceHDF5FileHandler& hdf5_file ) const override;
  
  /*! \brief Return the number of particle states that will be sampled for the 
   * given history number
   */
  unsigned long long getNumberOfParticleStateSamples(
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

  // Reduce the dimension sample counters on the comm
  void reduceDimensionSampleCounters(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process );

  // Reduce the dimension trial counters on the comm
  void reduceDimensionTrialCounters(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process );

  // Reduce the dimension counters on the comm
  static void reduceDimensionCounters(
            Teuchos::Array<DimensionCounterMap>& dimension_counters,
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
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
           const Teuchos::Array<DimensionCounterMap>& all_dimension_counters );

  // Reduce the local dimension sample counters
  ModuleTraits::InternalCounter reduceLocalDimensionSampleCounters(
                                   const PhaseSpaceDimension dimension ) const;

  // Reduce the local dimension trial counters
  ModuleTraits::InternalCounter reduceLocalDimensionTrialCounters(
                                   const PhaseSpaceDimension dimension ) const;

  // Reduce the dimension counter
  static ModuleTraits::InternalCounter reduceDimensionCounters(
               const PhaseSpaceDimension dimension,
               const Teuchos::Array<DimensionCounterMap>& dimension_counters );

  // Initialize the dimension sample counters
  void initializeDimensionSampleCounters();

  // Initialize the dimension trial counters
  void initializeDimensionTrialCounters();

  // Initialize the dimension counters
  void initializeDimensionCounters(
                     Teuchos::Array<DimensionCounterMap>& dimension_counters );

  // Increment the dimension counters
  static void incrementDimensionCounters(
                                  DimensionCounterMap& dimension_counters,
                                  const bool ignore_energy_dimension = false );
  
  // The particle distribution
  std::shared_ptr<const ParticleDistribution> d_particle_distribution;

  // Ther particle type that will be generated by this source
  ParticleType d_particle_type;

  // The dimension trial counters
  Teuchos::Array<DimensionCounterMap> d_dimension_trial_counters;

  // The dimension samples counters
  Teuchos::Array<DimensionCounterMap> d_dimension_sample_counters;

  // The particle state critical line energy sampling functions
  Teuchos::Array<Utility::Pair<double,ParticleStateSamplingFunction> >
  d_particle_state_critical_line_energy_sampling_functions;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_PARTICLE_SOURCE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleSource.hpp
//---------------------------------------------------------------------------//
