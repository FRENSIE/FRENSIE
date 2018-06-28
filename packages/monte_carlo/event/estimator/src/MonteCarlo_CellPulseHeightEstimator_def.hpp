//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CellPulseHeightEstimator_def.hpp
//! \author Alex Robinson
//! \brief  Cell pulse height estimator class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_CELL_PULSE_HEIGHT_ESTIMATOR_DEF_HPP
#define MONTE_CARLO_CELL_PULSE_HEIGHT_ESTIMATOR_DEF_HPP

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Utility_OpenMPProperties.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Default constructor
template<typename ContributionMultiplierPolicy>
CellPulseHeightEstimator<ContributionMultiplierPolicy>::CellPulseHeightEstimator()
{ /* ... */ }
  
// Constructor
template<typename ContributionMultiplierPolicy>
CellPulseHeightEstimator<ContributionMultiplierPolicy>::CellPulseHeightEstimator(
          const Estimator::idType id,
          const double multiplier,
          const std::vector<CellIdType>& entity_ids )
  : BaseEstimatorType( id, multiplier, entity_ids ),
    ParticleEnteringCellEventObserver(),
    ParticleLeavingCellEventObserver(),
    d_update_tracker( 1 ),
    d_dimension_values( 1 )
{ /* ... */ }

// Add current history estimator contribution
/*! \details It is unsafe to call this function directly! This function will
 * be called by the appropriate dispatcher when an event of interest occurs.
 * If calling this function directly, make sure that the cell of interest is
 * actually assigned to this estimator (otherwise segfaults are likely!).
 */
template<typename ContributionMultiplierPolicy>
inline void CellPulseHeightEstimator<ContributionMultiplierPolicy>::updateFromParticleEnteringCellEvent(
					       const ParticleState& particle,
					       const CellIdType cell_entering )
{
  // Make sure that the particle type is assigned
  testPrecondition( this->isParticleTypeAssigned( particle.getParticleType() ) );

  unsigned thread_id = Utility::OpenMPProperties::getThreadId();

  double contribution = particle.getWeight()*particle.getEnergy();

  this->addInfoToUpdateTracker( thread_id, cell_entering, contribution );

  // Indicate that there is an uncommitted history contribution
  this->setHasUncommittedHistoryContribution( thread_id );
}

// Add current history estimator contribution
/*! \details It is unsafe to call this function directly! This function will
 * be called by the appropriate dispatcher when an event of interest occurs.
 * If calling this function directly, make sure that the cell of interest is
 * actually assigned to this estimator (otherwise segfaults are likely! ).
 */
template<typename ContributionMultiplierPolicy>
inline void CellPulseHeightEstimator<ContributionMultiplierPolicy>::updateFromParticleLeavingCellEvent(
					        const ParticleState& particle,
					        const CellIdType cell_leaving )
{
  // Make sure that the particle type is assigned
  testPrecondition( this->isParticleTypeAssigned( particle.getParticleType() ) );
  unsigned thread_id = Utility::OpenMPProperties::getThreadId();
  
  double contribution = -particle.getWeight()*particle.getEnergy();
  
  this->addInfoToUpdateTracker( thread_id, cell_leaving, contribution );
  
  // Indicate that there is an uncommitted history contribution
  this->setHasUncommittedHistoryContribution( thread_id );
}

// Add estimator contribution from a portion of the current history
template<typename ContributionMultiplierPolicy>
void CellPulseHeightEstimator<ContributionMultiplierPolicy>::commitHistoryContribution()
{
  unsigned thread_id = Utility::OpenMPProperties::getThreadId();

  typename SerialUpdateTracker::const_iterator
    cell_data, end_cell_data;

  this->getCellIteratorFromUpdateTracker( thread_id, cell_data, end_cell_data );

  double energy_deposition_in_all_cells = 0.0;

  size_t bin_index;
  double bin_contribution;

  Estimator::DimensionValueMap& thread_dimension_values =
    d_dimension_values[thread_id];

  while( cell_data != end_cell_data )
  {
    thread_dimension_values[ENERGY_DIMENSION] =
      boost::any( cell_data->second );

    if( this->isPointInEstimatorPhaseSpace( thread_dimension_values ) )
    {
      bin_index = this->calculateBinIndex( thread_dimension_values, 0u );

      bin_contribution = this->calculateHistoryContribution(
					      cell_data->second,
					      ContributionMultiplierPolicy() );

      this->commitHistoryContributionToBinOfEntity( cell_data->first,
						    bin_index,
						    bin_contribution );

      // Add the energy deposition in this cell to the total energy deposition
      energy_deposition_in_all_cells += cell_data->second;
    }

    ++cell_data;
  }

  // Store the total energy deposition in the dimension values map
  thread_dimension_values[ENERGY_DIMENSION] =
    boost::any( energy_deposition_in_all_cells );

  // Determine the pulse bin for the combination of all cells
  if( this->isPointInEstimatorPhaseSpace( thread_dimension_values ) )
  {
    bin_index = this->calculateBinIndex( thread_dimension_values, 0u );

    bin_contribution = this->calculateHistoryContribution(
					      energy_deposition_in_all_cells,
					      ContributionMultiplierPolicy() );

    this->commitHistoryContributionToBinOfTotal( bin_index,
						 bin_contribution );
  }

  // Reset the update tracker
  this->resetUpdateTracker( thread_id );

  // Reset the has uncommitted history contribution boolean
  this->unsetHasUncommittedHistoryContribution( thread_id );
}

// Print the estimator data
template<typename ContributionMultiplierPolicy>
void CellPulseHeightEstimator<ContributionMultiplierPolicy>::printSummary(
						       std::ostream& os ) const
{
  os << "Cell Pulse Height Estimator: " << this->getId() << "\n";

  this->printImplementation( os, "Cell" );
}

// Enable support for multiple threads
template<typename ContributionMultiplierPolicy>
void
CellPulseHeightEstimator<ContributionMultiplierPolicy>::enableThreadSupport(
						   const unsigned num_threads )
{
  // Make sure only the root thread calls this
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );
  
  BaseEstimatorType::enableThreadSupport( num_threads );

  // Add thread support to update tracker
  d_update_tracker.resize( num_threads );

  // Add thread support to the dimension values
  d_dimension_values.resize( num_threads );
}

// Reset the estimator data
template<typename ContributionMultiplierPolicy>
void CellPulseHeightEstimator<ContributionMultiplierPolicy>::resetData()
{
  // Make sure only the root thread calls this
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  BaseEstimatorType::resetData();

  // Reset the update tracker
  for( size_t i = 0; i < d_update_tracker.size(); ++i )
  {
    d_update_tracker[i].clear();

    this->unsetHasUncommittedHistoryContribution( i );
  }
}

// Assign bin boundaries to an estimator dimension
template<typename ContributionMultiplierPolicy>
void CellPulseHeightEstimator<ContributionMultiplierPolicy>::assignDiscretization(
  const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>& bins,
  const bool range_dimension ) 
{
  if( bins->getDimension() == ENERGY_DIMENSION )
    BaseEstimatorType::assignDiscretization( bins, false );
  else
  {
    FRENSIE_LOG_TAGGED_WARNING( "Estimator",
                                << bin_boundaries->getDimensionName() <<
                                " bins cannot be set for pulse height "
                                "estimators. The bins requested for pulse "
                                "height estimator " << this->getId() <<
                                " will be ignored." );
  }
}

// Set the response functions
template<typename ContributionMultiplierPolicy>
void CellPulseHeightEstimator<ContributionMultiplierPolicy>::assignResponseFunction(
             const std::shared_ptr<const ParticleResponse>& response_function )
{
  FRENSIE_LOG_TAGGED_WARNING( "Estimator",
                              "response functions cannot be set for pulse "
                              "height estimators. The response function "
                              "requested for pulse height estimator "
                              << this->getId() << " will be ignored." );
}

// Set the particle types that can contribute to the estimator
/*! \details Only photons and electrons can contribute to this estimator
 */
template<typename ContributionMultiplierPolicy>
void CellPulseHeightEstimator<ContributionMultiplierPolicy>::assignParticleType( const ParticleType particle_type ) 
{
  if( particle_type == PHOTON ||
      particle_type == ELECTRON ||
      particle_type == POSITRON )
    Estimator::assignParticleType( particle_type );
  else
  {
    FRENSIE_LOG_TAGGED_WARNING( "Estimator",
                                "cannot assign particle type "
                                << particle_type << " to a pulse height "
                                "estimators (only photons and charged "
                                "particles can contribute). Pulse height "
                                "estimator " << this->getId() << " will "
                                "ignore this request." );
  }
}

// Calculate the estimator contribution from the entire history
/*! \details The multiplier policy cannot be used directly since it only
 * operates on a particle state. The policy classes will instead be used as
 * tags for tag dispatching. This function simply returns 1.0.
 */
template<typename ContributionMultiplierPolicy>
inline double CellPulseHeightEstimator<ContributionMultiplierPolicy>::calculateHistoryContribution(
					        const double energy_deposition,
						WeightMultiplier )
{
  return 1.0;
}

// Calculate the estimator contribution from the entire history
/*! \details The multiplier policy cannot be used directly since it only
 * operates on a particle state. The policy classes will instead be used as
 * tags for tag dispatching. This function returns the energy that has been
 * deposited in the cell(s) of interest for the entire history.
 */
template<typename ContributionMultiplierPolicy>
inline double CellPulseHeightEstimator<ContributionMultiplierPolicy>::calculateHistoryContribution(
					        const double energy_deposition,
						WeightAndEnergyMultiplier )
{
  return energy_deposition;
}

// Add info to update tracker
template<typename ContributionMultiplierPolicy>
void CellPulseHeightEstimator<ContributionMultiplierPolicy>::addInfoToUpdateTracker(
						   const unsigned thread_id,
						   const CellIdType cell_id,
						   const double contribution )
{
  // Make sure the thread id is valid
  testPrecondition( thread_id < d_update_tracker.size() );

  SerialUpdateTracker& thread_update_tracker = d_update_tracker[thread_id];

  auto cell_it = thread_update_tracker.find( cell_id );

  if( cell_it != thread_update_tracker.end() )
    cell_it->second += contribution;
  else
    thread_update_tracker[cell_id] = contribution;
}

// Get the entity iterators from the update tracker
template<typename ContributionMultiplierPolicy>
void CellPulseHeightEstimator<ContributionMultiplierPolicy>::getCellIteratorFromUpdateTracker(
	         const unsigned thread_id,
		 typename SerialUpdateTracker::const_iterator& start_cell,
	         typename SerialUpdateTracker::const_iterator& end_cell ) const
{
  // Make sure the thread id is valid
  testPrecondition( thread_id < d_update_tracker.size() );

  start_cell = d_update_tracker[thread_id].begin();
  end_cell = d_update_tracker[thread_id].end();
}

// Reset the update tracker
template<typename ContributionMultiplierPolicy>
void
CellPulseHeightEstimator<ContributionMultiplierPolicy>::resetUpdateTracker(
						     const unsigned thread_id )
{
  // Make sure the thread id is valid
  testPrecondition( thread_id < d_update_tracker.size() );

  d_update_tracker[thread_id].clear();
}

// Save the data to an archive
// Note: The update tracker will not be saved. Any uncommited data should be
// committed before the save.
template<typename ContributionMultiplierPolicy>
template<typename Archive>
void CellPulseHeightEstimator<ContributionMultiplierPolicy>::save( Archive& ar, const unsigned version )
{
  // Save the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseEstimatorType );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleEnteringCellEventObserver );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleLeavingCellEventObserver );
}

// Load the data from an archive
template<typename ContributionMultiplierPolicy>
template<typename Archive>
void CellPulseHeightEstimator<ContributionMultiplierPolicy>::load( Archive& ar, const unsigned version )
{
  // Load the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseEstimatorType );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleEnteringCellEventObserver );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleLeavingCellEventObserver );

  // Initialize the thread data
  d_update_tracker.resize( 1 );
  d_dimension_values.resize( 1 );
}

} // end MonteCarlo namespace

// Explicit instantiation (extern declaration)
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( WeightMultipliedCellPulseHeightEstimator, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightMultiplier> );
EXTERN_EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightMultiplier> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( WeightAndEnergyMultipliedCellPulseHeightEstimator );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightAndEnergyMultiplier> );
EXTERN_EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightAndEnergyMultiplier> );

#endif // end MONTE_CARLO_CELL_PULSE_HEIGHT_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CellPulseHeightEstimator_def.hpp
//---------------------------------------------------------------------------//
