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
#include <boost/mpl/vector.hpp>

// FRENSIE Includes
#include "MonteCarlo_EntityEstimator.hpp"
#include "MonteCarlo_EstimatorContributionMultiplierPolicy.hpp"
#include "MonteCarlo_ParticleEnteringCellEventObserver.hpp"
#include "MonteCarlo_ParticleLeavingCellEventObserver.hpp"
#include "Geometry_Model.hpp"
#include "Utility_Map.hpp"
#include "Utility_Set.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Tuple.hpp"

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
class CellPulseHeightEstimator : public EntityEstimator,
                                 public ParticleEnteringCellEventObserver,
                                 public ParticleLeavingCellEventObserver
{
  // Typedef for the serial update tracker
  typedef std::pair<double,std::unordered_map<Geometry::Model::EntityId,std::tuple<double,double> > >
  SerialUpdateTracker;

  // Typedef for the parallel update tracker
  typedef std::vector<SerialUpdateTracker> ParallelUpdateTracker;

public:

  //! Typedef for the cell id type
  typedef Geometry::Model::EntityId CellIdType;

  //! Typedef for event tags used for quick dispatcher registering
  typedef boost::mpl::vector<ParticleEnteringCellEventObserver::EventTag,
                             ParticleLeavingCellEventObserver::EventTag>
  EventTags;

  //! Constructor
  CellPulseHeightEstimator( const Id id,
                            const double multiplier,
                            const std::vector<CellIdType>& entity_ids );

  //! Destructor
  ~CellPulseHeightEstimator()
  { /* ... */ }

  //! Check if the estimator is a cell estimator
  bool isCellEstimator() const final override;

  //! Check if the estimator is a surface estimator
  bool isSurfaceEstimator() const final override;

  //! Check if the estimator is a mesh estimator
  bool isMeshEstimator() const final override;

  //! Add current history estimator contribution
  void updateFromParticleEnteringCellEvent(
                               const ParticleState& particle,
                               const CellIdType cell_entering ) final override;

  //! Add current history estimator contribution
  void updateFromParticleLeavingCellEvent(
                                const ParticleState& particle,
                                const CellIdType cell_leaving ) final override;

  //! Commit the contribution from the current history to the estimator
  void commitHistoryContribution() final override;

  //! Print the estimator data summary
  void printSummary( std::ostream& os ) const final override;

  //! Enable support for multiple threads
  void enableThreadSupport( const unsigned num_threads ) final override;

  //! Reset the estimator data
  void resetData() final override;

private:

  // Default constructor
  CellPulseHeightEstimator();

  // Assign discretization to an estimator dimension
  void assignDiscretization( const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>& bins,
                             const bool range_dimension ) final override;

  // Assign response function to the estimator
  void assignResponseFunction( const std::shared_ptr<const ParticleResponse>& response_function ) final override;

  // Assign the particle type to the estimator
  void assignParticleType( const ParticleType particle_type ) final override;

  // Check and correct a positron contribution
  static void checkAndCorrectPositronEnergyContribution(
                                                 const ParticleState& particle,
                                                 double& energy_contribution );

  // Calculate the estimator contribution from the entire history
  static double calculateHistoryContribution( const double energy_deposition,
                                              const double charge_deposition,
                                              const double source_weight,
                                              WeightMultiplier );

  // Calculate the estimator contribution from the entire history
  static double calculateHistoryContribution( const double energy_deposition,
                                              const double charge_deposition,
                                              const double source_weight,
                                              WeightAndEnergyMultiplier );

  // Calculate the estimator contribution from the entire history
  static double calculateHistoryContribution( const double energy_deposition,
                                              const double charge_deposition,
                                              const double source_weight,
                                              WeightAndChargeMultiplier );

  // Add info to update tracker
  void addInfoToUpdateTracker( const unsigned thread_id,
                               const CellIdType cell_id,
                               const double source_weight,
                               const double energy_contribution,
                               const double charge_contribution );

  // Get the entity iterators from the update tracker
  void getCellIteratorFromUpdateTracker(
                const unsigned thread_id,
                typename Utility::TupleElement<1,SerialUpdateTracker>::type::const_iterator& start_cell,
                typename Utility::TupleElement<1,SerialUpdateTracker>::type::const_iterator& end_cell ) const;

  // Reset the update tracker
  void resetUpdateTracker( const unsigned thread_id );

  // Save the data to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the data from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The entities that have been updated
  ParallelUpdateTracker d_update_tracker;

  // The generic particle state map (avoids having to make a new map for cont.)
  std::vector<Estimator::DimensionValueMap> d_dimension_values;
};

//! The weight multiplied cell pulse height estimator
typedef CellPulseHeightEstimator<WeightMultiplier> WeightMultipliedCellPulseHeightEstimator;

//! The weight and energy multiplied cell pulse height estimator
typedef CellPulseHeightEstimator<WeightAndEnergyMultiplier> WeightAndEnergyMultipliedCellPulseHeightEstimator;

//! The weight and charge multiplied cell pulse height estimator
typedef CellPulseHeightEstimator<WeightAndChargeMultiplier> WeightAndChargeMultipliedCellPulseHeightEstimator;

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS1_VERSION( CellPulseHeightEstimator, MonteCarlo, 0 );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_CellPulseHeightEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_CELL_PULSE_HEIGHT_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CellPulseHeightEstimator.hpp
//---------------------------------------------------------------------------//
