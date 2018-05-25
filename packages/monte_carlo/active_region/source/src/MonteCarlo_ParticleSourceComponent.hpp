//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSourceComponent.hpp
//! \author Alex Robinson
//! \brief  The particle source component class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_SOURCE_COMPONENT_HPP
#define MONTE_CARLO_PARTICLE_SOURCE_COMPONENT_HPP

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_PhaseSpaceDimension.hpp"
#include "MonteCarlo_UniqueIdManager.hpp"
#include "Geometry_Model.hpp"
#include "Geometry_Navigator.hpp"
#include "Utility_Communicator.hpp"
#include "Utility_DistributionTraits.hpp"
#include "Utility_TypeNameTraits.hpp"

namespace MonteCarlo{

//! The particle source component
class ParticleSourceComponent
{

public:

  //! The trial counter type
  typedef Utility::DistributionTraits::Counter Counter;

  //! The cell id set
  typedef Geometry::Model::CellIdSet CellIdSet;

  //! Constructor
  ParticleSourceComponent( const size_t id,
                           const double selection_weight,
                           const std::shared_ptr<const Geometry::Model>& model );

  //! Constructor (with rejection cells)
  ParticleSourceComponent( const size_t id,
                           const double selection_weight,
                           const CellIdSet& rejection_cells,
                           const std::shared_ptr<const Geometry::Model>& model );

  //! Destructor
  virtual ~ParticleSourceComponent()
  { /* ... */ }

  //! Enable thread support
  void enableThreadSupport( const size_t threads );

  //! Reset the sampling statistics
  void resetData();

  //! Reduce the sampling statistics on the root process
  void reduceData( const Utility::Communicator& comm,
                   const int root_process );

  //! Sample a particle state
  void sampleParticleState( ParticleBanke& bank,
                            const unsigned long long history );

  //! Return the starting cells that have been cached
  void getStartingCells( CellIdSet& starting_cells ) const;

  //! Get the selection weight of this component
  double getSelectionWeight() const;

  //! Get the id of this source
  size_t getId() const;

  //! Return the number of sampling trials
  Counter getNumberOfTrials() const;

  //! Return the number of samples that have been generated
  Counter getNumberOfSamples() const;

  //! Return the sampling efficiency from the source
  double getSamplingEfficiency() const;

  //! Return the number of sampling trials in the phase space dimension
  virtual Counter getNumberOfDimensionTrials(
                               const PhaseSpaceDimension dimension ) const = 0;

  //! Return the number of samples in the phase space dimension
  virtual Counter getNumberOfDimensionSamples(
                               const PhaseSpaceDimension dimension ) const = 0;

  //! Return the sampling efficiency in the phase space dimension
  virtual double getDimensionSamplingEfficiency(
                               const PhaseSpaceDimension dimension ) const = 0;

  //! Print a summary of the sampling statistics
  virtual void printSummary( std::ostream& os ) const = 0;

  //! Log a summary of the sampling statistics
  void logSummary() const;

protected:

  //! Enable thread support
  virtual void enableThreadSupportImpl( const size_t threads ) = 0;

  //! Reset the sampling statistics
  virtual void resetDataImpl() = 0;

  //! Reduce the sampling statistics on the root process
  virtual void reduceDataImpl( const Utility::Communicator& comm,
                               const int root_process ) = 0;

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
   * MonteCarlo::ParticleSourceComponent::sampleParticleState method. True 
   * should be returned if another sample can be made for this history state 
   * id.
   */
  virtual bool sampleParticleStateImpl(
                               const std::shared_ptr<ParticleState>& particle,
                               const unsigned long long history_state_id ) = 0;

  //! Print a standard summary of the source data
  void printStandardSummary( const std::string& source_component_type,
                             const Counter trials,
                             const Counter samples,
                             const double efficiency,
                             std::ostream& os ) const;

  //! Print a standard summary of the source starting cells
  void printStandardStartingCellSummary( const CellIdSet& starting_cells,
                                         std::ostream& os ) const;

  //! Print a standard summary of the dimension data
  void printStandardDimensionSummary(
                                const std::string& dimension_distribution_type,
                                const PhaseSpaceDimension dimension,
                                const Counter trials,
                                const Counter samples,
                                const double efficiency,
                                std::ostream& os ) const;

private:

  // Merge the starting cells on the root process
  void mergeStartingCells( const Utility::Communicator& comm,
                           const int root_process );

  // Merge the local starting cells
  void mergeLocalStartCellCaches( CellIdSet& starting_cells ) const;

  // Reduce the sample counters on the root process
  void reduceSampleCounters( const Utility::Communicator& comm,
                             const int root_process );

  // Reduce the trial counters on the root process
  void reduceTrialCounters( const Utility::Communicator& comm,
                            const int root_process );

  // Reduce the counters on the root process
  static void reduceCounters( std::vector<Counter>& counters,
                              Utility::Communicator& comm,
                              const int root_process );

  // Reduce the local samples counters
  Counter reduceLocalSampleCounters() const;

  // Reduce the local trials counters
  Counter reduceLocalTrialCounters() const;

  // Check if the sampled particle position is valid
  bool isSampledParticlePositionValid( const ParticleState& particle,
                                       const Navigator& navigator ) const;

  // The component id
  UniqueIdManager<ParticleSourceComponent,size_t> d_id;

  // The component selection weight
  double d_selection_weight;

  // The rejection cells
  CellIdSet d_rejection_cells;
  
  // The model that the source is embedded in
  std::shared_ptr<const Geometry::Model> d_model;

  // The navigator for the model that the source is embedded in
  std::vector<std::shared_ptr<const Geometry::Navigator> > d_navigator;

  // The start cell cache
  std::vector<CellIdSet> d_start_cell_cache;

  // The number of trials
  std::vector<Counter> d_number_of_trials;

  // The number of valid samples
  std::vector<Counter> d_number_of_samples;
};
  
} // end MonteCarlo namespace

namespace Utility{

//! Specialization of Utility::TypeNameTraits for MonteCarlo::ParticleSourceComponent
template<>
struct TypeNameTraits<MonteCarlo::ParticleSourceComponent>
{
  //! Check if the type has a specialization
  typedef std::true_type IsSpecialized;

  //! Get the type name
  static inline std::string name()
  { return "ParticleSourceComponent"; }
};
  
} // end Utility namespace

#endif // end MONTE_CARLO_PARTICLE_SOURCE_COMPONENT_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSourceComponent.hpp
//---------------------------------------------------------------------------//
