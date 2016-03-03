//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CellPulseHeightEstimator.hpp
//! \author Alex Robinson
//! \brief  Cell pulse height estimator class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_CELL_PULSE_HEIGHT_ESTIMATOR_HPP
#define MONTE_CARLO_CELL_PULSE_HEIGHT_ESTIMATOR_HPP

// Boost Includes
#include <boost/unordered_set.hpp>
#include <boost/mpl/vector.hpp>

// FRENSIE Includes
#include "MonteCarlo_EntityEstimator.hpp"
#include "MonteCarlo_EstimatorContributionMultiplierPolicy.hpp"
#include "MonteCarlo_ParticleEnteringCellEventObserver.hpp"
#include "MonteCarlo_ParticleLeavingCellEventObserver.hpp"
#include "Geometry_ModuleTraits.hpp"

namespace MonteCarlo{

/*! The pulse height entity estimator class
 * \ingroup particle_entering_cell_event
 * \ingroup particle_leaving_cell_event
 * \details This class has been set up to get correct results with multiple
 * threads. However, the commitHistoryContribution member function call 
 * should only appear within an omp critical block. Use the enable thread
 * support member function to set up an instance of this class for the
 * requested number of threads. The classes default initialization is for
 * a single thread.
 */
template<typename ContributionMultiplierPolicy = WeightMultiplier>
class CellPulseHeightEstimator : public EntityEstimator<Geometry::ModuleTraits::InternalCellHandle>, 
				 public ParticleEnteringCellEventObserver,
				 public ParticleLeavingCellEventObserver
{

private:

  // Typedef for the serial update tracker
  typedef boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
			       double>
  SerialUpdateTracker;

  // Typedef for the parallel update tracker
  typedef Teuchos::Array<SerialUpdateTracker> 
  ParallelUpdateTracker;

public:

  //! Typedef for the cell id type
  typedef Geometry::ModuleTraits::InternalCellHandle cellIdType;

  //! Typedef for event tags used for quick dispatcher registering
  typedef boost::mpl::vector<ParticleEnteringCellEventObserver::EventTag,
			     ParticleLeavingCellEventObserver::EventTag>
  EventTags;

  //! Constructor
  CellPulseHeightEstimator( const Estimator::idType id,
			    const double multiplier,
			    const Teuchos::Array<cellIdType>& entity_ids );
  
  //! Destructor
  ~CellPulseHeightEstimator()
  { /* ... */ }

  //! Set the response functions
  void setResponseFunctions( 
                      const Teuchos::Array<std::shared_ptr<ResponseFunction> >&
                      response_functions );

  //! Set the particle types that can contribute to the estimator
  void setParticleTypes( const Teuchos::Array<ParticleType>& particle_types );

  //! Add current history estimator contribution
  void updateFromParticleEnteringCellEvent( const ParticleState& particle,
					    const cellIdType cell_entering );

  //! Add current history estimator contribution
  void updateFromParticleLeavingCellEvent( const ParticleState& particle,
					   const cellIdType cell_leaving );
  
  //! Commit the contribution from the current history to the estimator
  void commitHistoryContribution();

  //! Print the estimator data summary
  void printSummary( std::ostream& os ) const;

  //! Enable support for multiple threads
  void enableThreadSupport( const unsigned num_threads );

  //! Reset the estimator data
  void resetData();

  //! Export the estimator data
  void exportData( const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file,
		   const bool process_data ) const;

private:

  // Assign bin boundaries to an estimator dimension
  void assignBinBoundaries(
     const std::shared_ptr<EstimatorDimensionDiscretization>& bin_boundaries );

  // Calculate the estimator contribution from the entire history
  double calculateHistoryContribution( const double energy_deposition,
				       WeightMultiplier );

  // Calculate the estimator contribution from the entire history
  double calculateHistoryContribution( const double energy_deposition,
				       WeightAndEnergyMultiplier );

  // Add info to update tracker
  void addInfoToUpdateTracker( const unsigned thread_id,
			       const cellIdType cell_id,
			       const double contribution );

  // Get the entity iterators from the update tracker
  void getCellIteratorFromUpdateTracker(
	        const unsigned thread_id,
		typename SerialUpdateTracker::const_iterator& start_cell,
	        typename SerialUpdateTracker::const_iterator& end_cell ) const;

  // Reset the update tracker
  void resetUpdateTracker( const unsigned thread_id );

  // The entities that have been updated
  ParallelUpdateTracker d_update_tracker;

  // The generic particle state map (avoids having to make a new map for cont.)
  Teuchos::Array<Estimator::DimensionValueMap> d_dimension_values;
};

} // end MonteCarlo namespace 

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_CellPulseHeightEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_CELL_PULSE_HEIGHT_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CellPulseHeightEstimator.hpp
//---------------------------------------------------------------------------//
