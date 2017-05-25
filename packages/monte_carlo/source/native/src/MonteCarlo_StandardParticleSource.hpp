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
#include "Utility_GlobalOpenMPSession.hpp"

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

  //! Enable thread support
  void enableThreadSupport( const size_t threads ) override;

  //! Reset the source data
  void resetData() override;

  //! Reduce the source data
  void reduceData(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process ) override;

  //! Export the source data
  void exportData( const std::shared_ptr<Utility::HDF5FileHandler>&
                   hdf5_file ) const override;

  //! Print a summary of the source data
  void printSummary( std::ostream& os ) const override;

  //! Set the critical line energies
  void setCriticalLineEnergies(
               const Teuchos::ArrayRCP<const double>& critical_line_energies );

  //! Set the rejection cell
  void setRejectionCell(
                       const Geometry::ModuleTraits::InternalCellHandle cell );

  //! Sample a particle state from the source
  void sampleParticleState( ParticleBank& bank,
			    const unsigned long long history ) override;

  //! Return the number of sampling trials
  ModuleTraits::InternalCounter getNumberOfTrials() const override;

  //! Return the number of trials in the phase space dimension
  ModuleTraits::InternalCounter getNumberOfDimensionTrials(
                          const PhaseSpaceDimension dimension ) const override;

  //! Return the number of samples that have been generated
  ModuleTraits::InternalCounter getNumberOfSamples() const override;

  //! Return the number of samples in the phase space dimension
  ModuleTraits::InternalCounter getNumberOfDimensionSamples(
                          const PhaseSpaceDimension dimension ) const override;

  //! Return the sampling efficiency from the source
  double getSamplingEfficiency() const override;

  //! Return the sampling efficiency in the phase space dimension
  double getDimensionSamplingEfficiency(
                          const PhaseSpaceDimension dimension ) const override;

  //! Return the starting cells that have been cached
  void getStaringCells( std::set<Geometry::ModuleTraits::InternalCellHandle>& starting_cells ) const override;

private:

  // Check if the sampled particle position is valid
  bool isSampledParticlePositionValid( const ParticleState& particle ) const;

  // Generate probe particles
  void generateProbeParticles( ParticleBank& bank,
                               const unsigned long long history );

  // Sample a particle state
  void sampleParticleStateBasicImpl(
                         ParticleStateSamplingFunction& sampling_function,
                         ParticleState& particle,
                         const bool ignore_energy_dimension_counters = false );

  // Merge the starting cells on the comm
  void mergeStartingCells(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process );

  // Merge the starting cells with the packaged data
  void mergeStaringCellsWithPackagedData(
          std::set<Geometry::ModuleTraits::InternalCellHandle>& starting_cells,
          const std::string& packaged_data );

  // Package the starting cell data
  std::string packageStartingCellData(
                    const std::set<Geometry::ModuleTraits::InternalCellHandle>&
                    starting_cells ) const;

  // Unpack the starting cell data
  std::set<Geometry::ModuleTraits::InternalCellHandle>
  unpackStartingCellData( const std::string& packaged_data ) const;
  
  // Reduce the sample counters on the comm
  void reduceSampleCounters(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process );

  // Reduce the trial counters on the comm
  void reduceTrialCounters(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process );

  // Reduce the counters on the comm
  static void reduceCounters(
            Teuchos::Array<ModuleTraits::InternalCounter>& counters,
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process );

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

  // Merge the local starting cells
  void mergeLocalStartCellCaches( std::set<Geometry::ModuleTraits::InternalCellHandle>& starting_cells ) const;

  // Reduce the local samples counters
  ModuleTraits::InternalCounter reduceLocalSampleCounters() const;

  // Reduce the local trials counters
  ModuleTraits::InternalCounter reduceLocalTrialCounters() const;

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

  // Initialze the start cell caches
  void initializeStartCellCaches();

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

  // The default particle state sampling function
  ParticleStateSamplingFunction d_default_particle_state_sampling_function;

  // The start cell cache
  Teuchos::Array<std::set<Geometry::ModuleTraits::InternalCellHandle> >
  d_start_cell_cache;

  // The number of trials
  Teuchos::Array<ModuleTraits::InternalCounter> d_number_of_trials;

  // The number of valid samples
  Teuchos::Array<ModuleTraits::InternalCounter> d_number_of_samples;

  // The dimension trial counters
  Teuchos::Array<DimensionCounterMap> d_dimension_trial_counters;

  // The dimension samples counters
  Teuchos::Array<DimensionCounterMap> d_dimension_sample_counters;

  // The particle state critical line energy sampling functions
  Teuchos::Array<Utility::Pair<double,ParticleStateSamplingFunction> >
  d_particle_state_critical_line_energy_sampling_functions;

  // The rejection cells
  std::set<Geometry::ModuleTraits::InternalCellHandle> d_rejection_cells;
};

// Set a rejection cell
/*! \details A rejection cell is used to determine if a sampled particle
 * position should be kept or rejected. If the sampled point is inside of
 * one of the rejection cells, it is kept. This function can be used to
 * set multiple rejection cells. Only the master thread should call this
 * method.
 */
inline void StandardParticleSource::setRejectionCell(
                        const Geometry::ModuleTraits::InternalCellHandle cell )
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  // Make sure the cell is valid
  testPrecondition( this->getModel().doesCellExist( cell ) );

  d_rejection_cells.insert( cell );

  for( int i = 0; i < d_start_cell_cache.size(); ++i )
    d_start_cell_cache[i].insert( cell );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_PARTICLE_SOURCE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleSource.hpp
//---------------------------------------------------------------------------//
