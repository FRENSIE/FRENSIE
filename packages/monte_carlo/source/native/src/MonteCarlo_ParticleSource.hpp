//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSource.hpp
//! \author Alex Robinson
//! \brief  Particle source declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_SOURCE_HPP
#define MONTE_CARLO_PARTICLE_SOURCE_HPP

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_Comm.hpp>

// MonteCarlo Includes
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_PhaseSpaceDimension.hpp"
#include "MonteCarlo_ModuleTraits.hpp"
#include "MonteCarlo_SourceHDF5FileHandler.hpp"

namespace MonteCarlo{

//! The particle source base class
class ParticleSource
{

public:

  //! Constructor
  ParticleSource();

  //! Destructor
  virtual ~ParticleSource()
  { /* ... */ }

  //! Get the source id
  virtual ModuleTraits::InternalROIHandle getId() const = 0;

  //! Enable thread support
  void enableThreadSupport( const size_t threads );

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
  virtual void printSummary( std::ostream& os ) const = 0;

  //! Embed the source in the desired model
  void embedInModel( const std::shared_ptr<const Geometry::Model>& model );

  //! Sample a particle state from the source
  void sampleParticleState( ParticleBank& bank,
                            const unsigned long long history );

  // Return the number of sampling trials
  ModuleTraits::InternalCounter getNumberOfTrials() const;

  //! Return the number of sampling trials in the phase space dimension
  virtual ModuleTraits::InternalCounter getNumberOfDimensionTrials(
                               const PhaseSpaceDimension dimension ) const = 0;

  // Return the number of samples that have been generated
  ModuleTraits::InternalCounter getNumberOfSamples() const;

  //! Return the number of samples in the phase space dimension
  virtual ModuleTraits::InternalCounter getNumberOfDimensionSamples(
                               const PhaseSpaceDimension dimension ) const = 0;

  //! Return the sampling efficiency from the source
  double getSamplingEfficiency() const;

  //! Return the sampling efficiency in the phase space dimension
  virtual double getDimensionSamplingEfficiency(
                               const PhaseSpaceDimension dimension ) const = 0;

  //! Return the starting cells that have been cached
  void getStartingCells( std::set<Geometry::ModuleTraits::InternalCellHandle>& starting_cells ) const;

  //! Set the rejection cell
  void setRejectionCell(
                       const Geometry::ModuleTraits::InternalCellHandle cell );

protected:

  //! Enable thread support
  virtual void enableThreadSupportImpl( const size_t threads ) = 0;

  //! Reset the source data
  virtual void resetDataImpl() = 0;

  //! Reduce the source data
  virtual void reduceDataImpl(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process ) = 0;

  //! Export the source data
  virtual void exportDataImpl(
                           SourceHDF5FileHandler& source_hdf5_file ) const = 0;

  /*! \brief Return the number of particle states that will be sampled for the 
   * given history number
   */
  virtual unsigned long long getNumberOfParticleStateSamples(
                                  const unsigned long long history ) const = 0;

  //! Initialize a particle state
  virtual std::shared_ptr<ParticleState> initializeParticleState(
                               const unsigned long long history,
                               const unsigned long long history_state_id ) = 0;
  

  /*! Sample a particle state from the source
   *
   * All geometry model considerations can (and should) be ignored in the
   * implementation of this method. These will be handled by the 
   * MonteCarlo::ParticleSource::sampleParticleState method. True should be
   * returned if another sample can be made for this history state id.
   */
  virtual bool sampleParticleStateImpl(
                               const std::shared_ptr<ParticleState>& particle,
                               const unsigned long long history_state_id ) = 0;

  //! Print a standard summary of the source data
  void printStandardSummary( const std::string& source_type,
                             const ModuleTraits::InternalCounter trials,
                             const ModuleTraits::InternalCounter samples,
                             const double efficiency,
                             std::ostream& os ) const;

  //! Print a standard summary of the source starting cells
  void printStandardStartingCellSummary(
           std::set<Geometry::ModuleTraits::InternalCellHandle> starting_cells,
           std::ostream& os ) const;

  //! Print a standard summary of the dimension data
  void printStandardDimensionSummary(
                                const std::string& dimension_distribution_type,
                                const PhaseSpaceDimension dimension,
                                const ModuleTraits::InternalCounter trials,
                                const ModuleTraits::InternalCounter samples,
                                const double efficiency,
                                std::ostream& os ) const;

private:

  // Merge the starting cells on the comm
  void mergeStartingCells(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process );

  // Merge the starting cells with the packaged data
  void mergeStartingCellsWithPackagedData(
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

  // Merge the local starting cells
  void mergeLocalStartCellCaches( std::set<Geometry::ModuleTraits::InternalCellHandle>& starting_cells ) const;

  // Reduce the local samples counters
  ModuleTraits::InternalCounter reduceLocalSampleCounters() const;

  // Reduce the local trials counters
  ModuleTraits::InternalCounter reduceLocalTrialCounters() const;

  // Initialize the start cell caches
  void initializeStartCellCaches();

  // Check if the sampled particle position is valid
  bool isSampledParticlePositionValid( const ParticleState& particle ) const;

  // The model that the source is embedded in
  std::shared_ptr<const Geometry::Model> d_model;

  // The navigator for the model that the source is embedded in
  std::shared_ptr<const Geometry::Navigator> d_navigator;

  // The start cell cache
  Teuchos::Array<std::set<Geometry::ModuleTraits::InternalCellHandle> >
  d_start_cell_cache;

  // The number of trials
  Teuchos::Array<ModuleTraits::InternalCounter> d_number_of_trials;

  // The number of valid samples
  Teuchos::Array<ModuleTraits::InternalCounter> d_number_of_samples;

  // The rejection cells
  std::set<Geometry::ModuleTraits::InternalCellHandle> d_rejection_cells;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_SOURCE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSource.hpp
//---------------------------------------------------------------------------//
