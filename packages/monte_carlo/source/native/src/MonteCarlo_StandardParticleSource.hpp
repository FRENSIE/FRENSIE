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
#include <functional>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleSource.hpp"
#include "MonteCarlo_ParticleDistribution.hpp"
#include "Geometry_PointLocation.hpp"
#include "Utility_GlobalOpenMPSession.hpp"

namespace MonteCarlo{

//! The standard source class
class StandardParticleSource : public ParticleSource
{

private:

  // Typedef for scalar traits
  typedef Teuchos::ScalarTraits<double> ST;

  // Typedef for the dimension trial counter map
  typedef ParticleDistribution::DimensionTrialCounterMap
  DimensionTrialCounterMap;

public:

  //! Constructor
  StandardParticleSource(
    const ModuleTraits::InternalSourceHandle id,
    const std::shared_ptr<const ParticleDistribution>& particle_distribution );

  //! Destructor
  ~StandardParticleSource()
  { /* ... */ }

  //! Enable thread support
  void enableThreadSupport( const unsigned threads );

  //! Reset the source data
  void resetData();

  //! Reduce the source data
  void reduceData(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process );

  //! Export the source data
  void exportData(
            const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file ) const;

  //! Print a summary of the source data
  void printSummary( std::ostream& os ) const;

  //! Set the critical line energies
  void setCriticalLineEnergies(
               const Teuchos::ArrayRCP<const double>& critical_line_energies );

  //! Set the rejection cell
  template<typename PointLocationFunction>
  void setRejectionCell(const Geometry::ModuleTraits::InternalCellHandle& cell,
                        PointLocationFunction location_function );

  //! Sample a particle state from the source
  void sampleParticleState( ParticleBank& bank,
			    const unsigned long long history );

  //! Return the number of sampling trials
  TrialCounter getNumberOfTrials() const;

  //! Return the number of trials in the phase space dimension
  DimensionTrialCounter getNumberOfDimensionTrials(
                                   const PhaseSpaceDimension dimension ) const;

  //! Return the number of samples that have been generated
  TrialCounter getNumberOfSamples() const;

  //! Return the number of samples in the phase space dimension
  DimensionTrialCounter getNumberOfDimensionSamples(
                                   const PhaseSpaceDimension dimension ) const;

  //! Return the sampling efficiency from the source
  double getSamplingEfficiency() const;

  //! Return the sampling efficiency in the phase space dimension
  double getDimensionSamplingEfficiency(
                                   const PhaseSpaceDimension dimension ) const;

private:

  // Check if the sampled particle position is valid
  bool isSampledParticlePositionValid( const ParticleState& particle ) const;

  // Generate probe particles
  void generateProbeParticles(
                             ParticleSourcePhaseSpacePoint& phase_space_sample,
                             ParticleBank& bank,
                             const unsigned long long history ) const;

  // Reduce the local samples counters
  TrialCounter reduceLocalSampleCounters() const;

  // Reduce the local trials counters
  TrialCounter reduceLocalTrialCounters() const;

  // Reduce all of the local dimension samples counters
  void reduceAllLocalDimensionSampleCounters(
                   DimensionTrialCounterMap& dimension_sample_counters ) const;

  // Reduce all of the local dimension trials counters
  void reduceAllLocalDimensionTrialCounters(
                    DimensionTrialCounterMap& dimension_trial_counters ) const;

  // Reduce the dimension counters
  static void reduceAllDimensionCounters(
      DimensionTrailCounterMap& dimension_counters,
      const Teuchos::Array<DimensionTrialCounterMap>& all_dimension_counters );

  // Reduce the local dimension sample counters
  DimensionTrailCounter reduceLocalDimensionSampleCounters(
                                   const PhaseSpaceDimension dimension ) const;

  // Reduce the local dimension trial counters
  DimensionTrialCounter reduceLocalDimensionTrialCounters(
                                   const PhaseSpaceDimension dimension ) const;

  // Reduce the dimension counter
  static DimensionTrialCounter reduceDimensionCounters(
          const PhaseSpaceDimension dimension,
          const Teuchos::Array<DimensionTrialCounterMap>& dimension_counters );
  
  // The particle distribution
  std::shared_ptr<const ParticleDistribution> d_particle_distribution;

  // The critical line energies
  Teuchos::ArrayRCP<const double> d_critical_line_energies;

  // The cell rejection functions
  typedef std::function<Geometry::PointLocation (const Geometry::Ray&)>
  CellRejectionFunction;
  Teuchos::Array<CellRejectionFunction> d_cell_rejection_functions;

  // The number of trials
  Teuchos::Array<TrialCounter> d_number_of_trials;

  // The number of valid samples
  Teuchos::Array<TrialCounter> d_number_of_samples;

  // The dimension trial counters
  Teuchos::Array<DimensionTrialCounterMap> d_dimension_trial_counters;

  // The dimension samples counters
  Teuchos::Array<DimensionTrialCounterMap> d_dimension_sample_counters;
};

// Set a rejection cell
/*! \details A rejection cell is used to determine if a sampled particle
 * position should be kept or rejected. If the sampled point is inside of
 * one of the rejection cells, it is kept. This function can be used to
 * set multiple rejection cells. Only the master thread should call this
 * method.
 */
template<typename PointLocationFunction>
inline void StandardParticleSource::setRejectionCell(
                        const Geometry::ModuleTraits::InternalCellHandle& cell,
                        PointLocationFunction location_function )
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  // Make sure the cell is valid
  testPrecondition( cell !=
                    Geometry::ModuleTraits::invalid_internal_cell_handle );

  CellRejectionFunction new_cell_rejection_function =
    std::bind<Geometry::PointLocation>( location_function,
                                        std::placeholders::_1,
                                        cell );

  d_cell_rejection_functions.push_back( new_cell_rejection_function );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_PARTICLE_SOURCE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleSource.hpp
//---------------------------------------------------------------------------//
